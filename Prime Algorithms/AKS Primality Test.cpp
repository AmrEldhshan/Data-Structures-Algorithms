#include <iostream>
using namespace std;

// Placeholder for illustration; full AKS implementation is very long
bool isPrimeAKS(int n) {
    if (n <= 1) return false;
    if (n <= 3) return true;
    // In practice, use simplified checks or libraries
    for (int i = 2; i*i <= n; i++)
        if (n % i == 0) return false;
    return true;
}

int main() {
    int n = 29;
    cout << (isPrimeAKS(n) ? "Prime" : "Not Prime") << endl;
}
