#include "data_structures/trees/lazy_segment_tree.h"

#include <iostream>
#include <vector>

using namespace std;

int main() {
    vector<long long> values = {1, 2, 3, 4, 5, 6, 7, 8};
    LazySegmentTree tree(values);

    cout << "initial sum[0, 8) = " << tree.sum(0, 8) << '\n';
    cout << "sum[2, 5) = " << tree.sum(2, 5) << '\n';

    tree.add(1, 6, 10);
    cout << "after adding 10 to [1, 6):\n";
    cout << "  sum[0, 8) = " << tree.sum(0, 8) << '\n';
    cout << "  sum[2, 5) = " << tree.sum(2, 5) << '\n';
    cout << "  sum[6, 8) = " << tree.sum(6, 8) << '\n';

    tree.add(0, 8, -3);
    cout << "after adding -3 to everything: sum[0, 8) = "
         << tree.sum(0, 8) << '\n';

    return 0;
}
