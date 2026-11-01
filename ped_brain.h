// ped_brain.h - "otak" tiap ped: kepribadian, mood, memori, keputusan, fallback offline.
#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include <random>
#include <cstdint>
#include <cstdio>

enum class Trait { Friendly, Grumpy, Criminal, Nervous, Cocky };
enum class Act   { None, Greet, Insult, Rob, Pickpocket };

struct PedMind {
    uint32_t id = 0;
    std::string name;
    Trait trait = Trait::Friendly;
    // mood 0..100
    float happy = 50, anger = 20, fear = 20, greed = 30;
    bool  knowsPlayer = false;
    int   timesTalked = 0;
    float lastSeenGameTime = 0;
    float cooldown = 0;                 // detik sebelum boleh inisiatif lagi
    std::vector<std::string> history;   // "P: ..." / "N: ..." (dibatasi 10 baris)

    void clamp() {
        for (float* v : {&happy, &anger, &fear, &greed}) *v = *v < 0 ? 0 : (*v > 100 ? 100 : *v);
    }
    void remember(const std::string& who, const std::string& txt) {
        history.push_back(who + ": " + txt);
        if (history.size() > 10) history.erase(history.begin());
    }
    const char* moodWord() const {
        if (anger > 70) return "marah";
        if (fear  > 70) return "ketakutan";
        if (happy > 70) return "senang";
        if (happy < 25) return "sedih/kesal";
        return "biasa aja";
    }
    const char* traitWord() const {
        switch (trait) {
            case Trait::Friendly: return "ramah"; case Trait::Grumpy: return "pemarah";
            case Trait::Criminal: return "kriminal licik"; case Trait::Nervous: return "penakut";
            default: return "sombong"; }
    }
};

class BrainRegistry {
public:
    std::unordered_map<uint32_t, PedMind> minds;
    std::mt19937 rng{std::random_device{}()};

    float rnd() { return std::uniform_real_distribution<float>(0, 1)(rng); }

    PedMind& get(uint32_t id) {
        auto it = minds.find(id);
        if (it != minds.end()) return it->second;
        PedMind m; m.id = id;
        static const char* names[] = {"Jamal","Tony","Rico","Sasha","Dre","Mika","Carl","Luis","Tanya","Budi"};
        m.name = names[rng() % 10];
        float r = rnd();
        m.trait = r < .35f ? Trait::Friendly : r < .55f ? Trait::Grumpy : r < .70f ? Trait::Criminal
                : r < .85f ? Trait::Nervous : Trait::Cocky;
        m.happy = 30 + rnd() * 50; m.anger = rnd() * 40; m.fear = rnd() * 40; m.greed = rnd() * 60;
        if (m.trait == Trait::Criminal) m.greed += 30;
        if (m.trait == Trait::Grumpy)   m.anger += 25;
        if (m.trait == Trait::Nervous)  m.fear  += 25;
        m.clamp();
        return minds.emplace(id, m).first->second;
    }

    // Mood drift pelan-pelan (panggil tiap frame dengan dt detik)
    void tick(float dt) {
        for (auto& kv : minds) {
            PedMind& m = kv.second;
            m.cooldown -= dt; if (m.cooldown < 0) m.cooldown = 0;
            m.anger += (20 - m.anger) * 0.01f * dt;
            m.fear  += (20 - m.fear)  * 0.02f * dt;
            m.happy += (50 - m.happy) * 0.005f * dt + (rnd() - .5f) * 0.4f * dt;
            m.clamp();
        }
    }

    // Keputusan inisiatif ped (dipanggil saat ped dekat player & tidak sedang ngobrol)
    // dist: jarak ke player (m), playerMoney, wanted: wanted level, playerArmed: player pegang senjata
    Act decide(PedMind& m, float dist, int playerMoney, int wanted, bool playerArmed) {
        if (m.cooldown > 0) return Act::None;
        m.cooldown = 8 + rnd() * 12;                       // jangan spam
        float r = rnd();
        // Rob: kriminal/serakah, player punya duit, ped nggak takut, player nggak bersenjata
        float pRob = (m.trait == Trait::Criminal ? .10f : .01f) * (m.greed / 50.f)
                   * (playerMoney > 500 ? 1.f : .2f) * (playerArmed ? .2f : 1.f) * (m.fear > 60 ? 0 : 1);
        if (dist < 6 && wanted == 0 && r < pRob) return Act::Rob;
        r = rnd();
        float pPick = (m.trait == Trait::Criminal ? .12f : .02f) * (m.greed / 50.f) * (playerMoney > 100 ? 1.f : 0);
        if (dist < 5 && r < pPick) return Act::Pickpocket;
        r = rnd();
        float pInsult = (m.anger / 100.f) * .25f * (m.trait == Trait::Cocky || m.trait == Trait::Grumpy ? 1.5f : .6f);
        if (dist < 8 && r < pInsult) return Act::Insult;
        r = rnd();
        float pGreet = (m.happy / 100.f) * .3f * (m.trait == Trait::Friendly ? 1.5f : .5f) * (m.knowsPlayer ? 1.4f : 1.f);
        if (dist < 8 && r < pGreet) return Act::Greet;
        return Act::None;
    }

    // Fallback offline kalau server AI nggak ada / timeout
    std::string offlineLine(const PedMind& m, Act a, const std::string& playerSays) {
        auto pick = [&](std::vector<std::string> v) { return v[rng() % v.size()]; };
        std::string who = m.knowsPlayer ? "Eh, lu lagi." : "";
        switch (a) {
            case Act::Greet:
                if (m.anger > 60) return pick({"Apa liat-liat?", "Minggir lu."});
                return m.knowsPlayer ? pick({"Woy, " + std::string("balik lagi lu!"), "Sehat bro? Masih inget gua?"})
                                     : pick({"Halo bro!", "Pagi, bro.", "Wih, orang baru."});
            case Act::Insult:
                return pick({"Baju lu jelek banget, serius.", "Minggir, dasar kampungan!", "Liat apa lu, hah?"});
            case Act::Rob:     return pick({"Dompet lu. SEKARANG!", "Jangan gerak! Serahin duit lu!"});
            case Act::Pickpocket: return "";
            default: break;
        }
        // balasan chat
        if (m.fear > 70)  return pick({"J-jangan sakiti gua...", "Gua nggak mau masalah, bro."});
        if (m.anger > 70) return pick({"Pergi lu, gua lagi bete!", "Jangan ganggu gua."});
        if (m.happy > 70) return pick({"Hahaha, bisa aja lu!", "Santai bro, hidup indah!"});
        return pick({"Hmm, gitu ya.", "Terserah lu deh.", "Oke, oke."});
    }

    // Prompt untuk LLM lewat proxy
    std::string buildPrompt(const PedMind& m, const std::string& playerSays, int playerMoney, int hour) {
        char buf[512];
        snprintf(buf, sizeof buf,
            "Kamu adalah NPC bernama %s di kota GTA San Andreas. Kepribadian: %s. Mood sekarang: %s "
            "(happy=%d anger=%d fear=%d). %s Uang player: $%d. Jam game: %02d:00.\n",
            m.name.c_str(), m.traitWord(), m.moodWord(), (int)m.happy, (int)m.anger, (int)m.fear,
            m.knowsPlayer ? "Kamu SUDAH kenal player ini dari obrolan sebelumnya." : "Kamu belum kenal player ini.",
            playerMoney, hour);
        std::string p = buf;
        p += "Riwayat:\n";
        for (auto& h : m.history) p += h + "\n";
        p += "Player: " + playerSays + "\n";
        return p;
    }
};
