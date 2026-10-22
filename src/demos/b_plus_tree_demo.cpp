#include "data_structures/trees/b_plus_tree.h"

#include <iostream>

using namespace std;

int main() {
    BPlusTree<int> tree(4);
    for (int value : {10, 20, 5, 6, 12, 30, 7, 17, 3, 25}) tree.insert(value);

    cout << "size = " << tree.size() << '\n';
    cout << "leaf order: ";
    for (int value : tree.values()) cout << value << ' ';
    cout << '\n';

    for (int value : {6, 17, 99}) {
        cout << "contains " << value << ": " << boolalpha
             << tree.contains(value) << '\n';
    }

    return 0;
}
