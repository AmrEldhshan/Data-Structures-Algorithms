#include <iostream>
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

bool fermatTest(int n, int k=5) {
    if (n <= 1) return false;
    for (int i = 0; i < k; i++) {
        int a = 2 + rand() % (n-3);
        if (power(a, n-1, n) != 1) return false;
    }
    return true;
}

int main() {
    int n = 29;
    cout << (fermatTest(n) ? "Probable Prime" : "Composite") << endl;
}
