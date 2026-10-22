#include "data_structures/heaps/min_heap.h"

#include <iostream>
#include <vector>

using namespace std;

int main() {
    MinHeap<int> heap;
    for (int value : {7, 2, 9, 1, 5, 3}) heap.push(value);

    cout << "top = " << heap.top() << ", size = " << heap.size() << '\n';

    cout << "extract order: ";
    while (!heap.empty()) {
        cout << heap.top() << ' ';
        heap.pop();
    }
    cout << '\n';

    // Building from an existing vector takes O(n), not O(n log n).
    MinHeap<int> built(vector<int>{10, 4, 8, 1, 6});
    cout << "\nbuilt heap top = " << built.top() << '\n';
    built.push(0);
    cout << "after push(0), top = " << built.top() << '\n';
    built.pop();
    cout << "after pop, top = " << built.top() << '\n';

    return 0;
}
