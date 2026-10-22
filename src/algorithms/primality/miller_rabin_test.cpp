#include <iostream>
#include <cstdlib>
using namespace std;

long long power(long long a, long long b, long long mod) {
    long long res = 1;
    a %= mod;
    while (b) {
        if (b & 1) res = (res*a) % mod;
        a = (a*a) % mod;
        b >>= 1;
    }
    return res;
}

bool millerTest(long long d, long long n) {
    long long a = 2 + rand() % (n - 4);
    long long x = power(a, d, n);
    if (x == 1 || x == n-1) return true;
    while (d != n-1) {
        x = (x*x) % n;
        d *= 2;
        if (x == 1) return false;
        if (x == n-1) return true;
    }
    return false;
}

bool isPrimeMR(long long n, int k=5) {
    if (n <= 1 || n == 4) return false;
    if (n <= 3) return true;
    long long d = n-1;
    while (d % 2 == 0) d /= 2;
    for (int i = 0; i < k; i++)
        if (!millerTest(d, n)) return false;
    return true;
}

int main() {
    long long n = 29;
    cout << (isPrimeMR(n) ? "Probable Prime" : "Composite") << endl;
}
