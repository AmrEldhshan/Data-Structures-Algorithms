#include <bits/stdc++.h>
using namespace std;

/*
====================================================
 Bloom Filter Implementation
====================================================

A Bloom Filter is a probabilistic data structure used
to test membership in a set.

- False positives: POSSIBLE
- False negatives: IMPOSSIBLE

It answers:
  - "possibly in the set"
  - "definitely NOT in the set"

----------------------------------------------------
 PARAMETERS
----------------------------------------------------
n : expected number of elements
m : number of bits in the Bloom filter
k : number of hash functions

Optimal values:
k = (m / n) * ln(2)
m = -(n * ln(fp)) / (ln(2)^2)

----------------------------------------------------
 TIME COMPLEXITY
----------------------------------------------------
Insert: O(k)
Query : O(k)

----------------------------------------------------
 SPACE COMPLEXITY
----------------------------------------------------
O(m) bits
====================================================
*/

class BloomFilter {
private:
    int m;                  // number of bits
    int k;                  // number of hash functions
    vector<bool> bitArray;  // bit array

    /*
    ------------------------------------------------
    Hash Function Generator
    ------------------------------------------------
    We use double hashing:
    hash_i(x) = (h1(x) + i * h2(x)) % m

    This avoids defining k independent hash functions
    while still providing good distribution.
    ------------------------------------------------
    */
    size_t hash1(const string& key) const {
        return std::hash<string>{}(key);
    }

    size_t hash2(const string& key) const {
        // A second hash with a salt
        static const string salt = "bloom_filter";
        return std::hash<string>{}(key + salt);
    }

public:
    /*
    ------------------------------------------------
    Constructor
    ------------------------------------------------
    n  : expected number of elements
    fp : target false positive probability
    ------------------------------------------------
    */
    BloomFilter(int n, double fp) {
        // Compute m using: m = -(n * ln(fp)) / (ln(2)^2)
        m = static_cast<int>(-(n * log(fp)) / (log(2) * log(2)));

        // Compute k using: k = (m / n) * ln(2)
        k = static_cast<int>((m / (double)n) * log(2));

        bitArray.resize(m, false);
    }

    /*
    ------------------------------------------------
    Insert Operation
    ------------------------------------------------
    Sets k bit positions to 1
    ------------------------------------------------
    */
    void insert(const string& key) {
        size_t h1 = hash1(key);
        size_t h2 = hash2(key);

        for (int i = 0; i < k; i++) {
            size_t index = (h1 + i * h2) % m;
            bitArray[index] = true;
        }
    }

    /*
    ------------------------------------------------
    Query Operation
    ------------------------------------------------
    If ANY bit is 0 → definitely NOT in set
    If ALL bits are 1 → possibly in set
    ------------------------------------------------
    */
    bool possiblyContains(const string& key) const {
        size_t h1 = hash1(key);
        size_t h2 = hash2(key);

        for (int i = 0; i < k; i++) {
            size_t index = (h1 + i * h2) % m;
            if (!bitArray[index])
                return false;  // definitely not in set
        }
        return true; // possibly in set
    }

    /*
    ------------------------------------------------
    Debug / Info
    ------------------------------------------------
    */
    void printInfo() const {
        cout << "Bloom Filter Info:\n";
        cout << "Bits (m): " << m << "\n";
        cout << "Hash functions (k): " << k << "\n";
    }
};

/*
====================================================
 Example Usage
====================================================
*/
int main() {
    int n = 1000;         // expected number of elements
    double fp = 0.01;    // target false positive probability (1%)

    BloomFilter bf(n, fp);
    bf.printInfo();

    bf.insert("apple");
    bf.insert("banana");
    bf.insert("orange");

    cout << "\nQueries:\n";
    cout << "apple   : " << bf.possiblyContains("apple") << "\n";
    cout << "banana  : " << bf.possiblyContains("banana") << "\n";
    cout << "grape   : " << bf.possiblyContains("grape") << "\n";

    return 0;
}
