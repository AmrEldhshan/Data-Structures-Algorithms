#include "data_structures/dynamic_array/dynamic_array.h"

#include <iostream>

using namespace std;

int main() {
    DynamicArray<int> values;

    cout << "push 10, 20, 30:\n";
    values.push_back(10);
    values.push_back(20);
    values.push_back(30);

    for (int value : values) cout << value << ' ';
    cout << " (size " << values.size() << ", capacity " << values.capacity()
         << ")\n";

    cout << "insert 15 at index 1: ";
    values.insert(1, 15);
    for (int value : values) cout << value << ' ';
    cout << '\n';

    cout << "erase index 2: ";
    values.erase(2);
    for (int value : values) cout << value << ' ';
    cout << '\n';

    cout << "reserve 16: capacity becomes ";
    values.reserve(16);
    cout << values.capacity() << '\n';

    cout << "resize to 7: ";
    values.resize(7);
    for (int value : values) cout << value << ' ';
    cout << '\n';

    cout << "front = " << values.front() << ", back = " << values.back()
         << '\n';

    DynamicArray<int> copy = values;
    copy.pop_back();
    cout << "copy after pop_back: ";
    for (int value : copy) cout << value << ' ';
    cout << '\n';

    return 0;
}
