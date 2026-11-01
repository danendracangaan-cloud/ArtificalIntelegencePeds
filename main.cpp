// TES MINIMAL: cuma buktiin apakah AML memanggil mod kita. Tanpa fitur apa pun.
#include <mod/amlmod.h>
#include <android/log.h>
#include <cstdio>
#include <cstring>
#include <dlfcn.h>

MYMOD(net.interactiveped, InteractivePeds, 1.0, you)

static void Mark(const char* stage) {
    __android_log_print(ANDROID_LOG_INFO, "InteractivePeds", "TES: %s", stage);
    char so[512] = "?";
    Dl_info info;
    if (dladdr((void*)&Mark, &info) && info.dli_fname) { strncpy(so, info.dli_fname, sizeof so - 1); so[sizeof so - 1] = 0; }
    const char* files[] = {
        "/storage/emulated/0/InteractivePeds_TES.txt",
        "/storage/emulated/0/Download/InteractivePeds_TES.txt",
        "/storage/emulated/0/Android_Unprotected/InteractivePeds_TES.txt",
        "/storage/emulated/0/Android_Unprotected/data/com.rockstargames.gtasa/InteractivePeds_TES.txt",
        "/storage/emulated/0/Android_Unprotected/data/com.rockstargames.gtasa/files/InteractivePeds_TES.txt",
        "/storage/emulated/0/Android/data/com.rockstargames.gtasa/files/InteractivePeds_TES.txt",
    };
    for (const char* f : files) {
        FILE* fp = fopen(f, "a");
        if (fp) { fprintf(fp, "%s | .so di: %s\n", stage, so); fclose(fp); }
    }
}

extern "C" void OnModPreLoad()   { Mark("OnModPreLoad jalan"); }
extern "C" void OnModLoad()      { Mark("OnModLoad jalan");    aml->ShowToast(true, "InteractivePeds TES: OnModLoad jalan"); }
extern "C" void OnAllModsLoaded(){ Mark("OnAllModsLoaded jalan"); aml->ShowToast(true, "InteractivePeds TES: semua mod selesai dimuat"); }
