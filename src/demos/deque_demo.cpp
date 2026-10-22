#include "data_structures/queues/deque.h"

#include <iostream>

using namespace std;

int main() {
    Deque<int> deque;

    deque.pushBack(2);
    deque.pushBack(3);
    deque.pushFront(1);
    deque.pushFront(0);

    cout << "after pushes, size = " << deque.size() << '\n';
    cout << "front = " << deque.front() << ", back = " << deque.back() << '\n';
    cout << "contents: ";
    for (size_t i = 0; i < deque.size(); ++i) cout << deque[i] << ' ';
    cout << "\n\n";

    deque.popFront();
    deque.popBack();

    cout << "after popFront and popBack: ";
    for (size_t i = 0; i < deque.size(); ++i) cout << deque[i] << ' ';
    cout << "\nfront = " << deque.front() << ", back = " << deque.back() << '\n';

    // Grow past the initial capacity to show the circular buffer resize.
    for (int value = 10; value < 20; ++value) deque.pushBack(value);
    cout << "\nAfter 10 more pushes, size = " << deque.size() << '\n';
    cout << "front = " << deque.front() << ", back = " << deque.back() << '\n';

    return 0;
}
