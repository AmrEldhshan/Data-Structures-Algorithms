#include "data_structures/trees/disjoint_sparse_table.h"

#include <iostream>
#include <vector>

using namespace std;

int main() {
    vector<int> values = {4, 1, 7, 2, 9, 3, 8, 5};
    DisjointSparseTable<int> table(values);

    cout << "values: ";
    for (int value : values) cout << value << ' ';
    cout << "\n\nrange minimums:\n";
    for (auto [left, right] : {pair<int, int>{0, 7}, {2, 5}, {3, 3}, {4, 6}}) {
        cout << "  min[" << left << ", " << right << "] = "
             << table.query(left, right) << '\n';
    }

    return 0;
}
