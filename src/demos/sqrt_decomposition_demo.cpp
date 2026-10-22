#include "data_structures/sqrt_decomposition/sqrt_decomposition.h"

#include <iostream>
#include <vector>

using namespace std;

int main() {
    vector<long long> values = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    SqrtDecomposition<long long> blocks(values);

    cout << "initial sum[0, 10) = " << blocks.sum(0, 10) << '\n';
    cout << "sum[3, 7) = " << blocks.sum(3, 7) << '\n';

    blocks.add(2, 8, 5);
    cout << "after adding 5 to [2, 8):\n";
    cout << "  sum[0, 10) = " << blocks.sum(0, 10) << '\n';
    cout << "  sum[3, 7) = " << blocks.sum(3, 7) << '\n';

    blocks.add(0, 5, -2);
    cout << "after adding -2 to [0, 5): sum[0, 10) = "
         << blocks.sum(0, 10) << '\n';

    return 0;
}
