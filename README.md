DONATE: bc1qps62cyk9f9unmdkc9k3ccj9e2h8ywfhg2j53ec

Built with ❤️ for the crypto research community.


============================================================
WEAK SEED GENERATOR - ONLY IMPORTANT GENERATORS
============================================================

DESCRIPTION:
This tool generates 64-character hex strings that LOOK like full 256-bit
seeds (64 chars = 32 bytes = 256 bits), but actually come from generators
with LOW ENTROPY (15-48 bits). These seeds are then used by AllChainScanner
to generate private keys and addresses.

🔴 THEY LOOK LIKE 256 BITS, BUT HAVE ONLY 15-48 BITS OF ENTROPY!

GENERATOR LIST:

1. MINSTD - 31 bits of entropy
   - Reality: std::minstd_rand from C++11
   - Weakness: Only 31 bits of state (2,147,483,647 possibilities)
   - Example: 2e52a25a5c8b9e4c...

2. RANDU - FAMOUSLY BAD (1960s)
   - Reality: Classic bad generator
   - Weakness: Strong correlations between values
   - Example: 65665e3265fe5c32...

3. Java Random - 48 bits of entropy
   - Reality: java.util.Random from OpenJDK
   - Weakness: Only 48 bits of state
   - Example: 2e52a25a5c8b9e4c...

4. Mersenne Twister (CORRECT) - SECURE
   - Reality: std::mt19937 with proper initialization
   - Note: This is SECURE (shown for comparison)
   - Example: 7f3b8a1c9d4e5f62...

5. Milk Sad - 32 bits of entropy
   - Reality: CVE-2023-31290 vulnerability
   - Weakness: Uses time(nullptr) - only 32 bits
   - Impact: $900,000+ stolen from crypto wallets
   - Example: 2e52a25a5c8b9e4c...

6. time(NULL) - 32 bits of entropy
   - Reality: Common practice in legacy code
   - Weakness: Only 32 bits (time in seconds)
   - Example: 4a1b2c3d5e6f7890...

7. PID + time - 32-47 bits of entropy
   - Reality: Common practice on servers
   - Weakness: PID adds ~15 bits, still too low
   - Example: 8c1a2b3d4e5f6078...

8. Weak /dev/urandom - Low entropy simulation
   - Reality: Early boot phase of system
   - Weakness: No entropy - uses time as source
   - Example: 6a1b2c3d4e5f6078...

============================================================
HOW IT WORKS
============================================================

Step 1: Generate weak seeds
./weak_generators -n 10 -f weak_seeds.txt

Step 2: Feed to AllChainScanner
./AllChainScanner -f weak_seeds.txt -o found.txt -t all

Step 3: Scanner converts each 64-char hex to:
- Private keys (SECP256K1 curve)
- Public keys (elliptic curve multiplication)
- Addresses (BTC: 1..., 3..., bc1...)
- Addresses (ETH: 0x...)
- Checks against blockchain for balance

============================================================
WHY THIS WORKS - VULNERABILITY EXPLANATION
============================================================

The generated seeds LOOK like:
2e52a25a5c8b9e4c8f1a2b3c4d5e6f708a1b2c3d4e5f6078a9b0c1d2e3f4a5b6

But actually come from:
MINSTD: seed = (seed * 48271) % 2147483647
Only 31 bits → 2,147,483,647 possibilities

Compared to REAL 256-bit seed:
All possible values: 2^256 ≈ 1.16 × 10^77
Weak seed: 2^31 ≈ 2.15 × 10^9
Difference: 10^68 times smaller!

============================================================
REAL-WORLD EXAMPLES
============================================================

Milk Sad (CVE-2023-31290):
- Used in libbitcoin-explorer 3.2.0
- Generated wallets with time(nullptr)
- $900,000+ stolen from affected wallets
- Affects: BTC, ETH, LTC, DOGE, ZEC, DASH

RANDU:
- Used in IBM System/360 (1960s)
- Became legendary for its failures
- Still found in legacy systems

Java Random:
- Used in older Android wallets (2014-2016)
- Affected thousands of wallets
- Still present in some outdated systems

============================================================
COMPILATION & USAGE
============================================================

COMPILE:
g++ -O3 -march=native -o weak_generators weak_generators.cpp

USAGE:
./weak_generators -n 10 -f weak_seeds.txt

OPTIONS:
  -n <number>   Number of seeds per generator (default: 10)
  -f <file>     Output filename (default: weak_seeds.txt)
  -h            Show help

EXAMPLE:
./weak_generators -n 100 -f my_weak_seeds.txt

============================================================
INTEGRATION WITH ALLCHAINSCANNER
============================================================

LINK: https://github.com/ethicbrudhack/AllChainScanner-Bitcoin-eth-zcash-etc..-

1. Generate weak seeds:
./weak_generators -n 1000 -f weak_seeds_1k.txt

2. Run scanner:
./AllChainScanner -f weak_seeds_1k.txt -o found.txt -t all

3. Check results:
cat found.txt

Expected output:
========================================
SEED: 2e52a25a5c8b9e4c8f1a2b3c4d5e6f70...
ADDRESS: 1A1zP1eP5QGefi2DMPTfTL5SLmv7DivfNa
BALANCE: 0.5 BTC
COIN: Bitcoin
PATH: m/44'/0'/0'/0/0
========================================

============================================================
SUPPORTED COINS BY ALLCHAINSCANNER
============================================================

BTC:    1..., 3..., bc1...
ETH:    0x...
LTC:    L..., M...
DOGE:   D...
DASH:   X...
ZEC:    t1..., t3...
BCH:    1..., 3..., bitcoincash:...
BNB:    0x...
MATIC:  0x...
AVAX:   0x...

============================================================
STATISTICS COMPARISON
============================================================

Generator    | Entropy   | Possibilities    | Time to Brute Force*
-------------|-----------|------------------|----------------------
REAL 256-bit | 256 bits  | 1.16 × 10^77     | Impossible (billions of years)
MINSTD       | 31 bits   | 2.15 × 10^9      | ~4 seconds
RANDU        | 31 bits   | 2.15 × 10^9      | ~4 seconds  
Java Random  | 48 bits   | 2.81 × 10^14     | ~3 weeks
Milk Sad     | 32 bits   | 4.29 × 10^9      | ~8 seconds
time(NULL)   | 32 bits   | 4.29 × 10^9      | ~8 seconds
PID+time     | 32-47 bits| 4.29 × 10^9      | ~3 weeks (worst case)
Weak /dev    | 32 bits   | 4.29 × 10^9      | ~8 seconds

*Based on:
- 150,000 seeds/sec on RTX 4090 (24-word mnemonics)
- 6,000,000 seeds/sec on RTX 4090 (BIP32 mode)
- Times are for scanning ALL possibilities

MINSTD (31 bits):
2,147,483,647 / 6,000,000 = ~358 seconds = ~6 minutes (BIP32 mode)
2,147,483,647 / 150,000 = ~14,316 seconds = ~4 hours (24-word mode)

Milk Sad (32 bits):
4,294,967,296 / 6,000,000 = ~716 seconds = ~12 minutes (BIP32 mode)
4,294,967,296 / 150,000 = ~28,633 seconds = ~8 hours (24-word mode)

Java Random (48 bits):
281,474,976,710,656 / 6,000,000 = ~46,912,496 seconds = ~1.5 years (BIP32 mode)
281,474,976,710,656 / 150,000 = ~1,876,499,844 seconds = ~59 years (24-word mode)

============================================================
WARNING
============================================================

⚠️  THESE SEEDS LOOK LEGITIMATE BUT ARE WEAK!
⚠️  ONLY TEST ON ADDRESSES YOU OWN!
⚠️  DO NOT USE FOR ILLEGAL ACTIVITIES!

The seeds generated by this tool are:
- Hex strings of 64 characters
- Exactly same length as real 256-bit seeds
- But come from generators with LOW ENTROPY
- Can be cracked in seconds to months

============================================================
REAL 256-BIT SEED vs WEAK SEED
============================================================

REAL SEED (256 bits):
b8c9d4e5f6078a9b0c1d2e3f4a5b6078c9d4e5f6078a9b0c1d2e3f4a5b6078c9d4
← 64 chars of RANDOM data (2^256 possibilities)

WEAK SEED (31 bits):
2e52a25a5c8b9e4c8f1a2b3c4d5e6f708a1b2c3d4e5f6078a9b0c1d2e3f4a5b6
← Looks the same! But comes from MINSTD (2^31 possibilities)

============================================================
RESOURCES
============================================================

CVE-2023-31290: https://nvd.nist.gov/vuln/detail/CVE-2023-31290
Milk Sad:      https://milksad.info
AllChainScanner: https://github.com/ethicbrudhack/AllChainScanner-Bitcoin-eth-zcash-etc..-

============================================================
LICENSE
============================================================

MIT License - Educational and research purposes only

============================================================

============================================================
