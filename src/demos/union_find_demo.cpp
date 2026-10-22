#include "data_structures/disjoint_set/union_find.h"

#include <iostream>

using namespace std;

int main() {
    UnionFind sets(7);

    cout << "initial components: " << sets.components() << '\n';

    sets.unite(0, 1);
    sets.unite(2, 3);
    sets.unite(1, 3);
    sets.unite(4, 5);

    cout << "after unions, components: " << sets.components() << '\n';
    cout << "connected(0, 2): " << (sets.connected(0, 2) ? "yes" : "no") << '\n';
    cout << "connected(0, 4): " << (sets.connected(0, 4) ? "yes" : "no") << '\n';
    cout << "component size of 0: " << sets.componentSize(0) << '\n';
    cout << "component size of 6: " << sets.componentSize(6) << '\n';

    // Union by rank + path compression keeps these trees very flat.
    cout << "\nunite(0, 6): " << (sets.unite(0, 6) ? "merged" : "already same") << '\n';
    cout << "components now: " << sets.components() << '\n';

    return 0;
}
