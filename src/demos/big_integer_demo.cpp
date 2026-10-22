#include "data_structures/big_integer/big_integer.h"

#include <iostream>
#include <string>

using namespace std;

int main() {
    BigInteger a("123456789012345678901234567890");
    BigInteger b("987654321098765432109876543210");

    cout << "a = " << a.toString() << '\n';
    cout << "b = " << b.toString() << '\n';
    cout << "a + b = " << (a + b).toString() << '\n';
    cout << "b - a = " << (b - a).toString() << '\n';
    cout << "a - b = " << (a - b).toString() << '\n';
    cout << "a * b = " << (a * b).toString() << '\n';
    cout << "a * 3 = " << (a * BigInteger(3)).toString() << '\n';
    cout << "a * -3 = " << (a * BigInteger(-3)).toString() << '\n';

    BigInteger factorial(1);
    for (int value = 2; value <= 30; ++value) {
        factorial = factorial * BigInteger(value);
    }
    cout << "30! = " << factorial.toString() << '\n';

    return 0;
}
