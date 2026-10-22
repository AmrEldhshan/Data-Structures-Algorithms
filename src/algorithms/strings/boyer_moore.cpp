#include <algorithm>
#include <array>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// ---------------------------------------------------------------------------
// Boyer-Moore (bad-character heuristic)
//
// Compare the pattern from right to left. On a mismatch, the bad-character
// table says how far the pattern can shift so that the mismatching text
// character lines up with its last occurrence in the pattern.
//
// This demo implements only the bad-character rule. The full algorithm adds
// the good-suffix rule, which gives a stronger worst-case guarantee.
//
// Time:  O(n / m) best case, O(n * m) worst case
// Space: O(alphabet)
// ---------------------------------------------------------------------------
vector<int> badCharacterTable(const string& pattern) {
    vector<int> last(256, -1);

    for (int i = 0; i < static_cast<int>(pattern.size()); ++i) {
        last[static_cast<unsigned char>(pattern[i])] = i;
    }

    return last;
}

vector<int> boyerMooreSearch(const string& text, const string& pattern) {
    vector<int> matches;
    if (pattern.empty() || pattern.size() > text.size()) return matches;

    vector<int> last = badCharacterTable(pattern);

    int m = static_cast<int>(pattern.size());
    int n = static_cast<int>(text.size());
    int shift = 0;

    while (shift <= n - m) {
        int j = m - 1;

        while (j >= 0 && pattern[j] == text[shift + j]) --j;

        if (j < 0) {
            matches.push_back(shift);

            if (shift + m < n) {
                shift += m - last[static_cast<unsigned char>(text[shift + m])];
            } else {
                shift += 1;
            }
        } else {
            int badCharacter = static_cast<unsigned char>(text[shift + j]);
            shift += max(1, j - last[badCharacter]);
        }
    }

    return matches;
}

int main() {
    string text = "HERE IS A SIMPLE EXAMPLE";
    string pattern = "EXAMPLE";

    cout << "text:    " << text << '\n';
    cout << "pattern: " << pattern << "\n\n";

    cout << "matches at indices: ";
    for (int index : boyerMooreSearch(text, pattern)) cout << index << ' ';
    cout << '\n';

    return 0;
}
