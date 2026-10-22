#include "data_structures/probabilistic/cuckoo_filter.h"

#include <iostream>
#include <string>

using namespace std;

int main() {
    CuckooFilter<string> filter(128, 4);

    for (const char* word : {"apple", "banana", "cherry", "date", "elder"}) {
        filter.insert(word);
    }

    cout << "inserted 5 words, size = " << filter.size() << '\n';
    cout << "contains apple: " << boolalpha << filter.contains("apple") << '\n';
    cout << "contains fig: " << filter.contains("fig") << '\n';

    cout << "erase banana: " << filter.erase("banana") << '\n';
    cout << "contains banana after erase: " << filter.contains("banana") << '\n';

    return 0;
}
