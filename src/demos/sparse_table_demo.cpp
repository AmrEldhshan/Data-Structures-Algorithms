#include "data_structures/trees/sparse_table.h"

#include <iostream>
#include <vector>

using namespace std;

int main() {
    vector<int> values = {7, 2, 3, 0, 5, 10, 3, 12, 18};
    SparseTable table(values);

    cout << "values: ";
    for (int value : values) cout << value << ' ';
    cout << "\n\n";

    struct Query {
        int left;
        int right;
    };

    for (Query query : {Query{0, 3}, Query{4, 7}, Query{2, 8}, Query{0, 8}}) {
        cout << "min[" << query.left << ".." << query.right << "] = "
             << table.rangeMin(query.left, query.right) << '\n';
    }

    // Sparse tables are static: the array is not updated after construction.
    cout << "\nA query is O(1) because the two blocks below overlap:\n";
    cout << "min[2..8]: blocks [2..5] and [5..8]\n";

    return 0;
}
