#include "data_structures/probabilistic/hyperloglog.h"

#include <iostream>
#include <string>

using namespace std;

int main() {
    HyperLogLog<string> sketch(12);

    for (int i = 0; i < 10'000; ++i) {
        sketch.add("user-" + to_string(i));
    }

    cout << "distinct users: 10000\n";
    cout << "HyperLogLog estimate: " << sketch.estimate() << '\n';

    sketch.clear();
    for (int i = 0; i < 100; ++i) sketch.add("small-" + to_string(i));
    cout << "distinct users: 100\n";
    cout << "HyperLogLog estimate: " << sketch.estimate() << '\n';

    return 0;
}
