#include "data_structures/heaps/min_max_heap.h"

#include <iostream>

using namespace std;

int main() {
    MinMaxHeap<int> heap;
    for (int value : {5, 1, 9, 3, 7, 2, 8, 4, 6}) heap.insert(value);

    cout << "min = " << heap.minimum() << ", max = " << heap.maximum()
         << ", size = " << heap.size() << '\n';

    cout << "extractMin order: ";
    while (!heap.empty()) cout << heap.extractMin() << ' ';
    cout << '\n';

    for (int value : {5, 1, 9, 3, 7, 2, 8, 4, 6}) heap.insert(value);
    cout << "extractMax order: ";
    while (!heap.empty()) cout << heap.extractMax() << ' ';
    cout << '\n';

    return 0;
}
