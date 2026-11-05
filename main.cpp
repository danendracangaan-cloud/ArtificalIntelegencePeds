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
#include <fcntl.h>
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
static float HudYFrac = 0.28f;                           // 0.0 = atas layar, 1.0 = bawah (default di atas biar nggak ketutup keyboard)
static int   UseMPKeyboard = 1, AutoOpenKeyboard = 0;      // AutoOpenKeyboard=0: keyboard dibuka manual lewat tombol chat
static int   UseMPChatTrigger = 1, PassChatToMP = 0, DrawBeforeHud = 1;
static int   FontSetup = 1;                                // 1 = set semua setelan font sendiri tiap kali menggambar (font tidak berubah-ubah)
static int   UseDeathCheck = 1, HealthOffset = 0x540;      // chat otomatis hilang kalau ped mati (offset darah = dugaan dari struktur PC)   // pinjam keyboard dari libMP32.so
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
               "HudX=%.0f\nHudY=%.0f\nHudLine=%.0f\nHudScale=%.2f\nUseFontOrient=%d\nFontOrient=%d\nHudAuto=%d\nUseFontWrap=%d\nUseMPKeyboard=%d\nKeyboardAuto=%d\nHudYFrac=%.2f\nUseMPChatTrigger=%d\nPassChatToMP=%d\nDrawBeforeHud=%d\nUseDeathCheck=%d\nHealthOffset=%d\nFontSetup=%d\n",
            PROXY_HOST.c_str(), PROXY_PORT.c_str(), TALK_RANGE, DrawHudOn, UseFontStyle, UseFontScale, UseFontColor, UseFontRender,
            HudX, HudY, HudLine, HudScale, UseFontOrient, FontOrient, HudAuto, UseFontWrap, UseMPKeyboard, AutoOpenKeyboard, HudYFrac, UseMPChatTrigger, PassChatToMP, DrawBeforeHud, UseDeathCheck, HealthOffset, FontSetup);
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
    char line[256]; bool hasNew = false, hasKb = false, hasY = false, hasTrig = false, hasDeath = false, hasFont = false;
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
            else if (key == "KeyboardAuto")     AutoOpenKeyboard = atoi(val.c_str());
            else if (key == "UseMPChatTrigger") { UseMPChatTrigger = atoi(val.c_str()); hasTrig = true; }
            else if (key == "PassChatToMP")     PassChatToMP = atoi(val.c_str());
            else if (key == "DrawBeforeHud")    DrawBeforeHud = atoi(val.c_str());
            else if (key == "UseDeathCheck")    { UseDeathCheck = atoi(val.c_str()); hasDeath = true; }
            else if (key == "HealthOffset")     HealthOffset = atoi(val.c_str());
            else if (key == "FontSetup")        { FontSetup = atoi(val.c_str()); hasFont = true; }
            else if (key == "HudYFrac")         { HudYFrac = (float)atof(val.c_str()); hasY = true; }
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
    if (!hasNew || !hasKb || !hasY || !hasTrig || !hasDeath || !hasFont) TryWrite(ini);          // ini lama belum punya kunci baru -> tulis ulang lengkap
}

// ============================ Baca memori game dengan aman ============================
// (trik pipe: kalau alamat tidak valid, write() gagal -> nggak crash)
static bool SafeRead(const void* src, void* dst, size_t n) {
    static int fds[2] = {-1, -1};
    if ((uintptr_t)src < 0x10000 || n == 0 || n > 4096) return false;
    if (fds[0] < 0) {
        if (pipe(fds) != 0) return false;
        for (int i = 0; i < 2; i++) fcntl(fds[i], F_SETFL, fcntl(fds[i], F_GETFL) | O_NONBLOCK);   // jangan pernah nge-hang
    }
    ssize_t w = write(fds[1], src, n);
    if (w != (ssize_t)n) {                                           // gagal/sebagian: kuras sisa di pipe supaya bacaan berikutnya tidak korup
        char tmp[4096];
        while (read(fds[0], tmp, sizeof tmp) > 0) {}
        return false;
    }
    ssize_t r = read(fds[0], dst, n);
    if (r != (ssize_t)n) { char tmp[4096]; while (read(fds[0], tmp, sizeof tmp) > 0) {} return false; }
    return true;
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

static void Act_ShootPlayer(void*) {}
static void Act_PickpocketRun(void*) {}
static int g_stubLogs = 0;
static void StubLog(const char* what) { if (g_stubLogs++ < 40) Mark(std::string("AKSI (belum terhubung ke game): ") + what); }
static void Act_Flee(void*)         { StubLog("flee"); }
static void Act_FaceAndStop(void*)  { StubLog("hadap player + diam"); }
static void Act_TalkGesture(void*, bool on) { StubLog(on ? "gesture bicara ON" : "gesture bicara OFF"); }
static void Act_Release(void*)      { StubLog("lepas ped (lanjut aktivitas)"); }
static void Act_Follow(void*)       { StubLog("follow"); }
static void Act_Stop(void*)         { StubLog("stop/diam"); }
static void Act_Leave(void*)        { StubLog("pergi"); }
static void Act_Dance(void*)        { StubLog("dance"); }
static void Act_HandsUp(void*)      { StubLog("angkat tangan"); }
static void Act_Wave(void*)         { StubLog("melambai"); }

// ============================ Teks di layar (font bawaan game) ============================

// ============================ Setup font eksplisit ============================
// Nama fungsi CFont dibaca dari tabel simbol libGTASA.so; jumlah/tipe argumen dibaca dari nama (mangled), jadi tidak menebak.
static void (*F_Style)(int);      static void (*F_Scale1)(float);  static void (*F_Scale2)(float, float);
static void (*F_Orient)(int);     static void (*F_Wrap)(float);     static void (*F_Prop)(int);
static void (*F_Back2)(int, int); static void (*F_Justify)(int);   static void (*F_Shadow)(int);
static bool g_fontReady = false;

static bool IntLike(const std::string& a) { return a.size() == 1 && strchr("hstijcal", a[0]) != nullptr; }
static void LoadCFont() {
    std::string so; FILE* mp = fopen("/proc/self/maps", "r"); char l[600];
    while (mp && fgets(l, sizeof l, mp)) if (strstr(l, "libGTASA.so")) { char* p = strchr(l, '/'); if (p) { so = p; while (!so.empty() && (so.back() == '\n' || so.back() == ' ')) so.pop_back(); break; } }
    if (mp) fclose(mp);
    size_t del = so.find(" (deleted)"); if (del != std::string::npos) so.erase(del);
    FILE* f = so.empty() ? nullptr : fopen(so.c_str(), "rb");
    Elf32_Ehdr eh;
    if (!f || fread(&eh, sizeof eh, 1, f) != 1 || memcmp(eh.e_ident, ELFMAG, SELFMAG) != 0 || eh.e_shnum == 0 || eh.e_shnum > 200) { if (f) fclose(f); Mark("FONT: gagal baca tabel simbol libGTASA"); return; }
    std::vector<Elf32_Shdr> sh(eh.e_shnum);
    fseek(f, eh.e_shoff, SEEK_SET);
    if (fread(sh.data(), sizeof(Elf32_Shdr), eh.e_shnum, f) != eh.e_shnum) { fclose(f); return; }
    std::vector<std::string> names;
    for (auto& s : sh) {
        if (s.sh_type != SHT_DYNSYM || s.sh_link >= sh.size()) continue;
        Elf32_Shdr& st = sh[s.sh_link];
        std::vector<Elf32_Sym> syms(s.sh_size / sizeof(Elf32_Sym)); std::vector<char> str(st.sh_size + 1, 0);
        fseek(f, s.sh_offset, SEEK_SET); if (fread(syms.data(), sizeof(Elf32_Sym), syms.size(), f) != syms.size()) break;
        fseek(f, st.sh_offset, SEEK_SET); if (fread(str.data(), 1, st.sh_size, f) != st.sh_size) break;
        for (auto& sy : syms) {
            if (sy.st_shndx == SHN_UNDEF || sy.st_name >= st.sh_size) continue;
            const char* n = &str[sy.st_name];
            if (strncmp(n, "_ZN5CFont", 9) == 0) names.push_back(n);
        }
    }
    fclose(f);
    {   std::string out = VIS_DIR + "InteractivePeds_symbols_FONT.txt"; FILE* o = fopen(out.c_str(), "w");
        if (o) { for (auto& n : names) fprintf(o, "%s\n", n.c_str()); fclose(o); } }
    auto find = [&](const char* base, std::string& args) -> uintptr_t {
        std::string pre = std::string("_ZN5CFont") + std::to_string(strlen(base)) + base + "E";
        for (auto& n : names) if (n.compare(0, pre.size(), pre) == 0) { args = n.substr(pre.size()); uintptr_t a = aml->GetSym(hGTASA, n.c_str()); if (a) { Mark("FONT: " + std::string(base) + " -> " + n); return a; } }
        Mark(std::string("FONT: ") + base + " TIDAK ADA"); return 0;
    };
    std::string a;
    if (uintptr_t p = find("SetFontStyle", a);       p && (IntLike(a) || a == "14eFontStyle")) SET_TO(F_Style, p);
    if (uintptr_t p = find("SetScale", a);           p) { if (a == "ff") SET_TO(F_Scale2, p); else if (a == "f") SET_TO(F_Scale1, p); }
    if (uintptr_t p = find("SetOrientation", a);     p && (IntLike(a) || a == "14eFontAlignment")) SET_TO(F_Orient, p);
    if (uintptr_t p = find("SetWrapx", a);           p && a == "f")  SET_TO(F_Wrap, p);
    if (uintptr_t p = find("SetProportional", a);    p && a == "b")  SET_TO(F_Prop, p);
    if (uintptr_t p = find("SetBackground", a);      p && a == "bb") SET_TO(F_Back2, p);
    if (uintptr_t p = find("SetJustify", a);         p && a == "b")  SET_TO(F_Justify, p);
    if (uintptr_t p = find("SetDropShadowPosition", a); p && IntLike(a)) SET_TO(F_Shadow, p);
    g_fontReady = F_Style || F_Scale1 || F_Scale2 || F_Orient || F_Wrap;
    Mark(std::string("FONT: setup eksplisit ") + (g_fontReady ? "SIAP" : "TIDAK SIAP (pakai cara lama)"));
}

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
    bool left = false;
    if (FontSetup && g_fontReady) {                                   // semua setelan di-set ulang tiap gambar -> tampilan font selalu sama
        float k = g_scrH > 0 ? g_scrH / 448.f : 1.f;
        if (F_Prop)    { Crumb("font: Proportional"); F_Prop(1); }
        if (F_Back2)   { Crumb("font: Background");   F_Back2(0, 0); }
        if (F_Justify) { Crumb("font: Justify");      F_Justify(0); }
        if (F_Style)   { Crumb("font: Style");        F_Style(1); }
        if (F_Scale2)      { Crumb("font: Scale2"); F_Scale2(0.72f * k * HudScale, 1.48f * k * HudScale); }
        else if (F_Scale1) { Crumb("font: Scale1"); F_Scale1(1.48f * k * HudScale); }
        if (F_Orient && UseFontOrient) { Crumb("font: Orient"); F_Orient(FontOrient); left = true; }
        if (F_Wrap)    { Crumb("font: Wrap"); F_Wrap(g_scrW > 0 ? (float)g_scrW : 3000.f); }
        if (F_Shadow)  { Crumb("font: Shadow"); F_Shadow(1); }
    } else {                                                          // cara lama (kalau FontSetup=0 atau fungsi tidak ketemu)
        if (UseFontStyle && Font_SetStyleH) { Crumb("draw: SetFontStyle"); Font_SetStyleH(1); }
        if (UseFontScale) {
            if (Font_SetScale1)      { Crumb("draw: SetScale(1)"); Font_SetScale1(HudScale); }
            else if (Font_SetScale2) { Crumb("draw: SetScale(2)"); Font_SetScale2(HudScale, HudScale * 2.f); }
        }
        left = UseFontOrient && Font_SetOrient;
        if (left) { Crumb("draw: SetOrientation"); Font_SetOrient(FontOrient); }
        if (UseFontWrap && Font_SetWrapx) { Crumb("draw: SetWrapx"); Font_SetWrapx(g_scrW > 0 ? (float)g_scrW : 3000.f); }
        if (UseFontColor && Font_SetColor) { Crumb("draw: SetColor"); Font_SetColor(0xFF00DCFF); }
    }
    uint16_t w[128]; size_t i = 0;
    {   // UTF-8 -> huruf dasar (font game belum tentu punya aksen)
        static const char* lat = "AAAAAAACEEEEIIIIDNOOOOOxOUUUUYTsaaaaaaaceeeeiiiidnooooo/ouuuuyty";
        for (size_t k = 0; k < txt.size() && i < 127; ) {
            unsigned char c = (unsigned char)txt[k]; uint32_t cp = c; size_t len = 1;
            if (c >= 0xF0) { len = 4; cp = c & 7; } else if (c >= 0xE0) { len = 3; cp = c & 15; } else if (c >= 0xC0) { len = 2; cp = c & 31; }
            for (size_t j = 1; j < len && k + j < txt.size(); j++) cp = (cp << 6) | ((unsigned char)txt[k + j] & 63);
            k += len;
            if (cp == 0xBF) cp = '?'; else if (cp == 0xA1) cp = '!';
            else if (cp >= 0xC0 && cp <= 0xFF) cp = (unsigned char)lat[cp - 0xC0];
            else if (cp == 0x2019 || cp == 0x2018) cp = '\'';
            else if (cp == 0x201C || cp == 0x201D) cp = '"';
            else if (cp > 126 || (cp < 32 && cp != 0)) cp = '?';
            w[i++] = (uint16_t)cp;
        }
    }
    w[i] = 0;
    float x = HudX, y = HudY + HudLine * line;
    if (HudAuto && g_scrW > 0 && g_scrH > 0) {                        // posisi otomatis dari ukuran layar
        x = left && FontOrient == 1 ? g_scrW * 0.04f : g_scrW * 0.5f;  // rata kiri -> pinggir kiri; selain itu -> tengah
        y = g_scrH * HudYFrac + g_scrH * 0.065f * line;
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
static bool g_waiting = false; static float g_waitT = 0;      // menunggu balasan AI
static bool g_kbOpen = false;
struct Reply { uint32_t id; std::string text; int dHappy, dAnger, dFear; std::string action; };
static std::mutex qmx; static std::queue<Reply> replies;


// ---- Gender ped dari ID skin (cowok -> nama cowok, cewek -> nama cewek) ----
static int ReadModel(void* ped) {                                    // CEntity::m_nModelIndex (offset 0x22, dugaan dari struktur PC)
    uint16_t mdl = 0xFFFF;
    if (!ped || !SafeRead((uint8_t*)ped + 0x22, &mdl, 2) || mdl > 20000) return -1;
    return (int)mdl;
}
static int g_genderLogs = 0;
static CVector g_playerPos = {0, 0, 0}; static bool g_playerPosOk = false;
static int g_playerModel = -1;                                       // skin player (0 = CJ)
static std::unordered_map<void*, float> g_lastHealth;              // darah terakhir yang masuk akal per ped
static PedMind& MindOf(void* ped) {
    uint32_t id = (uint32_t)(uintptr_t)ped;
    int model = ReadModel(ped);
    auto it = brain.minds.find(id);
    if (it != brain.minds.end() && model >= 0 && it->second.model != model) { brain.minds.erase(it); g_lastHealth.erase(ped); }   // alamat dipakai ulang oleh ped lain
    bool isNew = brain.minds.find(id) == brain.minds.end();
    brain.genderHint = Vocab::GenderOfSkin(model); brain.modelHint = model;
    int pg = Vocab::GangOfSkin(g_playerModel); if (pg == Vocab::G_NONE) pg = Vocab::G_GSF;        // CJ / skin biasa dianggap Grove Street
    int gang = Vocab::GangOfSkin(model);
    brain.gangHint = gang; brain.relHint = Vocab::Relation(gang, pg);
    brain.pnameHint = (g_playerModel == 0 || g_playerModel < 0) ? "CJ" : "homie";
    PedMind& m = brain.get(id);
    if (isNew && g_genderLogs++ < 30)
        Mark("PED baru: skin=" + std::to_string(model) + " gender=" + (m.gender == 2 ? "cewek" : m.gender == 1 ? "cowok" : "?") +
             " geng=" + (gang ? Vocab::GangName(gang) : "-") + " hubungan=" + std::to_string(m.relation) + " nama=" + m.name);
    return m;
}


// ---- Deteksi ped mati (darah <= 0). Baru dipercaya setelah offset terbukti masuk akal (>=3 ped dengan darah 1..400). ----
static int g_healthSeen = 0, g_healthLogs = 0, g_hurtLogs = 0;
static bool g_healthCalibrated = false;

// Ped/player kena pukul -> ped itu marah selama 60 detik (chat berubah jadi bentakan, bukan sapaan)
static void OnPedHurt(void* ped) {
    CVector q;
    if (!g_playerPosOk || !EntityPos(ped, q) || std::hypot(q.x - g_playerPos.x, q.y - g_playerPos.y) > 4.5f) return;
    PedMind& pm = MindOf(ped);
    if (pm.aggroT <= 0 && g_hurtLogs++ < 25) Mark("PED KENA PUKUL -> marah: " + pm.name);
    brain.provoke(pm);
}

static bool IsDead(void* ped) {
    if (!UseDeathCheck || !ped) return false;
    float h = 0;
    if (!SafeRead((uint8_t*)ped + HealthOffset, &h, 4) || !std::isfinite(h)) return false;
    if (h > 1.f && h < 400.f) {
        auto it0 = g_lastHealth.find(ped);
        if (it0 != g_lastHealth.end() && h < it0->second - 0.5f) OnPedHurt(ped);          // darah turun = kena pukul/tembak
        if (g_lastHealth.size() > 600) g_lastHealth.clear();
        g_lastHealth[ped] = h;
        if (g_healthSeen < 50) g_healthSeen++;
        if (g_healthLogs++ < 6) { char b[96]; snprintf(b, sizeof b, "Darah ped terbaca: %.0f (offset 0x%x)", h, HealthOffset); Mark(b); }
        return false;
    }
    // dianggap mati hanya kalau ped ini PERNAH terbaca hidup (darah > 1) lalu turun ke <= 0 (hindari salah deteksi kalau offset ngawur)
    auto it = g_lastHealth.find(ped);
    return h <= 0.5f && g_healthSeen >= 3 && it != g_lastHealth.end() && it->second > 1.f;
}

// ---- Kalibrasi otomatis offset darah: cari float yang awalnya 100.0 pada banyak ped dan pernah TURUN (kena pukul) ----
static const int CAL_BASE = 0x400, CAL_N = 192;
struct CalCand { int init100 = 0, drops = 0; };
static CalCand g_cal[CAL_N];
static std::unordered_map<void*, std::vector<float>> g_calPrev;
static void CalibrateHealth(void* ped) {
    if (g_healthCalibrated || !ped) return;
    float cur[CAL_N];
    if (!SafeRead((uint8_t*)ped + CAL_BASE, cur, sizeof cur)) return;
    for (int i = 0; i < CAL_N; i++) if (!std::isfinite(cur[i])) cur[i] = 0.f;
    auto it = g_calPrev.find(ped);
    if (it == g_calPrev.end()) {
        if (g_calPrev.size() > 300) g_calPrev.clear();
        for (int i = 0; i < CAL_N; i++) if (std::fabs(cur[i] - 100.f) < 0.01f) g_cal[i].init100++;
        g_calPrev[ped].assign(cur, cur + CAL_N);
    } else {
        for (int i = 0; i < CAL_N; i++) {
            float p = it->second[i];
            if (p > 1.f && p < 400.f && cur[i] < p - 0.5f && cur[i] > -400.f && cur[i] < 400.f) g_cal[i].drops++;
        }
        it->second.assign(cur, cur + CAL_N);
    }
    int best = -1;
    for (int i = 0; i < CAL_N; i++) {
        if (g_cal[i].drops < 1 || g_cal[i].init100 < 3) continue;
        if (best < 0 || g_cal[i].drops > g_cal[best].drops || (g_cal[i].drops == g_cal[best].drops && CAL_BASE + i * 4 == HealthOffset)) best = i;
    }
    if (best >= 0) {
        HealthOffset = CAL_BASE + best * 4; g_healthCalibrated = true; g_lastHealth.clear(); g_healthSeen = 0;
        char b[160]; snprintf(b, sizeof b, "KALIBRASI: offset darah ditemukan 0x%x (awal=100 pada %d ped, turun %d kali) - disimpan ke ini", HealthOffset, g_cal[best].init100, g_cal[best].drops);
        Mark(b);
        TryWrite(VIS_DIR + "InteractivePeds.ini");
    }
}

// ---- Player kena pukul -> ped terdekat dianggap penyerang ----
static float g_prevPlayerHealth = -1; static int g_lastHitFrame = -100000;
static void CheckPlayerHit(void* player, void* nearest, float best, int frame) {
    if (!UseDeathCheck || (!g_healthCalibrated && g_healthSeen < 3)) return;                     // offset belum terbukti masuk akal
    float h = 0;
    if (!SafeRead((uint8_t*)player + HealthOffset, &h, 4) || !std::isfinite(h) || h <= 1.f || h >= 400.f) return;
    if (g_prevPlayerHealth > 1.f && h < g_prevPlayerHealth - 0.9f && frame - g_lastHitFrame > 20) {
        g_lastHitFrame = frame;
        if (nearest && best < 3.0f) {
            PedMind& pm = MindOf(nearest);
            if (pm.aggroT <= 0 && g_hurtLogs++ < 25) Mark("PLAYER KENA PUKUL, penyerang diduga: " + pm.name);
            brain.provoke(pm);
        }
    }
    g_prevPlayerHealth = h;
}

static void LogChat(const std::string& s) {
    std::string f = VIS_DIR + "chat_log.txt";
    FILE* fp = fopen(f.c_str(), "a");
    if (fp) { fprintf(fp, "%s\n", s.c_str()); fclose(fp); }
}
static void SetBubble(const std::string& txt) {
    bubbleText = txt;
    bubbleTime = std::min(16.f, 4.f + (float)txt.size() * 0.07f);      // makin panjang, makin lama tampil
}
static std::vector<std::string> WrapText(const std::string& s, size_t w) {
    std::vector<std::string> out; std::string line, word;
    auto flush = [&]() {
        if (word.empty()) return;
        if (line.empty()) line = word;
        else if (line.size() + 1 + word.size() <= w) line += " " + word;
        else { out.push_back(line); line = word; }
        word.clear();
    };
    for (char c : s) { if (c == ' ' || c == '\n' || c == '\r') flush(); else word += c; }
    flush(); if (!line.empty()) out.push_back(line);
    return out;
}

// Jalankan aksi yang diputuskan ped (hasil AI atau hasil deteksi perintah)
static int g_actLogs = 0;
static void ExecuteAction(void* ped, const std::string& act, PedMind& m) {
    if (act.empty() || act == "none" || !ped) return;
    if (g_actLogs++ < 40) Mark("ACTION: " + act + " (" + m.name + ")");
    if      (act == "follow")   Act_Follow(ped);
    else if (act == "stop")     Act_Stop(ped);
    else if (act == "leave")    Act_Leave(ped);
    else if (act == "dance")    Act_Dance(ped);
    else if (act == "hands_up") Act_HandsUp(ped);
    else if (act == "wave")     Act_Wave(ped);
    else if (act == "flee")     Act_Flee(ped);
    else if (act == "fight")    { if (ENABLE_CRIME) Act_AimAtPlayer(ped); }
}

// Kirim ucapan player ke AI (thread terpisah). Balasan masuk lewat antrean `replies`.
static void SendChat(const std::string& said) {
    if (said.empty() || !talkId) return;
    PedMind& m = brain.get(talkId);
    { bool conf = false; Lang dl = DetectLang2(said, conf);          // bahasa terakhir player; kalau tidak yakin, tetap pakai bahasa sebelumnya
      if (conf) { m.lang = dl; brain.defaultLang = dl; } }
    m.remember("P", said); m.timesTalked++;
    std::string prompt = brain.buildPrompt(m, said, Game_PlayerMoney(), Game_Hour());
    uint32_t id = talkId; PedMind snap = m;
    bubbleText = m.name + ": ..."; bubbleTime = 20; g_waiting = true; g_waitT = 0;
    LogChat("Player: " + said);
    std::string host = PROXY_HOST, port = PROXY_PORT;
    std::thread([id, prompt, said, snap, host, port]() {
        std::string out; Reply r{id, "", 0, 0, 0, "none"};
        if (http_post(host, port, "/chat", prompt, out, 7)) {
            size_t nl = out.find('\n');
            if (nl != std::string::npos) {
                char act[48] = {0};
                int n = sscanf(out.substr(0, nl).c_str(), "%d,%d,%d,%47s", &r.dHappy, &r.dAnger, &r.dFear, act);
                if (n == 4) r.action = act;
                r.text = out.substr(nl + 1);
            } else r.text = out;
            while (!r.text.empty() && (r.text.back() == '\n' || r.text.back() == '\r' || r.text.back() == ' ')) r.text.pop_back();
        } else { BrainRegistry tmp; r.text = tmp.offlineChat(snap, said, r.dHappy, r.dAnger, r.dFear, r.action); }   // offline cerdas
        std::lock_guard<std::mutex> g(qmx); replies.push(r);
    }).detach();
}

// Input cadangan: tulis pesan di file chat.txt (folder Android_Unprotected/data/<game>/), simpan, lalu dekati ped.
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
static volatile bool g_nearTalk = false;                             // true saat player cukup dekat ped untuk ngobrol
static int (*MP_SendChat_orig)(const char*);
static bool g_mpHooked = false;
// Player menekan tombol chat milik mod MP, ngetik, kirim -> MP::SendChat dipanggil. Kalau lagi dekat ped, teksnya kita ambil.
static int MP_SendChat_hook(const char* text) {
    if (UseMPChatTrigger && g_nearTalk && text && *text && text[0] != '/') {
        OnKeyboardDone(text, nullptr);
        if (!PassChatToMP) return 1;                                 // jangan diteruskan ke chat/server MP
    }
    return MP_SendChat_orig ? MP_SendChat_orig(text) : 0;
}
static void ResolveMPKeyboard() {
    if (VK_Open && (g_mpHooked || !UseMPChatTrigger)) return;        // semua sudah siap
    void* h = aml->GetLibHandle("libMP32.so");
    if (!h) h = dlopen("libMP32.so", RTLD_NOW | RTLD_NOLOAD);
    if (!h) { Mark("MP32: library tidak ditemukan (keyboard pinjaman mati)"); return; }
    if (!g_mpHooked && UseMPChatTrigger) {
        uintptr_t sc = aml->GetSym(h, "_ZN2MP8SendChatEPKc");
        Mark(std::string("MP::SendChat: ") + (sc ? "ADA (di-hook sebagai trigger tombol chat)" : "TIDAK ADA"));
        if (sc) { aml->Hook((void*)sc, (void*)MP_SendChat_hook, (void**)&MP_SendChat_orig); g_mpHooked = true; }
    }
    uintptr_t a = aml->GetSym(h, "_ZN9VKeyboard4OpenEPKcS1_iPFvS1_PvES2_b");
    uintptr_t b = aml->GetSym(h, "_ZN9VKeyboard6IsOpenEv");
    uintptr_t c = aml->GetSym(h, "_ZN9VKeyboard5CloseEv");
    Mark(std::string("MP32 keyboard: Open=") + (a ? "ADA" : "TIDAK") + " IsOpen=" + (b ? "ADA" : "TIDAK") + " Close=" + (c ? "ADA" : "TIDAK"));
    if (a && b) { SET_TO(VK_Open, a); SET_TO(VK_IsOpen, b); SET_TO(VK_Close, c); }
}

// ============================ Loop per frame (hook CHud::Draw) ============================
static int g_frame = 0, g_logs = 0;

static void EndTalk() {                                              // obrolan selesai: ped ingat player, lanjut aktivitas
    if (!talkPed) return;
    PedMind& m = brain.get(talkId); if (m.timesTalked > 0) m.knowsPlayer = true;
    Act_TalkGesture(talkPed, false); Act_Release(talkPed);
    talkPed = nullptr;
}

static void FrameLogic() {
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
    g_playerPos = pp; g_playerPosOk = true;
    if (g_frame % 60 == 1) g_playerModel = ReadModel(player);
    if (g_frame % 5 == 0) RefreshPeds(player);

    // ped terdekat
    void* nearest = nullptr; float best = 1e9f; int calSampled = 0;
    if (!g_healthCalibrated && g_frame % 8 == 0) CalibrateHealth(player);
    for (void* p : g_peds) {
        CVector q; if (!EntityPos(p, q)) continue;
        float d = std::hypot(q.x - pp.x, q.y - pp.y);
        if (!g_healthCalibrated && g_frame % 8 == 0 && d < 22.f && calSampled < 8) { CalibrateHealth(p); calSampled++; }
        if (d < best && !IsDead(p)) { best = d; nearest = p; }
    }

    CheckPlayerHit(player, nearest, best, g_frame);                   // player dipukul ped terdekat -> ped itu marah
    if (talkPed) {                                                    // lawan bicara baru saja memukul / dipukul -> langsung membentak
        PedMind& tm = brain.get(talkId);
        if (tm.aggroSay) { tm.aggroSay = false; SetBubble(tm.name + ": " + Vocab::Spontaneous(brain.ctxOf(tm), (int)tm.lang, 1, brain.rng)); LogChat(bubbleText); }
    }

    // Lawan bicara mati -> semua fitur chat langsung hilang
    if (talkPed && IsDead(talkPed)) {
        static int deathLogs = 0;
        if (deathLogs++ < 20) Mark("Ped meninggal -> chat ditutup: " + brain.get(talkId).name);
        if (VK_Close && VK_IsOpen && VK_IsOpen()) { KbCrumb("kb: Close (ped mati)"); VK_Close(); }
        bubbleTime = 0; g_waiting = false; kbRearm = 0; kbArmed = false; g_kbOpen = false;
        { std::lock_guard<std::mutex> g(qmx); while (!replies.empty()) replies.pop(); }
        { std::lock_guard<std::mutex> g(kbMx); kbSaid.clear(); kbDone = false; kbCancelled = false; }
        EndTalk();
    }

    // Kunci lawan bicara selama obrolan masih berlangsung (supaya balasan nggak "hilang" karena ganti target)
    bool locked = talkPed && (g_waiting || bubbleTime > 0 || g_kbOpen || kbRearm > 0);
    void* target = nearest; float tdist = best;
    if (locked) {
        CVector q;
        if (std::find(g_peds.begin(), g_peds.end(), talkPed) != g_peds.end() && EntityPos(talkPed, q)) { target = talkPed; tdist = std::hypot(q.x - pp.x, q.y - pp.y); }
        else locked = false;
    }

    // sapaan/olokan spontan
    if (!locked && nearest && best < 8.f && g_frame % 600 == 0) {
        PedMind& m = MindOf(nearest);
        Act a = brain.decide(m, best, 0, 0, false);
        if (a == Act::Greet || a == Act::Insult) {
            if (talkPed != nearest) EndTalk();
            talkPed = nearest; talkId = m.id;
            SetBubble(m.name + ": " + brain.offlineLine(m, a, ""));
            LogChat(bubbleText);
        }
    }

    bool canTalk = target && tdist < (locked ? TALK_RANGE + 3.f : TALK_RANGE);
    g_nearTalk = canTalk;
    if (canTalk && talkPed != target) {                              // mulai ngobrol dengan ped baru
        EndTalk();
        talkPed = target; talkId = (uint32_t)(uintptr_t)target;
        PedMind& m = MindOf(target);
        bool id = m.lang == Lang::ID;
        m.aggroSay = false;
        if (m.gang || m.aggroT > 0) SetBubble(m.name + ": " + Vocab::Spontaneous(brain.ctxOf(m), (int)m.lang, 0, brain.rng));   // anggota geng: sambutan sesuai hubungan
        else SetBubble(m.name + ": " + (m.knowsPlayer ? (id ? "Eh, lu lagi." : "Oh, it's you again.") : (id ? "Ya?" : "Yeah?")));
        Act_FaceAndStop(talkPed); Act_TalkGesture(talkPed, true);    // hadap player, diam, gesture bicara
    }
    if (!canTalk && talkPed && !locked) EndTalk();

    // keyboard in-game (pinjam dari libMP32.so)
    if (UseMPKeyboard) {
        static int resolveTries = 0;
        if ((!VK_Open || !g_mpHooked) && g_frame % 300 == 1 && resolveTries++ < 6) ResolveMPKeyboard();
        if (VK_Open && VK_IsOpen) {
            KbCrumb("kb: IsOpen"); bool kbOpen = VK_IsOpen(); g_kbOpen = kbOpen;
            { std::lock_guard<std::mutex> g(kbMx);
              if (kbDone) {
                  kbDone = false;
                  if (!kbSaid.empty()) { std::string said = kbSaid; kbSaid.clear(); SendChat(said); kbRearm = 6.f; }   // terkirim -> boleh ngobrol lagi 6 detik setelah balasan
                  else if (kbCancelled) { kbCancelled = false; kbRearm = 0; }                                         // batal -> tunggu player menjauh
              } }
            if (canTalk && AutoOpenKeyboard && kbArmed && !kbOpen && !g_waiting && g_frame - kbOpenedFrame > 120) {
                PedMind& pm = brain.get(talkId);
                std::string title = "Talk to " + pm.name;
                KbCrumb("kb: Open"); VK_Open(title.c_str(), "", 120, OnKeyboardDone, nullptr, false); KbCrumb("kb: Open selesai");
                kbArmed = false; kbOpenedFrame = g_frame;
            }
            if (!canTalk && tdist > TALK_RANGE + 3.f) kbArmed = true;
            if (kbRearm > 0 && !g_waiting) { kbRearm -= dt; if (kbRearm <= 0) kbArmed = true; }
        }
    }

    // balasan AI
    if (g_waiting) { g_waitT += dt; if (g_waitT > 20.f) g_waiting = false; }
    { std::lock_guard<std::mutex> g(qmx);
      while (!replies.empty()) {
          Reply r = replies.front(); replies.pop();
          PedMind& m = brain.get(r.id);
          m.happy += r.dHappy; m.anger += r.dAnger; m.fear += r.dFear; m.clamp();
          m.remember("N", r.text);
          SetBubble(m.name + ": " + r.text);
          LogChat(bubbleText);
          g_waiting = false;
          void* ped = nullptr;
          for (void* p : g_peds) if ((uint32_t)(uintptr_t)p == r.id) { ped = p; break; }
          if (ped && IsDead(ped)) { bubbleTime = 0; continue; }
          ExecuteAction(ped, r.action, m);                           // bertindak sesuai yang dikatakan player
      } }
    if (g_frame % 45 == 0) PollChatFile();

    // gambar (teks panjang dipecah jadi beberapa baris)
    int line = 0;
    if (canTalk) DrawHud(AutoOpenKeyboard ? "[ CHAT ]" : "[ CHAT ]  tekan tombol chat", line++);   // selalu tampil selama dekat ped
    if (bubbleTime > 0) {
        std::vector<std::string> ls = WrapText(bubbleText, 40);
        for (size_t i = 0; i < ls.size() && i < 5; i++) DrawHud(ls[i], line++);
        if (!canTalk) bubbleTime -= dt;                              // selama masih dekat, teks terakhir tetap tampil
    }

    // log bukti (dibatasi supaya file nggak membengkak)
    if (g_frame % 300 == 1 && g_logs < 12) {
        g_logs++;
        char b[200]; snprintf(b, sizeof b, "FRAME %d: player=(%.0f,%.0f,%.0f) ped=%d terdekat=%.1fm jam=%d",
                              g_frame, pp.x, pp.y, pp.z, (int)g_peds.size(), best > 1e8f ? -1.f : best, Game_Hour());
        Mark(b);
    }
}

static void Render2D_hook() {
    // DrawBeforeHud=1: gambar teks kita SEBELUM HUD game, saat setelan font masih standar (supaya tampilan font tetap sama).
    if (DrawBeforeHud) { FrameLogic(); Render2D_orig(); }
    else               { Render2D_orig(); FrameLogic(); }
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
    if (FontSetup) LoadCFont();
    std::thread([]() {
        DumpSymbols("libGTASA.so", "InteractivePeds_symbols_PED.txt", {"SetLookFlag", "ClearLook", "SetHeading", "AchieveHeading", "TurnToFace", "BlendAnimation", "AddAnimation", "CAnimManager", "StandStill", "SmartFlee", "FollowLeader", "FollowPed", "CTaskManager", "CPedIntelligence", "CTaskSimpleCarSetPedOut", "SetPedState", "SetMoveState", "PlayAnim", "TaskPlayAnim", "CTaskSimpleRunNamedAnim", "CTaskComplexWander", "CTaskSimpleHandsUp", "CTaskSimpleDuck", "CPed4Task", "CPed12SetIdle"});
        DumpSymbols("libGTASA.so", "InteractivePeds_symbols.txt", {"Touch", "Keyboard", "KeyBoard", "AND_", "OS_", "Widget", "CPad", "RsGlobal"});
    }).detach();
    Mark("4. OnModLoad selesai");
}
