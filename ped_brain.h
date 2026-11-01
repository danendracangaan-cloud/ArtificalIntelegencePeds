// ped_brain.h - "otak" tiap ped: kepribadian, mood, memori, keputusan, fallback offline.
#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include <random>
#include <cstdint>
#include <cstdio>
#include <cctype>
#include <initializer_list>

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


    // ---------- Balasan offline cerdas: baca maksud kalimat player + mood + kepribadian + ingatan ----------
    // dH/dA/dF = perubahan mood (senang/marah/takut) akibat ucapan player.
    std::string offlineChat(const PedMind& m, const std::string& said, int& dH, int& dA, int& dF) {
        std::string t = said;
        for (auto& c : t) c = (char)tolower((unsigned char)c);
        auto has = [&](std::initializer_list<const char*> ks) { for (auto k : ks) if (t.find(k) != std::string::npos) return true; return false; };
        std::string last;
        for (int i = (int)m.history.size() - 1; i >= 0; i--) if (m.history[i].rfind("N: ", 0) == 0) { last = m.history[i].substr(3); break; }
        auto pick = [&](std::vector<std::string> v) {
            for (int k = 0; k < 8; k++) { const std::string& c = v[rng() % v.size()]; if (c != last) return c; }
            return v[0];
        };
        bool angry = m.anger > 60, scared = m.fear > 60, happy = m.happy > 65;
        bool nervous = m.trait == Trait::Nervous, cocky = m.trait == Trait::Cocky, crim = m.trait == Trait::Criminal;
        std::string n = m.name;
        dH = dA = dF = 0;

        if (has({"bunuh", "tembak", "mati lu", "mati kau", "hajar", "habisi", "pukul", "awas lu", "gua bunuh", "gue bunuh"})) {
            dF = 25; dA = 10; dH = -15;
            if (scared || nervous) return pick({"J-jangan! Gua cuma lewat doang, bro!", "Tolong... jangan sakitin gua, gua nggak punya salah!", "Oke oke, tenang! Gua pergi sekarang!"});
            if (cocky || crim)     return pick({"Hah? Coba aja kalau berani, bocah.", "Lu pikir gua takut? Gua udah sering ngadepin orang kayak lu.", "Silakan. Tapi jangan nangis kalau gua balas."});
            return pick({"Wah, santai bro. Jangan cari masalah di sini.", "Hei hei, ngomong yang bener. Gua nggak mau ribut.", "Gua panggil polisi nih kalau lu ngancem terus!"});
        }
        if (has({"goblok", "bodoh", "tolol", "anjing", "bangsat", "sialan", "brengsek", "kampret", "jelek", "pecundang", "idiot"})) {
            dA = 20; dH = -15; dF = scared ? 5 : 0;
            if (nervous) return pick({"Kok lu kasar banget sih... gua salah apa?", "Udah, udah... jangan marah-marah gitu.", "G-gua pergi aja deh kalau lu begitu."});
            if (cocky || angry || m.trait == Trait::Grumpy) return pick({"Ngomong sekali lagi, gua bikin lu nyesel!", "Mulut lu, dijaga! Lu nggak kenal gua siapa.", "Ngaca dulu, baru ngatain orang!", "Lu cari ribut? Gua ladenin!"});
            return pick({"Wah, kasar banget. Nggak ada sopan-santunnya lu.", "Santai dikit napa, bro. Gua nggak ngapa-ngapain lu.", "Yaelah, hidup lu stres banget kayaknya."});
        }
        if (has({"makasih", "terima kasih", "thanks", "thx", "tengkyu", "mantap", "keren", "bagus", "baik banget", "hebat"})) {
            dH = 12; dA = -8;
            return pick({"Sama-sama, bro! Santai aja.", "Hehe, bisa aja lu. Jadi malu gua.", "Nah gitu dong, yang sopan. Gua suka orang kayak lu.", "Santai! Kapan-kapan ngobrol lagi ya."});
        }
        if (has({"dadah", "bye", "dah dulu", "gua pergi", "gue pergi", "sampai jumpa", "duluan", "cabut"})) {
            return pick({m.knowsPlayer ? "Oke, hati-hati di jalan. Jangan lama-lama ilang." : "Oke, bro. Hati-hati.", "Yoi, sampai ketemu lagi!", "Cabut aja, gua juga mau jalan."});
        }
        if (has({"nama", "siapa lu", "siapa kamu", "siapa elu", "who are you"})) {
            dH = 3;
            if (angry) return pick({"Ngapain nanya nama gua? Urusan lu apa?", "Nama gua " + n + ". Terus kenapa?"});
            return pick({"Nama gua " + n + ". Lu sendiri siapa?", "Panggil aja gua " + n + ", bro.", n + ". Orang sini, udah lama nongkrong di jalanan ini."});
        }
        if (has({"apa kabar", "gimana kabar", "kabar lu", "gimana hari", "lagi apa", "lagi ngapain", "how are you"})) {
            dH = 4;
            if (angry)  return pick({"Buruk. Hari ini bikin emosi terus.", "Jangan nanya, lagi bete banget gua."});
            if (scared) return pick({"Agak tegang, bro. Daerah ini kadang nggak aman.", "Gua... baik-baik aja. Cuma lagi waspada."});
            if (happy)  return pick({"Mantap banget hari ini! Cuaca bagus, hidup enak.", "Baik banget, bro! Lu sendiri gimana?", "Lagi bagus nih, nggak ada yang bikin pusing."});
            return pick({"Biasa aja, bro. Hidup jalan terus.", "Yaa gitu-gitu aja. Lu sendiri?", "Lumayan lah, masih bisa napas."});
        }
        if (has({"halo", "hai", "hi ", "hei", "hey", "woi", "woy", "pagi", "siang", "sore", "malam", "bro", "yo", "assalamualaikum", "salam", "hello", "tes", "test"})) {
            dH = 4;
            if (m.knowsPlayer && m.timesTalked > 3) return pick({"Wih, " + std::string("lu lagi! Kita udah sering ngobrol ya."), "Eh, langganan gua datang. Ada apa lagi?", "Woy, balik lagi! Gua udah hafal muka lu."});
            if (m.knowsPlayer) return pick({"Oh, lu yang kemarin ngobrol sama gua kan? Halo lagi.", "Halo lagi, bro. Gua masih inget lu."});
            if (angry)  return pick({"Apa? Gua lagi nggak mood ngobrol.", "Mau apa? Cepetan, gua sibuk.", "Hmph. Ada perlu apa lu?"});
            if (scared) return pick({"H-halo... lu nggak bakal macam-macam kan?", "Halo. Gua cuma lagi lewat, bro."});
            if (happy)  return pick({"Halo juga, bro! Hari yang bagus ya!", "Woy! Santai, senang ketemu lu!", "Haii! Ada yang bisa gua bantu?"});
            return pick({"Halo juga.", "Yo. Ada apa?", "Hai, bro. Lu orang baru di sini ya?"});
        }
        if (has({"uang", "duit", "pinjam", "minjem", "minta", "bagi", "dolar", "cash", "kaya", "miskin"})) {
            dA = angry ? 5 : 0;
            if (crim)  return pick({"Duit? Nah, ini topik favorit gua. Lu punya berapa?", "Kalau soal duit, gua bisa kasih info... asal ada imbalannya.", "Gua nggak minjemin duit, tapi gua tau cara cari duit cepat."});
            if (angry || m.greed > 70) return pick({"Duit? Gua aja kekurangan! Minta sama orang lain.", "Enak aja minta duit. Kerja dong!"});
            return pick({"Duit gua pas-pasan, bro. Maaf ya.", "Wah, gua juga lagi seret nih.", "Lagi nggak ada, bro. Coba tanya orang lain."});
        }
        if (has({"dimana", "di mana", "arah", "jalan ke", "toko", "polisi", "rumah sakit", "gym", "tempat", "lokasi", "nyasar"})) {
            if (angry) return pick({"Gua bukan GPS. Tanya orang lain!", "Mana gua tau. Gua bukan pemandu wisata."});
            return pick({"Wah, gua kurang tau daerah situ. Coba tanya yang lain.", "Lurus aja terus, nanti juga ketemu. Kayaknya.", "Gua cuma tau jalan sekitar sini, bro."});
        }
        if (has({"cinta", "sayang", "cantik", "ganteng", "pacar", "jodoh"})) {
            dH = 5;
            return pick({"Hahaha, lu ada-ada aja!", "Wah, jangan bikin gua baper, bro.", "Hehe, gombalan lu kurang ampuh, tapi lumayan lucu."});
        }
        if (has({"?"})) {
            if (angry)  return pick({"Banyak nanya lu. Gua nggak tau, nggak peduli.", "Tanya yang lain aja."});
            if (nervous)return pick({"Hmm... gua nggak yakin. Mungkin?", "Gua nggak berani jawab, bro."});
            if (cocky)  return pick({"Pertanyaan bagus. Tapi lu nggak bakal ngerti jawabannya.", "Gua tau jawabannya, tapi lu belum pantas dengar."});
            return pick({"Hmm, pertanyaan menarik. Gua belum pernah mikirin itu.", "Susah dijawab, bro. Menurut lu sendiri gimana?", "Entahlah. Mungkin iya, mungkin enggak."});
        }
        // default: respons sesuai mood
        if (scared) return pick({"J-jangan deket-deket ya, bro...", "Lu bikin gua nggak nyaman.", "Gua mending pergi aja."});
        if (angry)  return pick({"Udah, jangan ganggu gua lagi.", "Gua lagi nggak mood. Pergi sana.", "Hmph. Terserah lu."});
        if (happy)  return pick({"Hahaha, bisa aja lu!", "Santai, bro. Hidup itu indah!", "Wih, seru juga ngobrol sama lu.", "Gua suka ngobrol sama lu, sumpah."});
        return pick({"Hmm, gitu ya.", "Oke, oke. Terus?", "Menarik juga omongan lu.", "Gua dengerin kok. Lanjut.", "Yaa gitu deh jalan hidup."});
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
