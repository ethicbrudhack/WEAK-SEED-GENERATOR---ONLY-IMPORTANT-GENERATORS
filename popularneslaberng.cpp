// ============================================================
// GENERATOR SŁABYCH SEEDÓW - TYLKO WAŻNE GENERATORY
// ============================================================
// Kompilacja: g++ -O3 -march=native -o weak_generators weak_generators.cpp
// Użycie: ./weak_generators -n 10
// ============================================================

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <cstring>
#include <random>
#include <chrono>
#include <vector>
#include <unistd.h>
#include <sys/types.h>
#include <sstream>

using namespace std;

const int SEED_LENGTH = 64;

// ============================================================
// GENERATOR 1: MINSTD - 31 BITÓW (POPRAWIONY MNOŻNIK)
// ============================================================
// RZECZYWISTOŚĆ: std::minstd_rand z C++11
// SŁABOŚĆ: Tylko 31 bitów stanu (2,147,483,647 możliwości)
// ============================================================
class MINSTD {
private:
    uint32_t seed;
public:
    MINSTD() : seed(12345) {}
    
    uint32_t next_rand() {
        seed = (uint64_t)seed * 48271 % 2147483647;
        return seed;
    }
    
    string generate_seed() {
        string result;
        result.reserve(64);
        for(int i = 0; i < 8; i++) {
            uint32_t val = next_rand();
            stringstream ss;
            ss << hex << setw(8) << setfill('0') << val;
            result += ss.str();
        }
        return result;
    }
};

// ============================================================
// GENERATOR 2: RANDU - SŁYNNIE ZŁY
// ============================================================
// RZECZYWISTOŚĆ: Klasyczny zły generator z lat 60.
// SŁABOŚĆ: Silne korelacje między kolejnymi wartościami
// ============================================================
class RANDU {
private:
    uint32_t seed;
public:
    RANDU() : seed(1) {}
    
    uint32_t next_rand() {
        seed = (uint64_t)seed * 65539 % 2147483648;
        return seed;
    }
    
    string generate_seed() {
        string result;
        result.reserve(64);
        for(int i = 0; i < 8; i++) {
            uint32_t val = next_rand();
            stringstream ss;
            ss << hex << setw(8) << setfill('0') << val;
            result += ss.str();
        }
        return result;
    }
};

// ============================================================
// GENERATOR 3: Java Random - 48 BITÓW
// ============================================================
// RZECZYWISTOŚĆ: java.util.Random z OpenJDK
// SŁABOŚĆ: Tylko 48 bitów stanu, podatny na ataki brute-force
// ============================================================
class JavaRandom {
private:
    uint64_t seed;
public:
    JavaRandom() : seed(12345) {}
    
    uint32_t next_rand() {
        seed = (seed * 0x5DEECE66D + 0xB) & ((1LL << 48) - 1);
        return (uint32_t)(seed >> 16);
    }
    
    string generate_seed() {
        string result;
        result.reserve(64);
        for(int i = 0; i < 8; i++) {
            uint32_t val = next_rand();
            stringstream ss;
            ss << hex << setw(8) << setfill('0') << val;
            result += ss.str();
        }
        return result;
    }
};

// ============================================================
// GENERATOR 4: Mersenne Twister - PRAWIDŁOWA INICJALIZACJA
// ============================================================
// RZECZYWISTOŚĆ: std::mt19937 z poprawną inicjalizacją
// UWAGA: To jest BEZPIECZNY generator (pokazany dla porównania)
// ============================================================
class MersenneTwister {
private:
    mt19937 gen;
public:
    MersenneTwister() {
        random_device rd;
        gen.seed(rd());
    }
    
    uint32_t next_rand() {
        return gen();
    }
    
    string generate_seed() {
        string result;
        result.reserve(64);
        for(int i = 0; i < 8; i++) {
            uint32_t val = next_rand();
            stringstream ss;
            ss << hex << setw(8) << setfill('0') << val;
            result += ss.str();
        }
        return result;
    }
};

// ============================================================
// GENERATOR 5: Milk Sad - ZŁA INICJALIZACJA (32 BITY)
// ============================================================
// RZECZYWISTOŚĆ: Atak Milk Sad z 2023 roku
// SŁABOŚĆ: Inicjalizacja time(nullptr) daje tylko 32 bity entropii
// PRZYKŁAD: Wykorzystane do kradzieży kryptowalut o wartości ~900k USD
// ============================================================
class MilkSad {
private:
    mt19937 gen;
public:
    MilkSad() {
        gen.seed(static_cast<uint32_t>(time(nullptr)));
    }
    
    uint32_t next_rand() {
        return gen();
    }
    
    string generate_seed() {
        string result;
        result.reserve(64);
        for(int i = 0; i < 8; i++) {
            uint32_t val = next_rand();
            stringstream ss;
            ss << hex << setw(8) << setfill('0') << val;
            result += ss.str();
        }
        return result;
    }
};

// ============================================================
// GENERATOR 6: time(NULL) - 32 BITY
// ============================================================
// RZECZYWISTOŚĆ: Częsta praktyka w starszym kodzie
// SŁABOŚĆ: Tylko 32 bity entropii (czas w sekundach)
// ============================================================
class TimeSeed {
private:
    uint32_t seed;
public:
    TimeSeed() {
        seed = (uint32_t)time(NULL);
    }
    
    uint32_t next_rand() {
        seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
        return seed;
    }
    
    string generate_seed() {
        string result;
        result.reserve(64);
        for(int i = 0; i < 8; i++) {
            uint32_t val = next_rand();
            stringstream ss;
            ss << hex << setw(8) << setfill('0') << val;
            result += ss.str();
        }
        return result;
    }
};

// ============================================================
// GENERATOR 7: PID + time - 32-47 BITÓW
// ============================================================
// RZECZYWISTOŚĆ: Częsta praktyka w serwerach
// SŁABOŚĆ: PID dodaje ~15 bitów, ale to wciąż mało
// ============================================================
class PIDTimeSeed {
private:
    uint32_t seed;
public:
    PIDTimeSeed() {
        seed = (uint32_t)(time(NULL) ^ getpid());
    }
    
    uint32_t next_rand() {
        seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
        return seed;
    }
    
    string generate_seed() {
        string result;
        result.reserve(64);
        for(int i = 0; i < 8; i++) {
            uint32_t val = next_rand();
            stringstream ss;
            ss << hex << setw(8) << setfill('0') << val;
            result += ss.str();
        }
        return result;
    }
};

// ============================================================
// GENERATOR 8: Weak /dev/urandom - SYMULACJA BRAKU ENTROPII
// ============================================================
// RZECZYWISTOŚĆ: Sytuacja we wczesnej fazie bootowania systemu
// SŁABOŚĆ: System nie ma entropii, używa czasu jako źródła
// ============================================================
class WeakURandom {
private:
    uint32_t seed;
public:
    WeakURandom() {
        seed = static_cast<uint32_t>(time(nullptr) & 0xFFFFFFFF);
    }
    
    uint32_t next_rand() {
        seed = (seed * 1103515245 + 12345) & 0xFFFFFFFF;
        return seed;
    }
    
    string generate_seed() {
        string result;
        result.reserve(64);
        for(int i = 0; i < 8; i++) {
            uint32_t val = next_rand();
            stringstream ss;
            ss << hex << setw(8) << setfill('0') << val;
            result += ss.str();
        }
        return result;
    }
};

// ============================================================
// GŁÓWNA FUNKCJA
// ============================================================
int main(int argc, char* argv[]) {
    cout << string(80, '=') << endl;
    cout << "GENERATOR SŁABYCH SEEDÓW - TYLKO WAŻNE GENERATORY" << endl;
    cout << string(80, '=') << endl;
    
    string filename = "weak_seeds.txt";
    int seeds_per_generator = 10;
    
    for (int i = 1; i < argc; ++i) {
        if (strcmp(argv[i], "-h") == 0) {
            cout << "\nUŻYCIE: ./weak_generators -n <liczba>" << endl;
            cout << "  -n <liczba>  Liczba seedów na generator" << endl;
            cout << "  -f <plik>   Nazwa pliku" << endl;
            return 0;
        } else if (strcmp(argv[i], "-n") == 0 && i + 1 < argc) {
            seeds_per_generator = atoi(argv[++i]);
        } else if (strcmp(argv[i], "-f") == 0 && i + 1 < argc) {
            filename = argv[++i];
        }
    }
    
    ofstream clear_file(filename, ios::trunc);
    clear_file.close();
    
    cout << "\n📁 Zapisuję do: " << filename << endl;
    cout << "📊 Generuję " << seeds_per_generator << " seedów na generator\n" << endl;
    
    ofstream file(filename, ios::app);
    if (!file.is_open()) {
        cerr << "❌ Nie można otworzyć pliku!" << endl;
        return 1;
    }
    
    MINSTD gen1;
    RANDU gen2;
    JavaRandom gen3;
    MersenneTwister gen4;
    MilkSad gen5;
    TimeSeed gen6;
    PIDTimeSeed gen7;
    WeakURandom gen8;
    
    vector<pair<string, string>> generators = {
        {"MINSTD", "31 bitów entropii"},
        {"RANDU", "Słynnie zły - wzór widoczny!"},
        {"Java Random", "48 bitów entropii"},
        {"Mersenne Twister (POPRAWNY)", "Bezpieczny (random_device)"},
        {"Milk Sad", "32 bity entropii (time(nullptr)) - atak 2023!"},
        {"time(NULL)", "32 bity entropii"},
        {"PID + time", "32-47 bitów entropii"},
        {"Weak /dev/urandom", "Symulacja braku entropii"}
    };
    
    for(int g = 0; g < 8; g++) {
        cout << "🔹 " << generators[g].first << endl;
        cout << "   " << generators[g].second << endl;
        
        string first_seed;
        for(int i = 0; i < seeds_per_generator; i++) {
            string seed;
            switch(g) {
                case 0: seed = gen1.generate_seed(); break;
                case 1: seed = gen2.generate_seed(); break;
                case 2: seed = gen3.generate_seed(); break;
                case 3: seed = gen4.generate_seed(); break;
                case 4: seed = gen5.generate_seed(); break;
                case 5: seed = gen6.generate_seed(); break;
                case 6: seed = gen7.generate_seed(); break;
                case 7: seed = gen8.generate_seed(); break;
            }
            file << seed << "\n";
            if (i == 0) first_seed = seed;
        }
        
        cout << "   Przykład: " << first_seed.substr(0, 20) 
             << "..." << first_seed.substr(44) << endl;
        cout << endl;
    }
    
    file.close();
    
    cout << string(80, '-') << endl;
    cout << "✅ Wygenerowano " << (8 * seeds_per_generator) 
         << " seedów do pliku: " << filename << endl;
    cout << "\n⚠️  OSTRZEŻENIE: Te seedy WYGLĄDAJĄ na 256-bitowe" << endl;
    cout << "   ale mają MAŁĄ ENTROPIĘ (15-48 bitów)!" << endl;
    cout << "\n📖 LEGENDA:" << endl;
    cout << "   - Milk Sad - konkretny atak z 2023 roku (kradzież ~900k USD)" << endl;
    cout << "   - MINSTD - 31 bitów (zgodny z C++11)" << endl;
    cout << string(80, '=') << endl;
    
    return 0;
}