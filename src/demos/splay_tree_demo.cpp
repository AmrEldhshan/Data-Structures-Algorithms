#include "data_structures/trees/splay_tree.h"

#include <iostream>

using namespace std;

int main() {
    SplayTree<int> tree;
    for (int value : {50, 30, 70, 20, 40, 60, 80, 35, 45}) {
        tree.insert(value);
    }

    cout << "in-order: ";
    for (int value : tree.inOrder()) cout << value << ' ';
    cout << '\n';

    cout << "contains 40: " << boolalpha << tree.contains(40) << '\n';
    cout << "kth(4): " << tree.kth(4) << '\n';
    cout << "rank(50): " << tree.rank(50) << '\n';
    cout << "minimum: " << tree.minimum() << ", maximum: " << tree.maximum()
         << '\n';

    tree.erase(70);
    cout << "after erasing 70: ";
    for (int value : tree.inOrder()) cout << value << ' ';
    cout << '\n';

    return 0;
}
