#include "data_structures/cache/lru_cache.h"

#include <iostream>
#include <string>

using namespace std;

int main() {
    LruCache<string, int> cache(2);

    cache.put("one", 1);
    cache.put("two", 2);

    cout << "get(one) = " << cache.get("one").value_or(-1) << '\n';

    // Capacity is 2. "one" was just used, so "two" is the least recent.
    cache.put("three", 3);

    cout << "contains(two)   = " << (cache.contains("two") ? "yes" : "no") << '\n';
    cout << "contains(one)   = " << (cache.contains("one") ? "yes" : "no") << '\n';
    cout << "contains(three) = " << (cache.contains("three") ? "yes" : "no") << '\n';

    cout << "get(three) = " << cache.get("three").value_or(-1) << '\n';
    cout << "size = " << cache.size() << ", capacity = " << cache.capacity()
         << '\n';

    return 0;
}
