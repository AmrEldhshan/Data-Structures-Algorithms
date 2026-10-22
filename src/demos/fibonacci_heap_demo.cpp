#include "data_structures/heaps/fibonacci_heap.h"

#include <iostream>

using namespace std;

int main() {
    FibonacciHeap<int> heap;
    for (int value : {7, 2, 9, 1, 5, 3, 8, 4, 6}) heap.insert(value);

    cout << "size = " << heap.size() << ", minimum = " << heap.minimum()
         << '\n';
    cout << "extractMin order: ";
    while (!heap.empty()) cout << heap.extractMin() << ' ';
    cout << '\n';

    return 0;
}
