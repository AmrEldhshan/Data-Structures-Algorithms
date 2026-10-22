#include <iostream>
#include <string>
#include <vector>

using namespace std;

// ---------------------------------------------------------------------------
// Rabin-Karp
//
// Compare a rolling hash of the pattern with the hash of every window of the
// text. When the hashes match, verify the characters to rule out a collision.
//
// hash("abc") = (a * B^2 + b * B + c) mod M
//
// A window slides by removing the left character and adding the right one, so
// each step costs O(1).
//
// Time:  O(n + m) expected, O(n * m) worst case (many collisions)
// Space: O(1) extra
// ---------------------------------------------------------------------------
const long long BASE = 257;
const long long MOD = 1'000'000'007;

long long power(long long base, long long exponent) {
    long long result = 1;
    base %= MOD;
    while (exponent > 0) {
        if (exponent & 1) result = result * base % MOD;
        base = base * base % MOD;
        exponent >>= 1;
    }
    return result;
}

vector<int> rabinKarp(const string& text, const string& pattern) {
    vector<int> matches;
    int n = static_cast<int>(text.size());
    int m = static_cast<int>(pattern.size());
    if (m == 0 || m > n) return matches;

    long long patternHash = 0;
    long long windowHash = 0;

    for (int i = 0; i < m; ++i) {
        patternHash = (patternHash * BASE + pattern[i]) % MOD;
        windowHash = (windowHash * BASE + text[i]) % MOD;
    }

    long long highestPower = power(BASE, m - 1);

    for (int start = 0; start + m <= n; ++start) {
        if (windowHash == patternHash) {
            // Hashes match: confirm with a real comparison.
            if (text.compare(start, m, pattern) == 0) {
                matches.push_back(start);
            }
        }

        if (start + m < n) {
            windowHash = (windowHash - text[start] * highestPower % MOD + MOD) % MOD;
            windowHash = (windowHash * BASE + text[start + m]) % MOD;
        }
    }

    return matches;
}

int main() {
    string text = "ABABDABACDABABCABAB";
    string pattern = "ABAB";

    cout << "text:    " << text << '\n';
    cout << "pattern: " << pattern << "\n\n";

    cout << "matches at indices: ";
    for (int index : rabinKarp(text, pattern)) cout << index << ' ';
    cout << '\n';

    return 0;
}
