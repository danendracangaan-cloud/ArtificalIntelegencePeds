// InteractivePeds v0.5 - AML mod GTA SA Android (armeabi-v7a, libGTASA.so 2.00)
// Dibuild dengan header AML 1.1 (terbukti cocok dengan AML di HP pengguna).
#include <mod/amlmod.h>
#include <android/log.h>
#include <thread>
#include <mutex>
#include <queue>
#include <cmath>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <sys/stat.h>
#include <unistd.h>
#include <dlfcn.h>
#include <cstring>
#include <elf.h>
#include "ped_brain.h"
#include "net.h"

#define LOGI(...) __android_log_print(ANDROID_LOG_INFO,  "InteractivePeds", __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, "InteractivePeds", __VA_ARGS__)

MYMOD(net.interactiveped, InteractivePeds, 1.0, you)

// ============================ Config & file bantu ============================
static std::string PKG        = "com.rockstargames.gtasa";
static std::string VIS_DIR;                       // folder yang bisa dibuka user (Android_Unprotected)
static std::string PROXY_HOST = "192.168.1.10";
static std::string PROXY_PORT = "8787";
static float       TALK_RANGE = 2.5f;
static int UseFontStyle = 0, UseFontScale = 0, UseFontColor = 0, UseFontRender = 0, DrawHudOn = 1;
static float HudX = 60.f, HudY = 220.f, HudLine = 34.f, HudScale = 0.9f;
static int   UseFontOrient = 1, FontOrient = 1;     // FontOrient: 0=tengah, 1=kiri, 2=kanan
static int   UseMPKeyboard = 1, AutoOpenKeyboard = 1;   // pinjam keyboard dari libMP32.so
static int   HudAuto = 1, UseFontWrap = 1;          // HudAuto: posisi teks otomatis dari ukuran layar
static int   g_scrW = 0, g_scrH = 0;
static const bool  ENABLE_CRIME = false;          // todong/copet: nyalakan setelah aksi ped selesai dibuat

static void Mark(const std::string& line) {
    LOGI("%s", line.c_str());
    for (const char* sub : {"", "files/"}) {
        std::string f = VIS_DIR + sub + "InteractivePeds_FULL.txt";
        FILE* fp = fopen(f.c_str(), "a");
        if (fp) { fprintf(fp, "%s\n", line.c_str()); fclose(fp); }
    }
}
static std::string GetPackageName() {
    char buf[256] = {0};
    FILE* f = fopen("/proc/self/cmdline", "r");
    if (f) { fread(buf, 1, sizeof buf - 1, f); fclose(f); }
    std::string p = buf;
    return p.empty() ? "com.rockstargames.gtasa" : p;
}
static bool TryWrite(const std::string& path) {
    FILE* f = fopen(path.c_str(), "w");
    if (!f) return false;
    fprintf(f, "[Settings]\nProxyHost=%s\nProxyPort=%s\nTalkRange=%.1f\n"
               "DrawHud=%d\nUseFontStyle=%d\nUseFontScale=%d\nUseFontColor=%d\nUseFontRender=%d\n"
               "HudX=%.0f\nHudY=%.0f\nHudLine=%.0f\nHudScale=%.2f\nUseFontOrient=%d\nFontOrient=%d\nHudAuto=%d\nUseFontWrap=%d\nUseMPKeyboard=%d\nAutoOpenKeyboard=%d\n",
            PROXY_HOST.c_str(), PROXY_PORT.c_str(), TALK_RANGE, DrawHudOn, UseFontStyle, UseFontScale, UseFontColor, UseFontRender,
            HudX, HudY, HudLine, HudScale, UseFontOrient, FontOrient, HudAuto, UseFontWrap, UseMPKeyboard, AutoOpenKeyboard);
    fclose(f);
    return true;
}
static void LoadConfig() {
    PKG = GetPackageName();
    VIS_DIR = "/storage/emulated/0/Android_Unprotected/data/" + PKG + "/";
    { std::string ct = VIS_DIR + "chat.txt"; FILE* t = fopen(ct.c_str(), "r"); if (t) fclose(t); else { t = fopen(ct.c_str(), "w"); if (t) fclose(t); } }
    std::string ini = VIS_DIR + "InteractivePeds.ini";
    FILE* f = fopen(ini.c_str(), "r");
    if (!f) { TryWrite(ini); return; }
    char line[256]; bool hasNew = false, hasKb = false;
    while (fgets(line, sizeof line, f)) {
        char k[64], v[160];
        if (sscanf(line, " %63[^=]=%159[^\r\n]", k, v) == 2) {
            std::string key = k, val = v;
            if (key == "ProxyHost") PROXY_HOST = val;
            else if (key == "ProxyPort") PROXY_PORT = val;
            else if (key == "TalkRange") TALK_RANGE = (float)atof(val.c_str());
            else if (key == "DrawHud")       DrawHudOn = atoi(val.c_str());
            else if (key == "UseFontStyle")  UseFontStyle  = atoi(val.c_str());
            else if (key == "HudX")          HudX = (float)atof(val.c_str());
            else if (key == "HudAuto")       { HudAuto = atoi(val.c_str()); hasNew = true; }
            else if (key == "UseFontWrap")   UseFontWrap = atoi(val.c_str());
            else if (key == "UseMPKeyboard")    { UseMPKeyboard = atoi(val.c_str()); hasKb = true; }
            else if (key == "AutoOpenKeyboard") AutoOpenKeyboard = atoi(val.c_str());
            else if (key == "HudY")          HudY = (float)atof(val.c_str());
            else if (key == "HudLine")       HudLine = (float)atof(val.c_str());
            else if (key == "HudScale")      HudScale = (float)atof(val.c_str());
            else if (key == "UseFontOrient") UseFontOrient = atoi(val.c_str());
            else if (key == "FontOrient")    FontOrient = atoi(val.c_str());
            else if (key == "UseFontScale")  UseFontScale  = atoi(val.c_str());
            else if (key == "UseFontColor")  UseFontColor  = atoi(val.c_str());
            else if (key == "UseFontRender") UseFontRender = atoi(val.c_str());
        }
    }
    fclose(f);
    if (!hasNew || !hasKb) TryWrite(ini);          // ini lama belum punya kunci baru -> tulis ulang lengkap
}

// ============================ Baca memori game dengan aman ============================
// (trik pipe: kalau alamat tidak valid, write() gagal -> nggak crash)
static bool SafeRead(const void* src, void* dst, size_t n) {
    static int fds[2] = {-1, -1};
    if ((uintptr_t)src < 0x10000 || n == 0 || n > 4096) return false;
    if (fds[0] < 0 && pipe(fds) != 0) return false;
    if (write(fds[1], src, n) != (ssize_t)n) return false;
    return read(fds[0], dst, n) == (ssize_t)n;
}

struct CVector { float x, y, z; };
class CPed;

// ============================ Simbol game ============================
static uintptr_t pGTASA; static void* hGTASA;
static CPed* (*FindPlayerPed)(int);
static void  (*Font_Print)(float, float, uint16_t*);
static void  (*Font_SetScale1)(float);
static void  (*Font_SetScale2)(float, float);
static void  (*Font_SetStyleH)(uint8_t);
static void  (*Font_SetColor)(uint32_t);     // CRGBA 4 byte, dioper lewat register
static void  (*Font_Render)();
static void  (*Font_SetOrient)(int);
static void  (*Font_SetWrapx)(float);
static uintptr_t symRsGlobal;
static void* (*Pools_GetPed)(int);
static uintptr_t symPedPool, symTimeStep, symClockHours;
static void  (*Render2D_orig)();

static uintptr_t FirstSym(std::initializer_list<const char*> names, const char** found = nullptr) {
    for (const char* n : names) { uintptr_t a = aml->GetSym(hGTASA, n); if (a) { if (found) *found = n; return a; } }
    return 0;
}

// ============================ Data game ============================
static bool EntityPos(void* e, CVector& o) {
    if (!e) return false;
    uint8_t* p = (uint8_t*)e; uint32_t m = 0; float f[3];
    if (!SafeRead(p + 0x14, &m, 4)) return false;                    // CPlaceable::m_matrix
    bool ok = m ? SafeRead((void*)(uintptr_t)(m + 0x30), f, 12)      // matrix->pos
                : SafeRead(p + 4, f, 12);                            // placement.pos
    if (!ok) return false;
    for (float v : f) if (!std::isfinite(v) || std::fabs(v) > 20000.f) return false;
    o = {f[0], f[1], f[2]};
    return true;
}
static float Game_DT() {
    float st = 1.f;
    if (symTimeStep && SafeRead((void*)symTimeStep, &st, 4) && st > 0 && st < 20) return st / 50.f;
    return 0.016f;
}
static int Game_Hour() {
    uint8_t h = 12;
    if (symClockHours && SafeRead((void*)symClockHours, &h, 1) && h < 24) return h;
    return 12;
}
// Daftar ped hidup (di-cache, di-refresh tiap beberapa frame)
static std::vector<void*> g_peds;
static void RefreshPeds(void* player) {
    g_peds.clear();
    if (!symPedPool || !Pools_GetPed) return;
    uint32_t pool = 0; if (!SafeRead((void*)symPedPool, &pool, 4) || !pool) return;
    uint32_t hdr[3]; if (!SafeRead((void*)(uintptr_t)pool, hdr, 12)) return;   // objects, flags, size
    int size = (int)hdr[2]; if (size <= 0 || size > 1000) return;
    for (int i = 0; i < size; i++) {
        uint8_t fl; if (!SafeRead((void*)(uintptr_t)(hdr[1] + i), &fl, 1)) break;
        if (fl & 0x80) continue;                                    // slot kosong
        void* p = Pools_GetPed((i << 8) | (fl & 0x7F));
        if (p && p != player) g_peds.push_back(p);
    }
}

// Stub yang belum diisi (butuh struktur game yang belum diverifikasi)
static int  Game_PlayerMoney() { return 0; }
static void Game_AddMoney(int) {}
static int  Game_Wanted()      { return 0; }
static bool Game_PlayerArmed() { return false; }
static void Act_AimAtPlayer(void*) {}
static void Act_Flee(void*) {}
static void Act_ShootPlayer(void*) {}
static void Act_PickpocketRun(void*) {}
static void Act_FaceAndStop(void*) {}

// ============================ Teks di layar (font bawaan game) ============================
static int g_crumbs = 0;
static void Crumb(const char* what) {          // jejak sebelum tiap panggilan font; kalau game crash, baris terakhir = pelakunya
    if (g_crumbs >= 60) return;
    g_crumbs++;
    std::string f = VIS_DIR + "InteractivePeds_crumb.txt";
    FILE* fp = fopen(f.c_str(), "a");
    if (fp) { fprintf(fp, "%s\n", what); fclose(fp); }
}
static void DrawHud(const std::string& txt, int line) {
    if (!DrawHudOn || !Font_Print) return;
    Crumb("draw: mulai");
    if (UseFontStyle && Font_SetStyleH) { Crumb("draw: SetFontStyle"); Font_SetStyleH(1); }
    if (UseFontScale) {
        if (Font_SetScale1)      { Crumb("draw: SetScale(1)"); Font_SetScale1(HudScale); }
        else if (Font_SetScale2) { Crumb("draw: SetScale(2)"); Font_SetScale2(HudScale, HudScale * 2.f); }
    }
    bool left = UseFontOrient && Font_SetOrient;
    if (left) { Crumb("draw: SetOrientation"); Font_SetOrient(FontOrient); }
    if (UseFontWrap && Font_SetWrapx) { Crumb("draw: SetWrapx"); Font_SetWrapx(g_scrW > 0 ? (float)g_scrW : 3000.f); }
    if (UseFontColor && Font_SetColor) { Crumb("draw: SetColor"); Font_SetColor(0xFF00DCFF); }
    uint16_t w[128]; size_t i = 0;
    for (; i < txt.size() && i < 127; i++) w[i] = (uint8_t)txt[i];
    w[i] = 0;
    float x = HudX, y = HudY + HudLine * line;
    if (HudAuto && g_scrW > 0 && g_scrH > 0) {                        // posisi otomatis dari ukuran layar
        x = left && FontOrient == 1 ? g_scrW * 0.04f : g_scrW * 0.5f;  // rata kiri -> pinggir kiri; selain itu -> tengah
        y = g_scrH * 0.62f + g_scrH * 0.05f * line;
    }
    Crumb("draw: PrintString");
    Font_Print(x, y, w);
    Crumb("draw: PrintString selesai");
    if (UseFontRender && Font_Render) { Crumb("draw: RenderFontBuffer"); Font_Render(); Crumb("draw: Render selesai"); }
}

// ============================ State obrolan ============================
static BrainRegistry& BR() { static BrainRegistry b; return b; }
#define brain (BR())
static void* talkPed = nullptr; static uint32_t talkId = 0;
static std::string bubbleText; static float bubbleTime = 0;
struct Reply { uint32_t id; std::string text; int dHappy, dAnger, dFear; };
static std::mutex qmx; static std::queue<Reply> replies;

static void LogChat(const std::string& s) {
    std::string f = VIS_DIR + "chat_log.txt";
    FILE* fp = fopen(f.c_str(), "a");
    if (fp) { fprintf(fp, "%s\n", s.c_str()); fclose(fp); }
}

// Kirim ucapan player ke AI (thread terpisah). Balasan masuk lewat antrean `replies`.
static void SendChat(const std::string& said) {
    if (!talkPed || said.empty()) return;
    PedMind& m = brain.get(talkId);
    m.remember("P", said); m.timesTalked++;
    std::string prompt = brain.buildPrompt(m, said, Game_PlayerMoney(), Game_Hour());
    uint32_t id = talkId; PedMind snap = m;
    bubbleText = m.name + ": ..."; bubbleTime = 15;
    LogChat("Player: " + said);
    std::string host = PROXY_HOST, port = PROXY_PORT;
    std::thread([id, prompt, said, snap, host, port]() {
        std::string out; Reply r{id, "", 0, 0, 0};
        if (http_post(host, port, "/chat", prompt, out)) {
            size_t nl = out.find('\n');
            if (nl != std::string::npos) { sscanf(out.substr(0, nl).c_str(), "%d,%d,%d", &r.dHappy, &r.dAnger, &r.dFear); r.text = out.substr(nl + 1); }
            else r.text = out;
        } else { BrainRegistry tmp; r.text = tmp.offlineChat(snap, said, r.dHappy, r.dAnger, r.dFear); }   // offline cerdas
        std::lock_guard<std::mutex> g(qmx); replies.push(r);
    }).detach();
}

// Input sementara: tulis pesan di file chat.txt (folder Android_Unprotected/data/<game>/), simpan, lalu dekati ped.
static void PollChatFile() {
    if (!talkPed) return;
    std::string f = VIS_DIR + "chat.txt";
    FILE* fp = fopen(f.c_str(), "r"); if (!fp) return;
    char buf[200] = {0}; size_t n = fread(buf, 1, sizeof buf - 1, fp); fclose(fp);
    std::string said(buf, n);
    while (!said.empty() && (said.back() == '\n' || said.back() == '\r' || said.back() == ' ')) said.pop_back();
    if (said.empty()) return;
    fp = fopen(f.c_str(), "w"); if (fp) fclose(fp);                  // kosongkan lagi
    SendChat(said);
}


// ============================ Keyboard pinjaman dari mod multiplayer (libMP32.so) ============================
// Simbol hasil dump: VKeyboard::Open / IsOpen / Close. Dugaan: fungsi statis (tanpa "this"); jejak crash ada di crumb.txt.
static bool (*VK_IsOpen)();
static void (*VK_Open)(const char*, const char*, int, void (*)(const char*, void*), void*, bool);
static void (*VK_Close)();
static std::mutex kbMx; static std::string kbSaid; static bool kbDone = false, kbCancelled = false;
static bool kbArmed = true; static int kbOpenedFrame = -100000; static float kbRearm = 0;
static int g_kbCrumbs = 0;
static void KbCrumb(const char* what) {
    if (g_kbCrumbs++ >= 25) return;
    std::string f = VIS_DIR + "InteractivePeds_crumb.txt";
    FILE* fp = fopen(f.c_str(), "a"); if (fp) { fprintf(fp, "%s\n", what); fclose(fp); }
}
static void OnKeyboardDone(const char* text, void*) {          // dipanggil mod MP saat lu tekan kirim / batal
    std::lock_guard<std::mutex> g(kbMx);
    if (text && *text) kbSaid = std::string(text).substr(0, 180); else kbCancelled = true;
    kbDone = true;
}
static void ResolveMPKeyboard() {
    if (VK_Open) return;
    void* h = aml->GetLibHandle("libMP32.so");
    if (!h) h = dlopen("libMP32.so", RTLD_NOW | RTLD_NOLOAD);
    if (!h) { Mark("MP32: library tidak ditemukan (keyboard pinjaman mati)"); return; }
    uintptr_t a = aml->GetSym(h, "_ZN9VKeyboard4OpenEPKcS1_iPFvS1_PvES2_b");
    uintptr_t b = aml->GetSym(h, "_ZN9VKeyboard6IsOpenEv");
    uintptr_t c = aml->GetSym(h, "_ZN9VKeyboard5CloseEv");
    Mark(std::string("MP32 keyboard: Open=") + (a ? "ADA" : "TIDAK") + " IsOpen=" + (b ? "ADA" : "TIDAK") + " Close=" + (c ? "ADA" : "TIDAK"));
    if (a && b) { SET_TO(VK_Open, a); SET_TO(VK_IsOpen, b); SET_TO(VK_Close, c); }
}

// ============================ Loop per frame (hook CHud::Draw) ============================
static int g_frame = 0, g_logs = 0;
static std::vector<std::string> g_hudLines;

static void Render2D_hook() {
    Render2D_orig();                                                 // HUD asli dulu
    g_frame++;
    float dt = Game_DT();
    brain.tick(dt);
    if (!FindPlayerPed) return;
    CPed* player = FindPlayerPed(-1);
    CVector pp;
    if (!player || !EntityPos(player, pp)) {
        if (g_frame % 300 == 1 && g_logs++ < 12) Mark("FRAME " + std::to_string(g_frame) + ": player/posisi tidak terbaca");
        return;
    }
    if (g_frame % 5 == 0) RefreshPeds(player);

    // ped terdekat
    void* nearest = nullptr; float best = 1e9f;
    for (void* p : g_peds) {
        CVector q; if (!EntityPos(p, q)) continue;
        float d = std::hypot(q.x - pp.x, q.y - pp.y);
        if (d < best) { best = d; nearest = p; }
        if (g_frame % 5 == 0 && ENABLE_CRIME) { /* inisiatif ped: lihat DoAction di versi berikut */ }
    }
    if (nearest && best < 8.f && g_frame % 600 == 0) {              // sapaan/olokan spontan (teks saja)
        PedMind& m = brain.get((uint32_t)(uintptr_t)nearest);
        Act a = brain.decide(m, best, 0, 0, false);
        if (a == Act::Greet || a == Act::Insult) {
            talkPed = nearest; talkId = m.id;
            bubbleText = m.name + ": " + brain.offlineLine(m, a, ""); bubbleTime = 6;
            LogChat(bubbleText);
        }
    }
    bool canTalk = nearest && best < TALK_RANGE;
    if (canTalk && talkPed != nearest) { talkPed = nearest; talkId = (uint32_t)(uintptr_t)nearest;
        PedMind& m = brain.get(talkId); bubbleText = m.name + (m.knowsPlayer ? ": Oh, lu lagi." : ": Ya?"); bubbleTime = 4; }
    if (!canTalk && talkPed && bubbleTime <= 0) {                    // pergi = obrolan selesai, ped ingat player
        PedMind& m = brain.get(talkId); if (m.timesTalked > 0) m.knowsPlayer = true;
        talkPed = nullptr;
    }

    // keyboard in-game (pinjam dari libMP32.so)
    if (UseMPKeyboard) {
        if (!VK_Open) ResolveMPKeyboard();
        if (VK_Open && VK_IsOpen) {
            KbCrumb("kb: IsOpen"); bool kbOpen = VK_IsOpen();
            { std::lock_guard<std::mutex> g(kbMx);
              if (kbDone) {
                  kbDone = false;
                  if (!kbSaid.empty()) { std::string said = kbSaid; kbSaid.clear(); if (talkPed) SendChat(said); kbRearm = 6.f; }   // terkirim -> boleh ngobrol lagi 6 detik lagi
                  else if (kbCancelled) { kbCancelled = false; kbRearm = 0; }                                                       // batal -> tunggu player menjauh
              } }
            if (canTalk && AutoOpenKeyboard && kbArmed && !kbOpen && g_frame - kbOpenedFrame > 120) {
                PedMind& pm = brain.get(talkId);
                std::string title = "Ngobrol dengan " + pm.name;
                KbCrumb("kb: Open"); VK_Open(title.c_str(), "", 120, OnKeyboardDone, nullptr, false); KbCrumb("kb: Open selesai");
                kbArmed = false; kbOpenedFrame = g_frame;
            }
            if (!canTalk && best > TALK_RANGE + 3.f) kbArmed = true;
            if (kbRearm > 0) { kbRearm -= dt; if (kbRearm <= 0) kbArmed = true; }
        }
    }

    // balasan AI
    { std::lock_guard<std::mutex> g(qmx);
      while (!replies.empty()) {
          Reply r = replies.front(); replies.pop();
          PedMind& m = brain.get(r.id);
          m.happy += r.dHappy; m.anger += r.dAnger; m.fear += r.dFear; m.clamp();
          m.remember("N", r.text);
          bubbleText = m.name + ": " + r.text; bubbleTime = 10;
          LogChat(bubbleText);
      } }
    if (g_frame % 45 == 0) PollChatFile();

    // gambar
    int line = 0;
    if (canTalk) DrawHud("[ CHAT ]  tulis di chat.txt lalu simpan", line++);
    if (bubbleTime > 0) { DrawHud(bubbleText, line++); bubbleTime -= dt; }

    // log bukti (dibatasi supaya file nggak membengkak)
    if (g_frame % 300 == 1 && g_logs < 12) {
        g_logs++;
        char b[200]; snprintf(b, sizeof b, "FRAME %d: player=(%.0f,%.0f,%.0f) ped=%d terdekat=%.1fm jam=%d",
                              g_frame, pp.x, pp.y, pp.z, (int)g_peds.size(), best > 1e8f ? -1.f : best, Game_Hour());
        Mark(b);
    }
}

// ============================ Laporan simbol ============================
static void Report(const char* label, const char* found) { Mark(std::string(found ? "ADA   : " : "TIDAK : ") + label + (found ? std::string(" -> ") + found : "")); }


// ============================ Dump nama fungsi libGTASA (buat cari fungsi touch/keyboard) ============================
// Membaca tabel simbol libGTASA.so dari disk, lalu menulis yang berkaitan dengan input ke InteractivePeds_symbols.txt
static void DumpSymbols(const char* lib, const char* outName, std::vector<const char*> kws) {
    std::string out = VIS_DIR + outName;
    { FILE* t = fopen(out.c_str(), "r"); if (t) { fseek(t, 0, SEEK_END); long sz = ftell(t); fclose(t); if (sz > 1000) return; } }   // sudah berisi -> lewati
    std::string so;
    FILE* m = fopen("/proc/self/maps", "r"); char l[600];
    while (m && fgets(l, sizeof l, m)) {
        if (strstr(l, lib)) { char* p = strchr(l, '/'); if (p) { so = p; while (!so.empty() && (so.back() == '\n' || so.back() == ' ')) so.pop_back(); break; } }
    }
    if (m) fclose(m);
    FILE* o = fopen(out.c_str(), "w"); if (!o) return;
    fprintf(o, "%s path: %s\n", lib, so.c_str());
    // File di /data/user/0/... sering sudah dihapus loader ("(deleted)"); coba salinan asli di folder mods juga
    size_t del = so.find(" (deleted)"); if (del != std::string::npos) so.erase(del);
    std::vector<std::string> cands;
    if (!so.empty()) cands.push_back(so);
    cands.push_back(VIS_DIR + "mods/" + lib);
    cands.push_back("/storage/emulated/0/Android/data/" + PKG + "/mods/" + lib);
    FILE* f = nullptr; Elf32_Ehdr eh; bool okElf = false;
    for (auto& c : cands) {
        f = fopen(c.c_str(), "rb");
        if (!f) { fprintf(o, "tidak bisa buka: %s\n", c.c_str()); continue; }
        if (fread(&eh, sizeof eh, 1, f) == 1 && memcmp(eh.e_ident, ELFMAG, SELFMAG) == 0 && eh.e_shnum > 0 && eh.e_shnum <= 200) { okElf = true; fprintf(o, "dibaca dari: %s\n", c.c_str()); break; }
        fprintf(o, "bukan ELF / tanpa section header: %s\n", c.c_str());
        fclose(f); f = nullptr;
    }
    if (!okElf) { fprintf(o, "GAGAL baca ELF dari semua lokasi\n"); fclose(o); return; }
    std::vector<Elf32_Shdr> sh(eh.e_shnum);
    fseek(f, eh.e_shoff, SEEK_SET);
    if (fread(sh.data(), sizeof(Elf32_Shdr), eh.e_shnum, f) != eh.e_shnum) { fprintf(o, "GAGAL baca section\n"); fclose(f); fclose(o); return; }
    int total = 0, written = 0;
    for (auto& s : sh) {
        if (s.sh_type != SHT_DYNSYM || s.sh_link >= sh.size()) continue;
        Elf32_Shdr& st = sh[s.sh_link];
        std::vector<Elf32_Sym> syms(s.sh_size / sizeof(Elf32_Sym));
        std::vector<char> str(st.sh_size + 1, 0);
        fseek(f, s.sh_offset, SEEK_SET); if (fread(syms.data(), sizeof(Elf32_Sym), syms.size(), f) != syms.size()) break;
        fseek(f, st.sh_offset, SEEK_SET); if (fread(str.data(), 1, st.sh_size, f) != st.sh_size) break;
        for (auto& sy : syms) {
            if (sy.st_shndx == SHN_UNDEF || sy.st_name >= st.sh_size) continue;
            const char* n = &str[sy.st_name]; total++;
            bool hit = false;
            for (const char* k : kws) if (strstr(n, k)) { hit = true; break; }
            if (hit && written++ < 4000) fprintf(o, "%s | +0x%x\n", n, (unsigned)sy.st_value);
        }
    }
    fprintf(o, "TOTAL simbol: %d, ditulis: %d\n", total, written);
    fclose(f); fclose(o);
}

// ============================ Entry AML ============================
extern "C" void OnModPreLoad() { LoadConfig(); Mark("1. OnModPreLoad"); }
extern "C" void OnAllModsLoaded() {
    Mark("5. OnAllModsLoaded");
    if (UseMPKeyboard) ResolveMPKeyboard();
    // Mod multiplayer (libMP32.so) baru termuat SETELAH mod kita, jadi dicek di sini
    std::thread([]() {
        DumpSymbols("libMP32.so", "InteractivePeds_symbols_MP32.txt", {"Keyboard", "KeyBoard", "Chat", "Input", "Say", "Send", "Command", "Cmd", "Edit", "Key", "Text", "Message", "Msg"});
    }).detach();
}

extern "C" void OnModLoad() {
    Mark("2. OnModLoad mulai (v0.5)");
    pGTASA = aml->GetLib("libGTASA.so"); hGTASA = aml->GetLibHandle("libGTASA.so");
    const char* nm = nullptr;
    SET_TO(FindPlayerPed, FirstSym({"_Z13FindPlayerPedi"}, &nm));                  Report("FindPlayerPed", nm); nm = nullptr;
    SET_TO(Font_Print,    FirstSym({"_ZN5CFont11PrintStringEffPt"}, &nm));          Report("CFont::PrintString", nm); nm = nullptr;
    SET_TO(Font_SetScale1,FirstSym({"_ZN5CFont8SetScaleEf"}, &nm));                 Report("CFont::SetScale(float)", nm); nm = nullptr;
    SET_TO(Font_SetScale2,FirstSym({"_ZN5CFont8SetScaleEff"}, &nm));                Report("CFont::SetScale(float,float)", nm); nm = nullptr;
    SET_TO(Font_SetStyleH,FirstSym({"_ZN5CFont11SetFontStyleEh", "_ZN5CFont11SetFontStyleEs"}, &nm)); Report("CFont::SetFontStyle", nm); nm = nullptr;
    SET_TO(Font_SetColor, FirstSym({"_ZN5CFont8SetColorE5CRGBA"}, &nm));            Report("CFont::SetColor", nm); nm = nullptr;
    SET_TO(Font_Render,   FirstSym({"_ZN5CFont16RenderFontBufferEv"}, &nm));        Report("CFont::RenderFontBuffer", nm); nm = nullptr;
    SET_TO(Font_SetOrient,FirstSym({"_ZN5CFont14SetOrientationEh", "_ZN5CFont14SetOrientationEi", "_ZN5CFont14SetOrientationE14eFontAlignment", "_ZN5CFont14SetOrientationEs"}, &nm)); Report("CFont::SetOrientation", nm); nm = nullptr;
    SET_TO(Font_SetWrapx, FirstSym({"_ZN5CFont8SetWrapxEf"}, &nm));                Report("CFont::SetWrapx", nm); nm = nullptr;
    symRsGlobal = FirstSym({"RsGlobal"}, &nm);                                      Report("RsGlobal", nm); nm = nullptr;
    if (symRsGlobal) {
        uint32_t w = 0, h = 0;
        if (SafeRead((void*)(symRsGlobal + 8), &w, 4) && SafeRead((void*)(symRsGlobal + 12), &h, 4) && w >= 300 && w <= 10000 && h >= 200 && h <= 10000) { g_scrW = (int)w; g_scrH = (int)h; }
        Mark("layar: " + std::to_string(g_scrW) + "x" + std::to_string(g_scrH) + (g_scrW ? "" : " (tidak terbaca, pakai HudX/HudY)"));
    }
    SET_TO(Pools_GetPed,  FirstSym({"_ZN6CPools6GetPedEi"}, &nm));                  Report("CPools::GetPed", nm); nm = nullptr;
    symPedPool    = FirstSym({"_ZN6CPools11ms_pPedPoolE"}, &nm);                    Report("CPools::ms_pPedPool", nm); nm = nullptr;
    symTimeStep   = FirstSym({"_ZN6CTimer12ms_fTimeStepE"}, &nm);                   Report("CTimer::ms_fTimeStep", nm); nm = nullptr;
    symClockHours = FirstSym({"_ZN6CClock18ms_nGameClockHoursE"}, &nm);             Report("CClock::ms_nGameClockHours", nm); nm = nullptr;
    uintptr_t hud = FirstSym({"_ZN4CHud4DrawEv"}, &nm);                             Report("CHud::Draw", nm);
    if (hud) aml->Hook((void*)hud, (void*)Render2D_hook, (void**)&Render2D_orig);
    Mark("3. hook dipasang: " + std::string(hud ? "YA" : "TIDAK"));
    std::thread([]() {
        DumpSymbols("libGTASA.so", "InteractivePeds_symbols.txt", {"Touch", "Keyboard", "KeyBoard", "AND_", "OS_", "Widget", "CPad", "RsGlobal"});
    }).detach();
    Mark("4. OnModLoad selesai");
}
