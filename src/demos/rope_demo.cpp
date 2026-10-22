#include "data_structures/strings/rope.h"

#include <iostream>
#include <string>

using namespace std;

int main() {
    Rope rope("Hello world");
    cout << "start: " << rope.toString() << " (" << rope.size() << ")\n";

    rope.insert(5, ",");
    rope.append("! Welcome to ropes.");
    rope.erase(0, 6);

    cout << "edited: " << rope.toString() << " (" << rope.size() << ")\n";
    cout << "substring(0, 11): " << rope.substring(0, 11) << '\n';
    cout << "at(0) = " << rope.at(0) << '\n';

    return 0;
}
