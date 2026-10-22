#include "data_structures/hashing/hash_map.h"

#include <iostream>
#include <string>

using namespace std;

int main() {
    HashMap<string, int> counts;

    for (const char* word : {"apple", "banana", "apple", "cherry", "apple",
                               "banana"}) {
        counts[word] += 1;
    }

    cout << "Word counts:\n";
    for (const char* word : {"apple", "banana", "cherry", "grape"}) {
        const int* count = counts.find(word);
        cout << "  " << word << " : " << (count ? *count : 0) << '\n';
    }

    cout << "\nsize = " << counts.size()
         << ", buckets = " << counts.bucketCount()
         << ", load factor = " << counts.loadFactor() << '\n';

    counts.erase("banana");
    cout << "after erase(banana), contains = "
         << (counts.contains("banana") ? "yes" : "no") << '\n';

    // Force a rehash by inserting many keys.
    for (int i = 0; i < 100; ++i) counts["key" + to_string(i)] = i;
    cout << "after 100 inserts: size = " << counts.size()
         << ", buckets = " << counts.bucketCount()
         << ", load factor = " << counts.loadFactor() << '\n';

    return 0;
}
