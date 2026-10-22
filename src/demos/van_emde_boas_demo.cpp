#include "data_structures/sets/van_emde_boas.h"

#include <iostream>

using namespace std;

int main() {
    VanEmdeBoas set;
    for (int value : {3, 5, 8, 13, 21, 34}) set.insert(value);

    cout << "set size = " << set.size() << ", min = " << set.minimum()
         << ", max = " << set.maximum() << '\n';

    for (int value : {0, 3, 4, 13, 21, 40}) {
        cout << "  contains " << value << ": " << boolalpha
             << set.contains(value)
             << ", successor = " << set.successor(value)
             << ", predecessor = " << set.predecessor(value) << '\n';
    }

    set.remove(13);
    cout << "after removing 13: successor(8) = " << set.successor(8) << '\n';

    return 0;
}
