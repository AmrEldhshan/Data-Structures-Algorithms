#include "data_structures/trees/fenwick_tree.h"

#include <iostream>
#include <vector>

using namespace std;

int main() {
    vector<long long> values = {3, 2, -1, 6, 5, 4, -3, 3, 7, 2, 3};
    FenwickTree tree(values);

    cout << "values: ";
    for (long long value : values) cout << value << ' ';
    cout << "\n\n";

    cout << "prefixSum(5)      = " << tree.prefixSum(5) << '\n';
    cout << "rangeSum(2, 7)    = " << tree.rangeSum(2, 7) << '\n';
    cout << "rangeSum(0, 10)   = " << tree.rangeSum(0, 10) << '\n';

    // Add 10 to values[4]. Every prefix ending at or after index 4 grows by 10.
    tree.add(4, 10);
    cout << "\nAfter add(4, 10):\n";
    cout << "prefixSum(5)      = " << tree.prefixSum(5) << '\n';
    cout << "rangeSum(2, 7)    = " << tree.rangeSum(2, 7) << '\n';

    return 0;
}
