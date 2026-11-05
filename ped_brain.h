// ped_brain.h - "otak" tiap ped: kepribadian, mood, memori, keputusan, fallback offline.
#pragma once
#include <algorithm>
#include "vocab.h"
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

// ---------- Bahasa & maksud ucapan player ----------
enum class Lang   { EN, ID, ES };
enum class Intent { None, Follow, Stop, Leave, Dance, HandsUp, Wave, Flee, Fight };

inline std::string LowerPad(const std::string& s) { return Vocab::NormText(s); }
inline bool HasAny(const std::string& t, std::initializer_list<const char*> ks) { return Vocab::HasAnyN(t, ks); }

// Deteksi bahasa. confident=false kalau tidak ada penanda sama sekali (pakai bahasa terakhir, jangan balik ke Inggris).
inline Lang DetectLang2(const std::string& said, bool& confident) {
    std::string t = Vocab::NormText(said);
    static const char* const IDW[] = {"gua","gue","gw","lu","lo","elu","loe","aku","saya","kamu","kau","anda","dia","kita","kami","mereka","apa","siapa","kenapa","mengapa","gimana","bagaimana","kapan","dimana","berapa","yang","dan","atau","ini","itu","sama","juga","lagi","udah","sudah","belum","mau","bisa","boleh","jangan","tolong","makasih","terima","halo","hai","selamat","pagi","siang","sore","malam","bang","mas","mbak","dong","sih","nih","deh","kok","aja","banget","nggak","ngga","gak","tidak","bukan","punya","ada","kerja","makan","minum","tidur","pergi","pulang","ikut","bawa","beli","jual","uang","duit","rumah","mobil","motor","polisi","teman","cewek","cowok","cantik","ganteng","sayang","cinta","maaf","iya","enggak","emang","kayak","kayaknya","masa","gitu","gini","begitu","begini","cuma","doang","ayo","yuk","lah","kan","toh","dulu","nanti","tadi","besok","kemarin","sekarang","orang","bosen","capek","sedih","senang","marah","takut","laper","lapar","suka","kenal","namanya","umur","dari","mana"};
    static const char* const ESW[] = {"hola","gracias","amigo","como","cómo","qué","tal","dinero","donde","dónde","adiós","adios","buenos","buenas","favor","quién","quien","puedes","necesito","hablas","vete","tengo","hambre","quiero","estoy","eres","pero","también","ayuda","usted","nombre","llamas","cuántos","cuantos","dime","oye","vamos","bueno","muy","mucho","señor","hermano","compa","jefe","casa","carro","coche","porque","para","donde","tienes","soy"};
    static const char* const ENW[] = {"the","you","your","are","what","how","why","when","where","who","do","does","did","is","am","i","me","my","it","to","and","of","in","for","that","this","can","could","would","will","hello","hi","hey","yo","thanks","thank","please","tell","like","love","want","need","get","have","has","go","with","not","dont","im","ive","its","let","lets","here","there","just","know","think","about","really","good","bad","man","dude","nice","cool","sorry","help","money","car","food"};
    int en = 0;
    for (const char* w : ENW) if (t.find(" " + std::string(w) + " ") != std::string::npos) en++;
    int id = 0, es = 0;
    for (const char* w : IDW) if (t.find(" " + std::string(w) + " ") != std::string::npos) id++;
    for (const char* w : ESW) if (t.find(" " + std::string(w) + " ") != std::string::npos) es++;
    confident = (id > 0 || es > 0 || en > 0);
    if (id > 0 && id >= es && id >= en) return Lang::ID;
    if (es > 0 && es > id && es >= en) return Lang::ES;
    return Lang::EN;
}
inline Lang DetectLang(const std::string& said) { bool c; return DetectLang2(said, c); }
inline Intent DetectIntent(const std::string& said) {
    std::string t = LowerPad(said);
    if (HasAny(t, {"hands up", "put your hands", "put em up", "angkat tangan", "manos arriba"})) return Intent::HandsUp;
    if (HasAny(t, {"follow me", "come with me", "come along", "come on with me", "ikut gua", "ikut gue", "ikut aku", "ikuti gua", "ikuti gue", "sígueme", "sigueme"})) return Intent::Follow;
    if (HasAny(t, {"fight me", "let's fight", "lets fight", "wanna fight", "punch", "come at me", "berantem", "ayo berkelahi", "pukul gua", "pelea"})) return Intent::Fight;
    if (HasAny(t, {"run away", "run!", "run for", "lari", "corre "})) return Intent::Flee;
    if (HasAny(t, {"go away", "get lost", "leave me", "scram", "beat it", "pergi", "minggir", "enyah", "vete", "piss off"})) return Intent::Leave;
    if (HasAny(t, {"dance", "dancing", "joget", "menari", "baila"})) return Intent::Dance;
    if (HasAny(t, {"wave", "lambai", "say hi to everyone"})) return Intent::Wave;
    if (HasAny(t, {"stop", "wait", "stay here", "stay put", "stand still", "don't move", "dont move", "freeze", "tunggu", "berhenti", "diam", "espera", "quédate", "quedate"})) return Intent::Stop;
    return Intent::None;
}
inline const char* IntentName(Intent i) {
    switch (i) { case Intent::Follow: return "follow"; case Intent::Stop: return "stop"; case Intent::Leave: return "leave";
                 case Intent::Dance: return "dance"; case Intent::HandsUp: return "hands_up"; case Intent::Wave: return "wave";
                 case Intent::Flee: return "flee"; case Intent::Fight: return "fight"; default: return "none"; }
}


struct PedMind {
    uint32_t id = 0;
    std::string name;
    Trait trait = Trait::Friendly;
    // mood 0..100
    float happy = 50, anger = 20, fear = 20, greed = 30;
    bool  knowsPlayer = false;
    Lang  lang = Lang::EN;               // bahasa terakhir yang dipakai player
    int   gender = 0;                    // 0 tidak diketahui, 1 cowok, 2 cewek (dari model skin)
    int   model  = -1;                   // ID skin ped
    float aggroT = 0;                    // detik tersisa ped marah ke player (habis berantem)
    bool  aggroSay = false;              // true = baru dipicu, ped perlu langsung membentak
    int   gang = 0, relation = 0;        // geng ped (Vocab::Gang) & hubungannya dengan player (-2..+2)
    std::string pname = "homie";         // cara ped menyebut player ("CJ" / "homie")
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
    const char* moodEN() const {
        if (anger > 70) return "angry";
        if (fear  > 70) return "scared";
        if (happy > 70) return "happy";
        if (happy < 25) return "sad/irritated";
        return "neutral";
    }
    const char* traitEN() const {
        switch (trait) {
            case Trait::Friendly: return "friendly"; case Trait::Grumpy: return "grumpy";
            case Trait::Criminal: return "sly street criminal"; case Trait::Nervous: return "nervous";
            default: return "cocky"; }
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
    int genderHint = 0, modelHint = -1;            // diisi main.cpp sebelum get() untuk ped baru
    Lang defaultLang = Lang::EN;                   // bahasa terakhir yang dipakai player (ped baru ikut)
    int gangHint = 0, relHint = 0; std::string pnameHint = "homie";   // diisi main.cpp sebelum get() untuk ped baru

    float rnd() { return std::uniform_real_distribution<float>(0, 1)(rng); }

    PedMind& get(uint32_t id) {
        auto it = minds.find(id);
        if (it != minds.end()) return it->second;
        PedMind m; m.id = id;
        m.gender = genderHint; m.model = modelHint; m.lang = defaultLang;
        m.name = Vocab::NameFor(genderHint, rng);
        float r = rnd();
        m.trait = r < .35f ? Trait::Friendly : r < .55f ? Trait::Grumpy : r < .70f ? Trait::Criminal
                : r < .85f ? Trait::Nervous : Trait::Cocky;
        m.happy = 30 + rnd() * 50; m.anger = rnd() * 40; m.fear = rnd() * 40; m.greed = rnd() * 60;
        if (m.trait == Trait::Criminal) m.greed += 30;
        if (m.trait == Trait::Grumpy)   m.anger += 25;
        if (m.trait == Trait::Nervous)  m.fear  += 25;
        m.gang = gangHint; m.relation = relHint; m.pname = pnameHint;
        if (m.relation >= 2)       { m.trait = Trait::Friendly; m.happy = std::max(m.happy, 75.f); m.anger = std::min(m.anger, 8.f);  m.fear = std::min(m.fear, 8.f); }
        else if (m.relation == 1)  { m.happy = std::max(m.happy, 60.f); m.anger = std::min(m.anger, 20.f); }
        else if (m.relation == -1) { m.anger = std::max(m.anger, 40.f); m.happy = std::min(m.happy, 50.f); if (m.trait == Trait::Friendly) m.trait = Trait::Grumpy; }
        else if (m.relation <= -2) { m.trait = Trait::Cocky; m.anger = std::max(m.anger, 65.f); m.fear = std::min(m.fear, 8.f); m.happy = std::min(m.happy, 30.f); }
        m.clamp();
        return minds.emplace(id, m).first->second;
    }

    // Ped dipukul / memukul player -> marah selama 60 detik
    void provoke(PedMind& m) { if (m.aggroT <= 0) m.aggroSay = true; m.aggroT = 60.f; m.anger = 95.f; m.happy = 5.f; m.fear = std::min(m.fear, 8.f); }

    // Mood drift pelan-pelan (panggil tiap frame dengan dt detik)
    void tick(float dt) {
        for (auto& kv : minds) {
            PedMind& m = kv.second;
            if (m.aggroT > 0) { m.aggroT -= dt; if (m.aggroT < 0) m.aggroT = 0; }
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
        m.cooldown = 8 + rnd() * 12;
        if (m.aggroT > 0) return rnd() < .6f ? Act::Insult : Act::None;    // lagi marah: ngebentak, bukan menyapa                       // jangan spam
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
        pInsult *= (m.relation <= -1 ? 2.2f : m.relation >= 1 ? 0.f : 1.f);
        if (dist < 8 && r < pInsult) return Act::Insult;
        r = rnd();
        float pGreet = (m.happy / 100.f) * .3f * (m.trait == Trait::Friendly ? 1.5f : .5f) * (m.knowsPlayer ? 1.4f : 1.f);
        pGreet *= (m.relation >= 1 ? 2.0f : m.relation <= -1 ? 0.5f : 1.f);
        if (dist < 8 && r < pGreet) return Act::Greet;
        return Act::None;
    }

    // Fallback offline kalau server AI nggak ada / timeout
    std::string offlineLineID(const PedMind& m, Act a, const std::string& playerSays) {
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
    std::string offlineChatID(const PedMind& m, const std::string& said, int& dH, int& dA, int& dF) {
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


    // ---------- Konteks untuk mesin kosakata ----------
    Vocab::Ctx ctxOf(const PedMind& m) {
        Vocab::Ctx c; c.happy = m.happy; c.anger = m.anger; c.fear = m.fear; c.trait = (int)m.trait;
        c.name = m.name; c.knows = m.knowsPlayer; c.times = m.timesTalked;
        c.gang = m.gang; c.rel = m.relation; c.pname = m.pname; c.aggro = m.aggroT > 0;
        for (int i = (int)m.history.size() - 1; i >= 0 && c.recent.size() < 12; i--)
            if (m.history[i].rfind("N: ", 0) == 0) c.recent.push_back(m.history[i].substr(3));
        return c;
    }
    std::string vocabReply(const PedMind& m, const std::string& said, Lang lang, int& dH, int& dA, int& dF) {
        Vocab::Ctx c = ctxOf(m);
        return Vocab::Reply(c, said, (int)lang, rng, dH, dA, dF);
    }

    // ---------- Sapaan/olokan/gumaman spontan (bahasa mengikuti player; default Inggris) ----------
    std::string offlineLine(const PedMind& m, Act a, const std::string& playerSays) {
        Vocab::Ctx c = ctxOf(m); int lang = (int)m.lang;
        switch (a) {
            case Act::Greet:  return Vocab::Spontaneous(c, lang, rng() % 100 < 22 ? 2 : 0, rng);   // kadang malah gumam random
            case Act::Insult: return Vocab::Spontaneous(c, lang, 1, rng);
            case Act::Rob: { static const char* r[] = {"Wallet. NOW!", "Don't move! Hand over the cash!", "Empty your pockets, pal!"}; return r[rng() % 3]; }
            default: return "";
        }
    }

    // ---------- Balasan chat offline: Inggris (default) ----------
    std::string offlineChatEN(const PedMind& m, const std::string& said, int& dH, int& dA, int& dF) {
        std::string t = LowerPad(said);
        std::string last;
        for (int i = (int)m.history.size() - 1; i >= 0; i--) if (m.history[i].rfind("N: ", 0) == 0) { last = m.history[i].substr(3); break; }
        auto pick = [&](std::vector<std::string> v) {
            for (int k = 0; k < 8; k++) { const std::string& c = v[rng() % v.size()]; if (c != last) return c; }
            return v[0];
        };
        bool angry = m.anger > 60, scared = m.fear > 60, happy = m.happy > 65;
        bool nervous = m.trait == Trait::Nervous, cocky = m.trait == Trait::Cocky, crim = m.trait == Trait::Criminal;
        const std::string& n = m.name;
        dH = dA = dF = 0;
        if (HasAny(t, {"kill you", "shoot you", "i'll kill", "gonna kill", "beat you", "i'll hurt", "you're dead", "you are dead", "bury you"})) {
            dF = 25; dA = 10; dH = -15;
            if (scared || nervous) return pick({"Whoa, easy man! I don't want any trouble!", "P-please don't hurt me, I'll just go!", "Okay okay, I'm leaving, just stay calm!"});
            if (cocky || crim)     return pick({"You really wanna do this? Bad idea, pal.", "I've dealt with tougher guys than you.", "Try me. See what happens."});
            return pick({"Hey, back off. I'll call the cops!", "Watch your mouth, buddy.", "Not cool, man. Not cool at all."});
        }
        if (HasAny(t, {"idiot", "stupid", "dumb", "asshole", "bitch", "fuck you", "loser", "ugly", "shut up", "moron", "jerk", "bastard"})) {
            dA = 20; dH = -15;
            if (nervous) return pick({"Wow... that was rude. What did I do?", "Okay, okay, no need to yell.", "I'm just gonna walk away now."});
            if (cocky || angry || m.trait == Trait::Grumpy) return pick({"Say that again, I dare you!", "Big mouth for someone who doesn't know me.", "Careful, pal. I'm not in the mood."});
            return pick({"Damn, that was uncalled for.", "Chill out, man. I didn't do anything to you.", "Rough day, huh?"});
        }
        if (HasAny(t, {"thank", "thanks", "thx", "appreciate", "awesome", "cool", "nice", "great job"})) {
            dH = 12; dA = -8;
            return pick({"No problem, buddy!", "Anytime, man. Take it easy.", "Heh, you're welcome. Stay safe out here."});
        }
        if (HasAny(t, {"bye", "goodbye", "see you", "see ya", "gotta go", "later", "i'm leaving", "take care"})) {
            return pick({"Alright, take care out there.", "See you around, man.", m.knowsPlayer ? "Don't be a stranger, alright?" : "Take it easy."});
        }
        if (HasAny(t, {"your name", "who are you", "what's your name", "whats your name", "who're you", "introduce"})) {
            dH = 3;
            if (angry) return pick({"Why do you wanna know? It's " + n + ", alright?", "Name's " + n + ". Happy now?"});
            return pick({"I'm " + n + ". And you?", "Name's " + n + ". Been hanging around this block for years.", "Call me " + n + "."});
        }
        if (HasAny(t, {"how are you", "how's it going", "hows it going", "what's up", "whats up", "how you doing", "how are things", "how do you do"})) {
            dH = 4;
            if (angry)  return pick({"Terrible. Today's been nothing but headaches.", "Don't ask. I'm in a rotten mood."});
            if (scared) return pick({"A little on edge, honestly. This neighborhood isn't always safe.", "I'm fine... just keeping my eyes open."});
            if (happy)  return pick({"Pretty damn good, man! Sun's out, nobody's bothering me.", "Can't complain! How about you?", "Living the dream, buddy."});
            return pick({"Just getting by, you know how it is.", "Same old, same old. You?", "Not bad, not great."});
        }
        if (HasAny(t, {"hello", "hi ", "hey", "yo ", "sup", "good morning", "good evening", "good afternoon", "howdy", "greetings", "test"})) {
            dH = 4;
            if (m.knowsPlayer && m.timesTalked > 3) return pick({"Well look who it is, my regular! Back again?", "Hey, my man! We talk a lot lately.", "Yo! I know that face by now."});
            if (m.knowsPlayer) return pick({"Hey, you're the one I talked to before. What's up?", "Oh, hey again. Good to see you."});
            if (angry)  return pick({"What do you want? I'm busy.", "Make it quick, pal.", "Hmph. Something you need?"});
            if (scared) return pick({"H-hey... you're not gonna cause trouble, right?", "Hi. I'm just passing through, man."});
            if (happy)  return pick({"Hey there! Beautiful day, huh?", "Yo! Good to see a friendly face.", "Hi! Anything I can help with?"});
            return pick({"Hey. What's up?", "Yo. You new around here?", "Hi there."});
        }
        if (HasAny(t, {"money", "cash", "dollar", "buck", "lend", "borrow", "loan", "broke", "rich"})) {
            if (crim)  return pick({"Money, huh? Now you're speaking my language. How much you got?", "I know a few ways to make quick cash... for a cut.", "I don't lend, but I know where the money is."});
            if (angry || m.greed > 70) return pick({"I'm broke myself, man. Ask someone else.", "Get a job, buddy."});
            return pick({"I'm tight on cash, man. Sorry.", "Nope, nothing to spare right now.", "Wish I could help, I'm flat broke."});
        }
        if (HasAny(t, {"where is", "where's", "wheres", "how do i get", "directions", "which way", "lost", "hospital", "police station", "gym", "store", "shop"})) {
            if (angry) return pick({"Do I look like a map to you?", "Ask someone else, I'm not a tour guide."});
            return pick({"Sorry, I'm not from around here.", "Just keep going straight, you'll find it. Probably.", "I only know this block, man."});
        }
        if (HasAny(t, {"love you", "beautiful", "handsome", "pretty", "hot ", "cute", "date", "girlfriend", "boyfriend", "marry"})) {
            dH = 5;
            return pick({"Ha! Smooth. Real smooth.", "You flirting with me? Bold move.", "Careful, you'll make me blush."});
        }
        if (said.find('?') != std::string::npos) {
            if (angry)   return pick({"Too many questions. Beat it.", "Ask someone else."});
            if (nervous) return pick({"Uh... I'm not sure. Maybe?", "I don't wanna say, man."});
            if (cocky)   return pick({"I know the answer, but you couldn't handle it.", "Good question. Wrong person to ask though."});
            return pick({"Good question. Never thought about it.", "Hard to say. What do you think?", "Beats me, man."});
        }
        if (scared) return pick({"Please don't get any closer...", "You're making me uncomfortable.", "I should really get going."});
        if (angry)  return pick({"I'm not in the mood. Move along.", "Whatever, pal.", "Leave me alone."});
        if (happy)  return pick({"Ha! You're alright, you know that?", "Life's good, man.", "I like talking to you, honestly."});
        return pick({"Hmm, I see.", "Okay... and then?", "Interesting.", "I'm listening, go on.", "That's how it goes around here."});
    }

    // ---------- Balasan chat offline: Spanyol (dasar) ----------
    std::string offlineChatES(const PedMind& m, const std::string& said, int& dH, int& dA, int& dF) {
        std::string t = LowerPad(said);
        auto pick = [&](std::vector<std::string> v) { return v[rng() % v.size()]; };
        dH = dA = dF = 0;
        if (HasAny(t, {" gracias "})) { dH = 10; return pick({"¡De nada, amigo!", "Para eso estamos, hermano."}); }
        if (HasAny(t, {" adiós ", " adios ", " hasta luego "})) return pick({"Cuídate mucho.", "Nos vemos, amigo."});
        if (HasAny(t, {" nombre ", " quién eres ", " quien eres "})) return pick({"Me llamo " + m.name + ". ¿Y tú?", "Soy " + m.name + ", mucho gusto."});
        if (HasAny(t, {" cómo estás ", " como estas ", " qué tal ", " que tal "})) { dH = 3; return pick({"Aquí, sobreviviendo. ¿Y tú?", "Bien, no me quejo."}); }
        if (HasAny(t, {" hola ", " buenos "})) { dH = 4; return pick({"¡Hola! ¿Qué onda?", "¡Buenas! ¿En qué te ayudo?"}); }
        if (HasAny(t, {" dinero "})) return pick({"No tengo dinero, hermano. Lo siento.", "Estoy en la quiebra, amigo."});
        return pick({"Mmm, ya veo.", "Interesante, cuéntame más.", "Así es la vida por aquí."});
    }

    // ---------- Respons atas perintah (follow/stop/dance/...) ----------
    // Mengembalikan teks jawaban dan mengisi `action` (aksi yang benar-benar dilakukan ped, "none" kalau menolak).
    std::string intentReply(const PedMind& m, Intent in, Lang lang, std::string& action) {
        bool angry = m.anger > 60, scared = m.fear > 60 || m.trait == Trait::Nervous;
        bool stubborn = angry || m.trait == Trait::Grumpy || m.trait == Trait::Cocky || m.trait == Trait::Criminal;
        bool ok = true;
        switch (in) {
            case Intent::Follow:  ok = !stubborn || m.happy > 70; break;
            case Intent::Stop:    ok = m.anger < 70; break;
            case Intent::Leave:   ok = true; break;
            case Intent::Dance:   ok = m.happy > 40 && m.trait != Trait::Grumpy; break;
            case Intent::HandsUp: ok = scared; break;
            case Intent::Wave:    ok = true; break;
            case Intent::Flee:    ok = true; break;
            case Intent::Fight:   ok = (m.trait == Trait::Cocky || angry || m.trait == Trait::Criminal); break;
            default: ok = false; break;
        }
        if (m.relation <= -1 && (in == Intent::Follow || in == Intent::Stop || in == Intent::Dance || in == Intent::HandsUp || in == Intent::Wave)) ok = false;   // musuh tidak menurut
        if (m.relation >= 2  && (in == Intent::Follow || in == Intent::Stop || in == Intent::Dance || in == Intent::Wave)) ok = true;                           // satu geng: siap
        if (m.aggroT > 0 && in != Intent::Leave && in != Intent::Flee) ok = false;                                                                                   // lagi marah: menolak
        action = ok ? IntentName(in) : "none";
        return Vocab::IntentLine((int)in, ok, (int)lang, rng);
    }

    // ---------- Dispatcher: bahasa + maksud + mood ----------
    std::string offlineChat(const PedMind& m, const std::string& said, int& dH, int& dA, int& dF, std::string& action) {
        bool conf = false; Lang dl = DetectLang2(said, conf);
        Lang lang = conf ? dl : m.lang;                // tidak yakin -> pakai bahasa terakhir
        Intent in = DetectIntent(said);
        action = "none"; dH = dA = dF = 0;
        if (in != Intent::None) { if (in == Intent::HandsUp || in == Intent::Fight) dF = 5; return intentReply(m, in, lang, action); }
        return vocabReply(m, said, lang, dH, dA, dF);
    }

    // Prompt untuk LLM lewat proxy
    std::string buildPrompt(const PedMind& m, const std::string& playerSays, int playerMoney, int hour) {
        char buf[700];
        const char* lg = m.lang == Lang::ID ? "Indonesian" : m.lang == Lang::ES ? "Spanish" : "English";
        snprintf(buf, sizeof buf,
            "You are %s, a pedestrian in Los Santos, San Andreas (a fictional USA). Personality: %s. Current mood: %s "
            "(happy=%d anger=%d fear=%d). %s Player's cash: $%d. Game time: %02d:00. "
            "The player's last message looks like: %s. Reply in the SAME language the player writes in; if unsure, use English.\n",
            m.name.c_str(), m.traitEN(), m.moodEN(), (int)m.happy, (int)m.anger, (int)m.fear,
            m.knowsPlayer ? "You already know this player from earlier conversations." : "You don't know this player yet.",
            playerMoney, hour, lg);
        std::string p = buf;
        p += "Conversation so far:\n";
        for (auto& h : m.history) p += h + "\n";
        p += "Player: " + playerSays + "\n";
        return p;
    }
};
