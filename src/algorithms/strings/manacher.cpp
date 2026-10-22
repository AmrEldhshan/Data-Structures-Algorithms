#include <iostream>
#include <string>
#include <vector>

using namespace std;

// ---------------------------------------------------------------------------
// Manacher's algorithm
//
// Find the longest palindromic substring in O(n). First insert separators so
// that even-length and odd-length palindromes are handled uniformly:
//
//   "abba"  ->  "^#a#b#b#a#$"
//
// p[i] is the radius (in transformed characters) of the palindrome centred at
// i. The mirror index inside the current rightmost palindrome lets us reuse
// work instead of expanding from scratch every time.
//
// Time:  O(n)
// Space: O(n)
// ---------------------------------------------------------------------------
string longestPalindromicSubstring(const string& text) {
    if (text.empty()) return "";

    string transformed = "^#";
    for (char letter : text) {
        transformed += letter;
        transformed += '#';
    }
    transformed += '$';

    int n = static_cast<int>(transformed.size());
    vector<int> radius(n, 0);

    int centre = 0;
    int right = 0;

    for (int i = 1; i < n - 1; ++i) {
        int mirror = 2 * centre - i;

        if (i < right) {
            radius[i] = min(right - i, radius[mirror]);
        }

        while (transformed[i + radius[i] + 1] ==
               transformed[i - radius[i] - 1]) {
            ++radius[i];
        }

        if (i + radius[i] > right) {
            centre = i;
            right = i + radius[i];
        }
    }

    int bestCentre = 0;
    int bestRadius = 0;
    for (int i = 1; i < n - 1; ++i) {
        if (radius[i] > bestRadius) {
            bestRadius = radius[i];
            bestCentre = i;
        }
    }

    int start = (bestCentre - bestRadius) / 2;
    return text.substr(start, bestRadius);
}

int main() {
    for (const char* text : {"babad", "cbbd", "forgeeksskeegfor", "abacdfgdcaba"}) {
        cout << "text: " << text
             << "  ->  longest palindrome: \""
             << longestPalindromicSubstring(text) << "\"\n";
    }

    return 0;
}
