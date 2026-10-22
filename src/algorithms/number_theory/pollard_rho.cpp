#include <algorithm>
#include <iostream>
#include <random>
#include <vector>

using namespace std;

// ---------------------------------------------------------------------------
// Pollard's rho factorisation
//
// Split a composite n into a non-trivial factor using the sequence
//   x_{i+1} = x_i^2 + c (mod n)
// and gcd(|x_i - x_j|, n). The cycle-finding step is Floyd's tortoise/hare.
//
// Miller-Rabin decides when a factor is prime. The bases below are
// deterministic for all 64-bit integers.
//
// Expected time: O(n^(1/4)) per split.
// ---------------------------------------------------------------------------
using u64 = unsigned long long;

u64 addMod(u64 a, u64 b, u64 modulus) {
    // a and b are already < modulus; avoid overflow in a + b.
    return a >= modulus - b ? a - (modulus - b) : a + b;
}

u64 multiplyMod(u64 a, u64 b, u64 modulus) {
    u64 result = 0;
    a %= modulus;

    while (b > 0) {
        if (b & 1) result = addMod(result, a, modulus);
        a = addMod(a, a, modulus);
        b >>= 1;
    }

    return result;
}

u64 powerMod(u64 base, u64 exponent, u64 modulus) {
    u64 result = 1 % modulus;
    base %= modulus;

    while (exponent > 0) {
        if (exponent & 1) result = multiplyMod(result, base, modulus);
        base = multiplyMod(base, base, modulus);
        exponent >>= 1;
    }

    return result;
}

bool isPrime(u64 n) {
    if (n < 2) return false;
    for (u64 prime : {2ULL, 3ULL, 5ULL, 7ULL, 11ULL, 13ULL, 17ULL, 19ULL,
                      23ULL, 29ULL, 31ULL, 37ULL}) {
        if (n % prime == 0) return n == prime;
    }

    u64 d = n - 1;
    int power = 0;
    while ((d & 1) == 0) {
        d >>= 1;
        ++power;
    }

    // Deterministic witness set for 64-bit integers.
    for (u64 base : {2ULL, 325ULL, 9375ULL, 28178ULL, 450775ULL,
                     9780504ULL, 1795265022ULL}) {
        if (base % n == 0) continue;

        u64 x = powerMod(base, d, n);
        if (x == 1 || x == n - 1) continue;

        bool composite = true;
        for (int i = 1; i < power; ++i) {
            x = multiplyMod(x, x, n);
            if (x == n - 1) {
                composite = false;
                break;
            }
        }
        if (composite) return false;
    }

    return true;
}

u64 absoluteDifference(u64 a, u64 b) { return a > b ? a - b : b - a; }

u64 gcd(u64 a, u64 b) {
    while (b != 0) {
        u64 remainder = a % b;
        a = b;
        b = remainder;
    }
    return a;
}

u64 pollardRho(u64 n) {
    if (n % 2 == 0) return 2;
    if (n % 3 == 0) return 3;

    static mt19937_64 rng(42);

    while (true) {
        u64 c = uniform_int_distribution<u64>(1, n - 1)(rng);
        u64 x = uniform_int_distribution<u64>(0, n - 1)(rng);
        u64 y = x;
        u64 divisor = 1;

        auto step = [&](u64 value) {
            return addMod(multiplyMod(value, value, n), c, n);
        };

        while (divisor == 1) {
            x = step(x);
            y = step(step(y));
            divisor = gcd(absoluteDifference(x, y), n);
        }

        if (divisor != n) return divisor;
    }
}

void factor(u64 n, vector<u64>& factors) {
    if (n == 1) return;

    if (isPrime(n)) {
        factors.push_back(n);
        return;
    }

    u64 divisor = pollardRho(n);
    factor(divisor, factors);
    factor(n / divisor, factors);
}

int main() {
    for (u64 number : {8051ULL, 600851475143ULL, 1000000007ULL * 1000000009ULL}) {
        vector<u64> factors;
        factor(number, factors);
        sort(factors.begin(), factors.end());

        cout << number << " = ";
        for (size_t i = 0; i < factors.size(); ++i) {
            if (i != 0) cout << " * ";
            cout << factors[i];
        }
        cout << '\n';
    }

    return 0;
}
