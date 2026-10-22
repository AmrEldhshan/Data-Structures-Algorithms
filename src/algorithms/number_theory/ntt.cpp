#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

// ---------------------------------------------------------------------------
// Number-theoretic transform (NTT)
//
// NTT is the modular-integer version of the FFT. It evaluates a polynomial at
// the powers of a primitive root of unity modulo a prime, multiplies the values
// pointwise, and interpolates back. With modulus 998244353 and primitive root 3,
// lengths up to 2^23 are supported.
//
// Time:  O(n log n)
// Space: O(n)
// ---------------------------------------------------------------------------
using int64 = long long;

const int MOD = 998244353;
const int PRIMITIVE_ROOT = 3;

int64 modPower(int64 base, int64 exponent, int64 modulus) {
    int64 result = 1;
    base %= modulus;

    while (exponent > 0) {
        if (exponent & 1) result = result * base % modulus;
        base = base * base % modulus;
        exponent >>= 1;
    }

    return result;
}

void ntt(vector<int64>& values, bool invert) {
    int n = static_cast<int>(values.size());

    for (int i = 1, j = 0; i < n; ++i) {
        int bit = n >> 1;
        for (; j & bit; bit >>= 1) j ^= bit;
        j ^= bit;
        if (i < j) swap(values[i], values[j]);
    }

    for (int length = 2; length <= n; length <<= 1) {
        int64 root = modPower(PRIMITIVE_ROOT, (MOD - 1) / length, MOD);
        if (invert) root = modPower(root, MOD - 2, MOD);

        for (int start = 0; start < n; start += length) {
            int64 current = 1;

            for (int offset = 0; offset < length / 2; ++offset) {
                int64 even = values[start + offset];
                int64 odd = values[start + offset + length / 2] * current % MOD;

                values[start + offset] = (even + odd) % MOD;
                values[start + offset + length / 2] =
                    (even - odd + MOD) % MOD;

                current = current * root % MOD;
            }
        }
    }

    if (invert) {
        int64 inverseN = modPower(n, MOD - 2, MOD);
        for (int64& value : values) value = value * inverseN % MOD;
    }
}

vector<int64> multiplyPolynomials(const vector<int64>& a,
                                  const vector<int64>& b) {
    if (a.empty() || b.empty()) return {};

    int resultSize = static_cast<int>(a.size() + b.size() - 1);
    int size = 1;
    while (size < resultSize) size <<= 1;

    vector<int64> left(a.begin(), a.end());
    vector<int64> right(b.begin(), b.end());
    left.resize(size, 0);
    right.resize(size, 0);

    ntt(left, false);
    ntt(right, false);

    for (int i = 0; i < size; ++i) left[i] = left[i] * right[i] % MOD;

    ntt(left, true);
    left.resize(resultSize);
    return left;
}

int main() {
    vector<int64> a = {1, 2, 3, 4};
    vector<int64> b = {5, 6, 7};

    vector<int64> product = multiplyPolynomials(a, b);

    cout << "a(x) = 1 + 2x + 3x^2 + 4x^3\n";
    cout << "b(x) = 5 + 6x + 7x^2\n";
    cout << "a(x) * b(x) = ";

    for (size_t i = 0; i < product.size(); ++i) {
        if (i != 0) cout << " + ";
        cout << product[i] << "x^" << i;
    }
    cout << '\n';

    return 0;
}
