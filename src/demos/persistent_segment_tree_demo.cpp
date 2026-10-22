#include "data_structures/trees/persistent_segment_tree.h"

#include <iostream>
#include <vector>

using namespace std;

int main() {
    vector<long long> values = {1, 2, 3, 4, 5};
    PersistentSegmentTree tree(values);

    int version1 = tree.update(0, 2, 30);
    int version2 = tree.update(version1, 4, 50);

    cout << "version 0: ";
    for (int i = 0; i < 5; ++i) cout << tree.sum(0, i, i + 1) << ' ';
    cout << "(sum " << tree.sum(0, 0, 5) << ")\n";

    cout << "version 1: ";
    for (int i = 0; i < 5; ++i) cout << tree.sum(version1, i, i + 1) << ' ';
    cout << "(sum " << tree.sum(version1, 0, 5) << ")\n";

    cout << "version 2: ";
    for (int i = 0; i < 5; ++i) cout << tree.sum(version2, i, i + 1) << ' ';
    cout << "(sum " << tree.sum(version2, 0, 5) << ")\n";

    cout << "versions stored: " << tree.versionCount() << '\n';

    return 0;
}
