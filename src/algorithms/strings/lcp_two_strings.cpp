#include <algorithm>
#include <iostream>
#include <string>

using namespace std;

// ---------------------------------------------------------------------------
// Longest common prefix of two strings
//
// Binary search the answer length. The predicate "the first length characters
// match" is monotone: once it fails, every longer prefix also fails.
//
// Each comparison costs O(length), so the total is O(n log n) in the worst case;
// a rolling hash or suffix array would make each comparison O(1) expected.
// ---------------------------------------------------------------------------
string longestCommonPrefix(const string& a, const string& b) {
    int low = 0;
    int high = static_cast<int>(min(a.size(), b.size()));

    while (low < high) {
        int middle = low + (high - low + 1) / 2;

        if (a.compare(0, middle, b, 0, middle) == 0) {
            low = middle;
        } else {
            high = middle - 1;
        }
    }

    return a.substr(0, low);
}

int main() {
    for (const auto& [a, b] : {
             pair<string, string>{"interview", "internet"},
             pair<string, string>{"flower", "flow"},
             pair<string, string>{"abc", "xyz"},
             pair<string, string>{"banana", "banana"}}) {
        cout << "\"" << a << "\" and \"" << b << "\": \""
             << longestCommonPrefix(a, b) << "\"\n";
    }

    return 0;
}
