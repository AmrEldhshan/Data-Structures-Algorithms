#ifndef DSA_NUMBER_THEORY_H
#define DSA_NUMBER_THEORY_H

#include <stdexcept>
#include <utility>
#include <vector>

// ---------------------------------------------------------------------------
// Number theory helpers
//
// All functions use 64-bit integers. Modular multiplication is safe for
// moduli below roughly 3 * 10^9 because (mod - 1)^2 still fits in long long.
// ---------------------------------------------------------------------------
namespace number_theory {

// Greatest common divisor (Euclid). gcd(0, 0) is defined as 0.
inline long long gcd(long long a, long long b) {
    if (a < 0) a = -a;
    if (b < 0) b = -b;
    while (b != 0) {
        long long remainder = a % b;
        a = b;
        b = remainder;
    }
    return a;
}

// Least common multiple. Divides first to reduce the chance of overflow.
inline long long lcm(long long a, long long b) {
    if (a == 0 || b == 0) return 0;
    return (a / gcd(a, b)) * b;
}

struct ExtendedGcd {
    long long gcd;
    long long x;
    long long y;
};

// Finds x and y such that a * x + b * y = gcd(a, b).
inline ExtendedGcd extendedGcd(long long a, long long b) {
    if (b == 0) return {a, 1, 0};

    ExtendedGcd previous = extendedGcd(b, a % b);
    return {previous.gcd, previous.y, previous.x - (a / b) * previous.y};
}

// (base ^ exponent) mod modulus, using binary exponentiation.
inline long long modPow(long long base, long long exponent, long long modulus) {
    if (modulus <= 0) throw std::invalid_argument("modPow: modulus must be positive");

    long long result = 1 % modulus;
    base %= modulus;
    if (base < 0) base += modulus;

    while (exponent > 0) {
        if (exponent & 1) result = result * base % modulus;
        base = base * base % modulus;
        exponent >>= 1;
    }

    return result;
}

// Modular inverse of a modulo m. Throws when gcd(a, m) != 1.
inline long long modInverse(long long a, long long modulus) {
    ExtendedGcd result = extendedGcd(a, modulus);
    if (result.gcd != 1) {
        throw std::invalid_argument("modInverse: a and modulus must be coprime");
    }

    long long inverse = result.x % modulus;
    if (inverse < 0) inverse += modulus;
    return inverse;
}

// Euler's totient: count of integers in [1, n] coprime to n.
inline long long totient(long long n) {
    if (n <= 0) throw std::invalid_argument("totient: n must be positive");

    long long result = n;
    for (long long factor = 2; factor * factor <= n; ++factor) {
        if (n % factor != 0) continue;

        while (n % factor == 0) n /= factor;
        result -= result / factor;
    }

    if (n > 1) result -= result / n;
    return result;
}

// Prime factorisation as (factor, exponent) pairs, in increasing order.
inline std::vector<std::pair<long long, int>> factorize(long long n) {
    if (n <= 0) throw std::invalid_argument("factorize: n must be positive");

    std::vector<std::pair<long long, int>> factors;

    for (long long factor = 2; factor * factor <= n; ++factor) {
        if (n % factor != 0) continue;

        int exponent = 0;
        while (n % factor == 0) {
            n /= factor;
            ++exponent;
        }
        factors.push_back({factor, exponent});
    }

    if (n > 1) factors.push_back({n, 1});
    return factors;
}

// n choose r modulo a prime modulus (n must be smaller than modulus).
inline long long binomialMod(int n, int r, long long modulus) {
    if (r < 0 || r > n) return 0;

    std::vector<long long> factorial(n + 1, 1);
    for (int i = 1; i <= n; ++i) {
        factorial[i] = factorial[i - 1] * i % modulus;
    }

    long long denominator = factorial[r] * factorial[n - r] % modulus;
    return factorial[n] * modInverse(denominator, modulus) % modulus;
}

// Catalan number C_n = (1 / (n + 1)) * binom(2n, n).
inline long long catalan(int n) {
    if (n < 0) throw std::invalid_argument("catalan: n must be non-negative");

    long long result = 1;
    for (int i = 0; i < n; ++i) {
        result = result * (2LL * (2 * i + 1)) / (i + 2);
    }
    return result;
}

} // namespace number_theory

#endif // DSA_NUMBER_THEORY_H
