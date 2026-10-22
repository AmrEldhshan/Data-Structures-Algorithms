#include <iostream>
#include <string>
#include <vector>

using namespace std;

// ---------------------------------------------------------------------------
// Knuth-Morris-Pratt (KMP)
//
// The prefix function lps[i] is the length of the longest proper prefix of
// pattern[0..i] that is also a suffix. When a mismatch happens, lps tells us
// how much of the pattern can be reused instead of starting over.
//
// Time:  O(n + m)
// Space: O(m)
// ---------------------------------------------------------------------------
vector<int> buildPrefixFunction(const string& pattern) {
    vector<int> lps(pattern.size(), 0);

    int length = 0; // length of the previous longest prefix-suffix
    for (int i = 1; i < static_cast<int>(pattern.size());) {
        if (pattern[i] == pattern[length]) {
            ++length;
            lps[i] = length;
            ++i;
        } else if (length != 0) {
            length = lps[length - 1];
        } else {
            lps[i] = 0;
            ++i;
        }
    }

    return lps;
}

vector<int> kmpSearch(const string& text, const string& pattern) {
    vector<int> matches;
    if (pattern.empty()) return matches;

    vector<int> lps = buildPrefixFunction(pattern);

    int matched = 0;
    for (int i = 0; i < static_cast<int>(text.size());) {
        if (text[i] == pattern[matched]) {
            ++i;
            ++matched;

            if (matched == static_cast<int>(pattern.size())) {
                matches.push_back(i - matched);
                matched = lps[matched - 1];
            }
        } else if (matched != 0) {
            matched = lps[matched - 1];
        } else {
            ++i;
        }
    }

    return matches;
}

int main() {
    string text = "ababcababa";
    string pattern = "aba";

    vector<int> lps = buildPrefixFunction(pattern);
    cout << "pattern: " << pattern << "\nprefix function: ";
    for (int value : lps) cout << value << ' ';
    cout << "\n\n";

    vector<int> matches = kmpSearch(text, pattern);
    cout << "text: " << text << '\n';
    cout << "matches at indices: ";
    for (int index : matches) cout << index << ' ';
    cout << '\n';

    return 0;
}
