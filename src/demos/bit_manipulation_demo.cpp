#include "algorithms/bit_manipulation/bit_manipulation.h"

#include <iostream>

using namespace std;

int main() {
    unsigned long long value = 0b10110100ULL; // 180

    cout << "value = " << value << " (binary 10110100)\n";
    cout << "set bits: " << bits::countSetBits(value) << '\n';
    cout << "bit length: " << bits::bitLength(value) << '\n';
    cout << "is power of two: "
         << (bits::isPowerOfTwo(value) ? "yes" : "no") << '\n';
    cout << "lowest set bit index: " << bits::lowestSetBitIndex(value) << '\n';
    cout << "is bit 5 set: " << (bits::isSet(value, 5) ? "yes" : "no") << '\n';

    cout << "\nafter setBit(2):    " << bits::setBit(value, 2) << '\n';
    cout << "after clearBit(5):  " << bits::clearBit(value, 5) << '\n';
    cout << "after toggleBit(0): " << bits::toggleBit(value, 0) << '\n';

    cout << "\npowers of two: ";
    for (unsigned long long candidate = 1; candidate <= 1024; candidate *= 2) {
        cout << candidate << ' ';
    }
    cout << '\n';

    return 0;
}
