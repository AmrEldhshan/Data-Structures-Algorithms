#include "algorithms/number_theory/number_theory.h"

#include <iostream>
#include <numeric>
#include <vector>

using namespace std;
using namespace number_theory;

// ---------------------------------------------------------------------------
// Chinese remainder theorem (pairwise coprime moduli)
//
// Solve:
//   x = a1 (mod m1)
//   x = a2 (mod m2)
//   ...
//
// Let M = m1 * m2 * ... * mk. For each i:
//   Mi = M / mi
//   x += ai * Mi * inverse(Mi mod mi)   (mod M)
//
// The answer is unique modulo M.
// ---------------------------------------------------------------------------
long long chineseRemainder(const vector<long long>& remainders,
                           const vector<long long>& moduli) {
    if (remainders.size() != moduli.size() || remainders.empty()) {
        throw invalid_argument("chineseRemainder: mismatched input");
    }

    long long product = 1;
    for (long long modulus : moduli) product *= modulus;

    long long result = 0;
    for (size_t i = 0; i < remainders.size(); ++i) {
        long long partial = product / moduli[i];
        long long inverse = modInverse(partial % moduli[i], moduli[i]);
        result = (result + remainders[i] * partial % product * inverse) % product;
    }

    return (result % product + product) % product;
}

int main() {
    // x = 2 (mod 3), x = 3 (mod 5), x = 2 (mod 7)
    vector<long long> remainders = {2, 3, 2};
    vector<long long> moduli = {3, 5, 7};

    long long x = chineseRemainder(remainders, moduli);

    cout << "system:\n";
    for (size_t i = 0; i < moduli.size(); ++i) {
        cout << "  x = " << remainders[i] << " (mod " << moduli[i] << ")\n";
    }
    cout << "\nsmallest non-negative solution: x = " << x << '\n';

    for (size_t i = 0; i < moduli.size(); ++i) {
        cout << "  check: " << x << " mod " << moduli[i] << " = "
             << x % moduli[i] << '\n';
    }

    return 0;
}
