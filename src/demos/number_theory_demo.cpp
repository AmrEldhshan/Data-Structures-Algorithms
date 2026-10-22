#include "algorithms/number_theory/number_theory.h"

#include <iostream>
#include <utility>
#include <vector>

using namespace std;
using namespace number_theory;

int main() {
    long long a = 30;
    long long b = 18;
    cout << "gcd(" << a << ", " << b << ") = " << gcd(a, b) << '\n';
    cout << "lcm(" << a << ", " << b << ") = " << lcm(a, b) << '\n';

    ExtendedGcd extended = extendedGcd(a, b);
    cout << "extended gcd: " << a << " * " << extended.x << " + " << b
         << " * " << extended.y << " = " << extended.gcd << '\n';

    long long base = 3;
    long long exponent = 200;
    long long modulus = 1'000'000'007;
    cout << "\n" << base << "^" << exponent << " mod " << modulus << " = "
         << modPow(base, exponent, modulus) << '\n';
    cout << "inverse of " << base << " mod " << modulus << " = "
         << modInverse(base, modulus) << '\n';
    cout << "check: " << base * modInverse(base, modulus) % modulus << '\n';

    long long n = 36;
    cout << "\ntotient(" << n << ") = " << totient(n) << '\n';

    cout << "prime factors of " << n << ": ";
    for (const auto& [factor, power] : factorize(n)) {
        cout << factor << "^" << power << ' ';
    }
    cout << '\n';

    cout << "\nC(10, 3) mod " << modulus << " = "
         << binomialMod(10, 3, modulus) << '\n';
    cout << "Catalan(10) = " << catalan(10) << '\n';

    return 0;
}
