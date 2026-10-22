#include "data_structures/trees/wavelet_tree.h"

#include <iostream>
#include <vector>

using namespace std;

int main() {
    vector<int> values = {5, 2, 8, 1, 9, 3, 7, 4, 6};
    WaveletTree tree(values);

    cout << "values: ";
    for (int value : values) cout << value << ' ';
    cout << "\n\n";

    cout << "count < 5 in [0, 9): " << tree.countLess(0, 9, 5) << '\n';
    cout << "count <= 4 in [2, 7): " << tree.countLessOrEqual(2, 7, 4) << '\n';

    for (int k = 1; k <= 9; ++k) {
        cout << "kthSmallest(0, 9, " << k << ") = "
             << tree.kthSmallest(0, 9, k) << '\n';
    }

    return 0;
}
