#include <iostream>
#include <cmath>
using namespace std;

bool isPrimeTrial(int n) {
    if (n <= 1) return false;
    for (int i = 2; i*i <= n; i++) {
        if (n % i == 0) return false;
    }
    return true;
}

int main() {
    int n = 29;
    cout << (isPrimeTrial(n) ? "Prime" : "Not Prime") << endl;
}
