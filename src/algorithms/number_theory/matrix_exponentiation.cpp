#include "data_structures/matrix/matrix.h"

#include <iostream>
#include <vector>

using namespace std;

// ---------------------------------------------------------------------------
// Matrix exponentiation
//
// Raise a matrix to a large power in O(log exponent) matrix multiplications by
// repeatedly squaring the base. The classic application is linear recurrences:
//
//   [F(n+1)]   [1 1]^n   [F(1)]
//   [F(n)  ] = [1 0]   * [F(0)]
//
// Time:  O(k^3 log n) for k x k matrices
// Space: O(k^2)
// ---------------------------------------------------------------------------
using Matrix64 = Matrix<long long>;

Matrix64 multiplyMod(const Matrix64& a, const Matrix64& b, long long modulus) {
    Matrix64 result(a.rows(), b.columns(), 0);

    for (int i = 0; i < a.rows(); ++i) {
        for (int k = 0; k < a.columns(); ++k) {
            long long left = a(i, k);
            if (left == 0) continue;

            for (int j = 0; j < b.columns(); ++j) {
                result(i, j) = (result(i, j) + left * b(k, j)) % modulus;
            }
        }
    }

    return result;
}

Matrix64 matrixPower(Matrix64 base, long long exponent, long long modulus) {
    Matrix64 result = Matrix64::identity(base.rows());

    while (exponent > 0) {
        if (exponent & 1) result = multiplyMod(result, base, modulus);
        base = multiplyMod(base, base, modulus);
        exponent >>= 1;
    }

    return result;
}

int main() {
    const long long mod = 1'000'000'007;

    Matrix64 transform(2, 2, 0);
    transform(0, 0) = 1;
    transform(0, 1) = 1;
    transform(1, 0) = 1;

    for (long long n : {10LL, 90LL, 1'000'000'000'000LL}) {
        Matrix64 power = matrixPower(transform, n, mod);

        // [F(n+1), F(n)]^T = transform^n * [F(1), F(0)]^T
        long long fibN = power(1, 0); // F(1) = 1, F(0) = 0
        cout << "F(" << n << ") mod " << mod << " = " << fibN << '\n';
    }

    return 0;
}
