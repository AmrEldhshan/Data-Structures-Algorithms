#include "data_structures/ordered/ordered_map.h"
#include "data_structures/ordered/ordered_set.h"

#include <iostream>
#include <string>

using namespace std;

int main() {
    OrderedSet<int> set;
    for (int value : {5, 1, 9, 3, 7, 3, 8}) set.insert(value);

    cout << "ordered set: ";
    for (int value : set.toVector()) cout << value << ' ';
    cout << "\nsize = " << set.size() << ", min = " << set.minimum()
         << ", max = " << set.maximum() << '\n';
    cout << "kth(2) = " << set.kth(2) << ", rank(7) = " << set.rank(7) << '\n';

    if (auto value = set.lowerBound(6)) cout << "lowerBound(6) = " << *value << '\n';
    if (auto value = set.upperBound(7)) cout << "upperBound(7) = " << *value << '\n';

    OrderedMap<string, int> ages;
    ages["alice"] = 30;
    ages["bob"] = 25;
    ages["carol"] = 35;
    ages["dave"] = 28;

    cout << "\nordered map:\n";
    for (const auto& [name, age] : ages.entries()) {
        cout << "  " << name << " -> " << age << '\n';
    }

    cout << "bob is " << ages.at("bob") << '\n';
    cout << "keys: ";
    for (const string& key : ages.keys()) cout << key << ' ';
    cout << '\n';

    ages.erase("bob");
    cout << "after erasing bob, contains = " << boolalpha
         << ages.contains("bob") << '\n';

    return 0;
}
