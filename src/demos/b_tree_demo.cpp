#include "data_structures/trees/b_tree.h"

#include <iostream>

using namespace std;

int main() {
    BTree<int> tree(2);
    for (int value : {10, 20, 5, 6, 12, 30, 7, 17, 3, 25, 18, 40, 1}) {
        tree.insert(value);
    }

    cout << "size = " << tree.size() << '\n';
    cout << "in-order: ";
    for (int value : tree.inOrder()) cout << value << ' ';
    cout << '\n';

    for (int value : {6, 17, 41}) {
        cout << "contains " << value << ": " << boolalpha
             << tree.contains(value) << '\n';
    }

    return 0;
}
