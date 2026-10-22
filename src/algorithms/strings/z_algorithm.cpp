#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// ---------------------------------------------------------------------------
// Z-algorithm
//
// z[i] is the length of the longest substring starting at i that matches a
// prefix of the string. To search for a pattern, build
//
//   pattern + '#' + text
//
// and report every position where z[i] >= pattern.size().
//
// Time:  O(n + m)
// Space: O(n + m)
// ---------------------------------------------------------------------------
vector<int> buildZ(const string& text) {
    int n = static_cast<int>(text.size());
    vector<int> z(n, 0);

    int left = 0;
    int right = 0; // [left, right) is the current Z-box

    for (int i = 1; i < n; ++i) {
        if (i < right) {
            z[i] = min(right - i, z[i - left]);
        }

        while (i + z[i] < n && text[z[i]] == text[i + z[i]]) {
            ++z[i];
        }

        if (i + z[i] > right) {
            left = i;
            right = i + z[i];
        }
    }

    return z;
}

vector<int> zSearch(const string& text, const string& pattern) {
    vector<int> matches;
    if (pattern.empty()) return matches;

    string combined = pattern + '\1' + text;
    vector<int> z = buildZ(combined);

    for (int i = static_cast<int>(pattern.size()) + 1;
         i < static_cast<int>(combined.size()); ++i) {
        if (z[i] >= static_cast<int>(pattern.size())) {
            matches.push_back(i - static_cast<int>(pattern.size()) - 1);
        }
    }

    return matches;
}

int main() {
    string text = "aabcaabxaaaz";
    string pattern = "aab";

    vector<int> z = buildZ(pattern + '\1' + text);
    cout << "pattern: " << pattern << '\n';
    cout << "text:    " << text << "\n\n";
    cout << "Z-values for pattern#text:\n  ";
    for (int value : z) cout << value << ' ';
    cout << "\n\n";

    cout << "matches at indices: ";
    for (int index : zSearch(text, pattern)) cout << index << ' ';
    cout << '\n';

    return 0;
}
