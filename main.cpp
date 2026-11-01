// InteractivePeds - AML mod untuk GTA SA Android (armeabi-v7a, libGTASA.so v2.00)
// Bagian [VERIFY] = harus lu cek sendiri dengan `nm -D libGTASA.so | grep <nama>` atau disassembler.
#include <mod/amlmod.h>
#include <android/log.h>
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO,  "InteractivePeds", __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, "InteractivePeds", __VA_ARGS__)
#include <thread>
#include <mutex>
#include <queue>
#include <cmath>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <sys/stat.h>
#include <dlfcn.h>
#include "ped_brain.h"
#include "net.h"

MYMOD(net.interactiveped, InteractivePeds, 1.0, you)

// ---- Penanda tahap: nulis baris ke InteractivePeds_FULL.txt (bukti kode kita jalan sampai mana) ----
static void Mark(const char* stage) {
    LOGI("FULL: %s", stage);
    const char* files[] = {
        "/storage/emulated/0/Android_Unprotected/data/com.rockstargames.gtasa/InteractivePeds_FULL.txt",
        "/storage/emulated/0/Android_Unprotected/data/com.rockstargames.gtasa/files/InteractivePeds_FULL.txt",
    };
    for (const char* f : files) {
        FILE* fp = fopen(f, "a");
        if (fp) { fprintf(fp, "%s\n", stage); fclose(fp); }
    }
}

// ---------------- Config ----------------
static std::string PROXY_HOST = "192.168.1.10";   // IP PC/VPS yang jalanin proxy.py (bisa diubah lewat file .ini)
static std::string PROXY_PORT = "8787";
static float TALK_RANGE = 2.5f;
static std::string g_status = "belum dijalankan";   // ditampilkan lewat toast di layar

// Nama paket asli game (dibaca dari proses sendiri, jadi aman walau APK hasil repack)
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
    fprintf(f, "[Settings]\nProxyHost=%s\nProxyPort=%s\nTalkRange=%.1f\n",
            PROXY_HOST.c_str(), PROXY_PORT.c_str(), TALK_RANGE);
    fclose(f);
    return true;
}

// Baca config; kalau file belum ada, bikin otomatis (coba beberapa lokasi).
static void LoadConfig() {
    std::string pkg = GetPackageName();
    LOGI("package: %s", pkg.c_str());
    // Cari lokasi file .so kita sendiri (mis. .../Android_Unprotected/data/<pkg>/mods/libInteractivePeds.so)
    std::string soDir, dataDir;
    Dl_info info;
    if (dladdr((void*)&LoadConfig, &info) && info.dli_fname) {
        std::string p = info.dli_fname;
        LOGI("lokasi .so: %s", p.c_str());
        size_t k = p.find_last_of('/');
        if (k != std::string::npos) soDir = p.substr(0, k + 1);          // .../mods/
        const std::string tail = "/mods/";
        if (soDir.size() > tail.size() && soDir.compare(soDir.size() - tail.size(), tail.size(), tail) == 0)
            dataDir = soDir.substr(0, soDir.size() - tail.size() + 1);   // .../<pkg>/
    }
    std::vector<std::string> dirs;
    // Lokasi resmi dari AML sendiri (sama seperti yang dipakai mod lain, mis. Natural Disaster)
    for (const char* p : { aml->GetConfigPath(), aml->GetAndroidDataPath() }) {
        if (p && *p) { std::string d = p; if (d.back() != '/') d += '/'; dirs.push_back(d); }
    }
    if (!dataDir.empty()) {
        dirs.push_back(dataDir + "configs/");
        dirs.push_back(dataDir + "files/configs/");
        dirs.push_back(dataDir + "files/");
    }
    if (!soDir.empty()) dirs.push_back(soDir);
    for (std::string root : {"/storage/emulated/0/Android_Unprotected/data/", "/storage/emulated/0/Android/data/"}) {
        dirs.push_back(root + pkg + "/configs/");
        dirs.push_back(root + pkg + "/files/configs/");
        dirs.push_back(root + pkg + "/files/");
    }
    for (auto& d : dirs) {
        std::string path = d + "InteractivePeds.ini";
        FILE* f = fopen(path.c_str(), "r");
        if (f) {                                    // ketemu -> baca
            char line[256];
            while (fgets(line, sizeof line, f)) {
                char k[64], v[160];
                if (sscanf(line, " %63[^=]=%159[^\r\n]", k, v) == 2) {
                    std::string key = k, val = v;
                    if (key == "ProxyHost") PROXY_HOST = val;
                    else if (key == "ProxyPort") PROXY_PORT = val;
                    else if (key == "TalkRange") TALK_RANGE = (float)atof(val.c_str());
                }
            }
            fclose(f);
            LOGI("config dibaca: %s", path.c_str());
            g_status = "ini dibaca: " + path;
            return;
        }
    }
    for (auto& d : dirs) {                          // belum ada -> bikin
        std::string dd = d; if (!dd.empty() && dd.back() == '/') dd.pop_back();
        mkdir(dd.c_str(), 0777);
        std::string path = d + "InteractivePeds.ini";
        if (TryWrite(path)) { LOGI("config dibuat: %s", path.c_str()); g_status = "ini dibuat: " + path; return; }
    }
    LOGE("gagal bikin InteractivePeds.ini di semua lokasi");
    g_status = "GAGAL bikin ini (semua lokasi ditolak)";
}

// ---------------- Struct minimal ----------------
struct CVector { float x, y, z; };
class CPed;  // pakai header SA lu (mis. dari template AML RusJJ) untuk akses penuh

// ---------------- Resolve fungsi game [VERIFY semua nama simbol] ----------------
static uintptr_t pGTASA; static void* hGTASA;
static CPed* (*FindPlayerPed)(int);                                   // _Z13FindPlayerPedi
static void  (*CalcScreenCoors)(const CVector*, CVector*, float*, float*, bool, bool); // _ZN7CSprite15CalcScreenCoorsERK7CVectorPS0_PfS3_bb
static void  (*Font_Print)(float, float, uint16_t*);                  // _ZN5CFont11PrintStringEffPt
static void  (*Font_SetScale)(float, float);                          // _ZN5CFont8SetScaleEff
static void  (*Font_SetColor)(uint32_t*);                             // _ZN5CFont8SetColorE5CRGBA
// ---- STUB: belum terhubung ke engine game. Isi satu per satu pakai aml-psdk / header SA. ----
static int   Game_GetNearbyPeds(const CVector&, float, CPed**, int) { return 0; }
static bool  Game_PedPos(CPed*, CVector&)  { return false; }
static uint32_t Game_PedHandle(CPed* p)    { return (uint32_t)(uintptr_t)p; }
static int   Game_PlayerMoney()            { return 0; }
static void  Game_AddMoney(int)            {}
static int   Game_Wanted()                 { return 0; }
static bool  Game_PlayerArmed()            { return false; }
static float Game_DT()                     { return 0.016f; }
static int   Game_Hour()                   { return 12; }
static void  Act_AimAtPlayer(CPed*)        {}
static void  Act_Flee(CPed*)               {}
static void  Act_ShootPlayer(CPed*)        {}
static void  Act_PickpocketRun(CPed*)      {}
static void  Act_FaceAndStop(CPed*)        {}
static void  Act_PlaySpeech(CPed*)         {}


// ---------------- State ----------------
static BrainRegistry& BR() { static BrainRegistry b; return b; }
#define brain (BR())
enum class UI { Idle, Chatting, RobChoice };
static UI ui = UI::Idle;
static CPed* talkPed = nullptr;
static uint32_t talkId = 0;
static std::string inputBuf;                 // diisi dari keyboard (lihat Input_PushChar)
static std::string bubbleText; static float bubbleTime = 0;   // teks balasan yang tampil
static int robAmount = 0;

struct Reply { uint32_t id; std::string text; int dHappy, dAnger, dFear; };
static std::mutex qmx; static std::queue<Reply> replies;

// ---------------- Input keyboard ----------------
// Android: hook/terima tombol dari Java->native (mis. hook fungsi key event game, atau IME).
// Dari hook lu panggil ini. Enter = kirim, Backspace = hapus, ESC = batal.
extern "C" void Input_PushKey(int key, uint32_t unicode);
void Input_PushKey(int key, uint32_t unicode) {
    if (ui != UI::Chatting) return;
    if (key == 13) { /* Enter */ extern void SendChat(); SendChat(); }
    else if (key == 27) { ui = UI::Idle; inputBuf.clear(); talkPed = nullptr; }
    else if (key == 8) { if (!inputBuf.empty()) inputBuf.pop_back(); }
    else if (unicode >= 32 && unicode < 127 && inputBuf.size() < 80) inputBuf.push_back((char)unicode);
}

// ---------------- Kirim chat ke AI (thread terpisah, game nggak nge-freeze) ----------------
void SendChat() {
    if (inputBuf.empty() || !talkPed) return;
    PedMind& m = brain.get(talkId);
    std::string said = inputBuf; inputBuf.clear();
    m.remember("P", said); m.timesTalked++;
    std::string prompt = brain.buildPrompt(m, said, Game_PlayerMoney(), Game_Hour());
    uint32_t id = talkId; PedMind snapshot = m;
    bubbleText = "..."; bubbleTime = 15;
    std::thread([id, prompt, said, snapshot]() {
        std::string out; Reply r{id, "", 0, 0, 0};
        if (http_post(PROXY_HOST, PROXY_PORT, "/chat", prompt, out)) {
            // format: baris1 = "dHappy,dAnger,dFear"  baris2.. = balasan
            size_t nl = out.find('\n');
            if (nl != std::string::npos) {
                sscanf(out.substr(0, nl).c_str(), "%d,%d,%d", &r.dHappy, &r.dAnger, &r.dFear);
                r.text = out.substr(nl + 1);
            } else r.text = out;
        } else {
            BrainRegistry tmp; r.text = tmp.offlineLine(snapshot, Act::None, said);   // fallback offline
        }
        std::lock_guard<std::mutex> g(qmx); replies.push(r);
    }).detach();
}

// ---------------- Gambar label "chat" di atas ped ----------------
static void DrawLabel(const CVector& world, const char* txt, float scale = 0.6f) {
    CVector s; float w, h;
    CVector p = {world.x, world.y, world.z + 1.1f};
    CalcScreenCoors(&p, &s, &w, &h, true, true);
    if (s.z < 1.f) return;                         // di belakang kamera
    uint16_t wide[96]; int i = 0; for (; txt[i] && i < 95; i++) wide[i] = (uint8_t)txt[i]; wide[i] = 0;
    Font_SetScale(scale * 0.5f, scale);
    Font_Print(s.x, s.y, wide);
}

// ---------------- Aksi hasil keputusan AI ----------------
static void DoAction(CPed* ped, PedMind& m, Act a) {
    switch (a) {
        case Act::Greet:
        case Act::Insult:
            bubbleText = m.name + ": " + brain.offlineLine(m, a, ""); bubbleTime = 5;
            talkPed = ped; talkId = m.id;   // bubble ngikut ped ini
            // Mau LLM juga untuk sapaan/olokan? kirim prompt "[kamu memulai: sapa/olok player]" via thread yang sama.
            break;
        case Act::Rob: {
            robAmount = std::min(Game_PlayerMoney(), 200 + (int)(brain.rnd() * 800));
            Act_AimAtPlayer(ped);
            bubbleText = m.name + ": " + brain.offlineLine(m, Act::Rob, ""); bubbleTime = 30;
            talkPed = ped; talkId = m.id; ui = UI::RobChoice;
            break; }
        case Act::Pickpocket:
            Act_PickpocketRun(ped);        // saat ped menyentuh player -> lihat OnPickpocketSuccess
            break;
        default: break;
    }
}

// Dipanggil dari Act_PickpocketRun begitu ped sampai dekat player
void OnPickpocketSuccess(CPed* ped) {
    PedMind& m = brain.get(Game_PedHandle(ped));
    int stolen = std::min(Game_PlayerMoney(), 50 + (int)(brain.rnd() * 300));
    Game_AddMoney(-stolen);
    bubbleText = "Dompet lu ilang $" + std::to_string(stolen) + "!"; bubbleTime = 4;
    Act_Flee(ped); m.knowsPlayer = true; m.greed -= 20;
}

// Pilihan rob: 1 = kasih, 2 = nggak. (hubungkan ke tombol/touch UI lu lewat Input_PushKey atau hook touch)
extern "C" void Rob_Choose(bool give) {
    if (ui != UI::RobChoice || !talkPed) return;
    PedMind& m = brain.get(talkId);
    if (give) {
        Game_AddMoney(-robAmount); Act_Flee(talkPed);
        bubbleText = m.name + ": Pinter. Jangan lapor-lapor."; m.fear += 10; m.happy += 10;
    } else {
        // 50% ped nembak, 50% ped panik kabur (tergantung fear)
        if (brain.rnd() > m.fear / 100.f) Act_ShootPlayer(talkPed); else Act_Flee(talkPed);
        bubbleText = m.name + ": Yaudah, rasain!"; m.anger += 30;
    }
    bubbleTime = 4; m.knowsPlayer = true; ui = UI::Idle; talkPed = nullptr;
}

// ---------------- Loop utama (dipanggil tiap frame) ----------------
static float lastTime = 0;
static void (*Render2D_orig)();
static void Render2D_hook() {
    Render2D_orig();                                   // gambar HUD asli dulu
    float dt = Game_DT();
    brain.tick(dt);

    if (!FindPlayerPed || !CalcScreenCoors || !Font_Print || !Font_SetScale) return;  // simbol belum ketemu
    CPed* player = FindPlayerPed(-1);
    if (!player) return;
    CVector pp; if (!Game_PedPos(player, pp)) return;

    // ambil balasan AI dari thread
    { std::lock_guard<std::mutex> g(qmx);
      while (!replies.empty()) {
          Reply r = replies.front(); replies.pop();
          PedMind& m = brain.get(r.id);
          m.happy += r.dHappy; m.anger += r.dAnger; m.fear += r.dFear; m.clamp();
          m.remember("N", r.text);
          bubbleText = m.name + ": " + r.text; bubbleTime = 8;
      } }

    CPed* near[16]; int n = Game_GetNearbyPeds(pp, 8.f, near, 16);
    CPed* closest = nullptr; float best = 1e9f;
    for (int i = 0; i < n; i++) {
        CVector p; if (!Game_PedPos(near[i], p)) continue;
        float d = std::hypot(p.x - pp.x, p.y - pp.y);
        if (d < best) { best = d; closest = near[i]; }
        PedMind& m = brain.get(Game_PedHandle(near[i]));
        // inisiatif ped (hanya saat player nggak lagi di UI apa pun)
        if (ui == UI::Idle) {
            Act a = brain.decide(m, d, Game_PlayerMoney(), Game_Wanted(), Game_PlayerArmed());
            if (a != Act::None) DoAction(near[i], m, a);
        }
    }

    // label "chat" di atas ped terdekat
    if (ui == UI::Idle && closest && best < TALK_RANGE) {
        CVector p; Game_PedPos(closest, p); DrawLabel(p, "[ CHAT ]");
        // Tap label / tombol: lu hubungkan ke input -> Chat_Begin(closest)
        extern void Chat_Begin(CPed*); // dipanggil dari hook input
    }

    // UI aktif
    if (talkPed) {
        CVector p; if (Game_PedPos(talkPed, p)) {
            if (bubbleTime > 0) { DrawLabel(p, bubbleText.c_str(), 0.55f); bubbleTime -= dt; }
        }
        if (ui == UI::Chatting) DrawLabel(pp, (std::string("> ") + inputBuf + "_").c_str(), 0.6f);
        if (ui == UI::RobChoice) {
            std::string t = "Serahin $" + std::to_string(robAmount) + "?  [1] Kasih   [2] Tolak";
            DrawLabel(pp, t.c_str(), 0.6f);
        }
        if (ui == UI::Idle && bubbleTime <= 0) talkPed = nullptr;
    }
}

void Chat_Begin(CPed* ped) {
    talkPed = ped; talkId = Game_PedHandle(ped); ui = UI::Chatting; inputBuf.clear();
    Act_FaceAndStop(ped);
    PedMind& m = brain.get(talkId);
    bubbleText = m.name + (m.knowsPlayer ? ": Oh, lu. Mau ngobrol lagi?" : ": Ya?"); bubbleTime = 6;
}
// Saat player menutup obrolan: ped "kenal" player
extern "C" void Chat_End() {
    if (talkPed) { PedMind& m = brain.get(talkId); if (m.timesTalked > 0) m.knowsPlayer = true; }
    ui = UI::Idle; inputBuf.clear();
}

// ---------------- Entry ----------------
// Pesan di layar: bukti mod ini kemuat. Dipanggil lagi setelah semua mod selesai (activity sudah siap).
extern "C" void OnModPreLoad() { Mark("1. OnModPreLoad"); }

extern "C" void OnAllModsLoaded() {
    Mark("5. OnAllModsLoaded");
    aml->ShowToast(true, "InteractivePeds AKTIF | %s", g_status.c_str());
}

extern "C" void OnModLoad() {
    Mark("2. OnModLoad mulai");
    LoadConfig();
    Mark(("3. LoadConfig selesai: " + g_status).c_str());
    aml->ShowToast(false, "InteractivePeds dimuat");
    pGTASA = aml->GetLib("libGTASA.so"); hGTASA = aml->GetLibHandle("libGTASA.so");
    SET_TO(FindPlayerPed,   aml->GetSym(hGTASA, "_Z13FindPlayerPedi"));
    SET_TO(CalcScreenCoors, aml->GetSym(hGTASA, "_ZN7CSprite15CalcScreenCoorsERK7CVectorPS0_PfS3_bb"));
    SET_TO(Font_Print,      aml->GetSym(hGTASA, "_ZN5CFont11PrintStringEffPt"));
    SET_TO(Font_SetScale,   aml->GetSym(hGTASA, "_ZN5CFont8SetScaleEff"));
    // Hook titik gambar HUD per-frame [VERIFY nama/offset]: contoh CHud::Draw
    void* hudDraw = (void*)aml->GetSym(hGTASA, "_ZN4CHud4DrawEv");
    if (hudDraw) aml->Hook(hudDraw, (void*)Render2D_hook, (void**)&Render2D_orig);
    else LOGE("CHud::Draw tidak ketemu - cek nama simbol");
    LOGI("InteractivePeds loaded");
    Mark("4. OnModLoad selesai");
}
