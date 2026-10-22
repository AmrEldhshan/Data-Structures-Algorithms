#include "data_structures/bitset/bitset.h"

#include <iostream>

using namespace std;

int main() {
    Bitset<16> bits;
    bits.set(1);
    bits.set(4);
    bits.set(9);
    bits.set(15);

    cout << "bits          = " << bits.to_string() << '\n';
    cout << "count         = " << bits.count() << '\n';
    cout << "any / none    = " << bits.any() << " / " << bits.none() << '\n';
    cout << "test(4)       = " << bits.test(4) << '\n';

    Bitset<16> other;
    other.set(4);
    other.set(0);

    cout << "\nother         = " << other.to_string() << '\n';
    cout << "bits & other  = " << (bits & other).to_string() << '\n';
    cout << "bits | other  = " << (bits | other).to_string() << '\n';
    cout << "bits ^ other  = " << (bits ^ other).to_string() << '\n';
    cout << "~bits         = " << (~bits).to_string() << '\n';

    bits.flip(1);
    bits.reset(9);
    cout << "\nafter flip(1) and reset(9): " << bits.to_string() << '\n';

    return 0;
}
