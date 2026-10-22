#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// ---------------------------------------------------------------------------
// Sliding window and two pointers
//
// A sliding window maintains an interval [left, right] and updates the answer
// incrementally instead of recomputing from scratch. The window expands to the
// right and shrinks from the left only when the invariant breaks.
//
// Time: O(n) for each example below.
// ---------------------------------------------------------------------------
int maxSumSubarray(const vector<int>& values, int k) {
    if (k <= 0 || k > static_cast<int>(values.size())) {
        throw invalid_argument("maxSumSubarray: invalid window size");
    }

    int windowSum = 0;
    for (int i = 0; i < k; ++i) windowSum += values[i];

    int best = windowSum;
    for (int right = k; right < static_cast<int>(values.size()); ++right) {
        windowSum += values[right] - values[right - k];
        best = max(best, windowSum);
    }

    return best;
}

int longestUniqueSubstring(const string& text) {
    vector<int> lastSeen(256, -1);

    int left = 0;
    int best = 0;

    for (int right = 0; right < static_cast<int>(text.size()); ++right) {
        unsigned char letter = static_cast<unsigned char>(text[right]);

        if (lastSeen[letter] >= left) {
            left = lastSeen[letter] + 1;
        }

        lastSeen[letter] = right;
        best = max(best, right - left + 1);
    }

    return best;
}

string minimumWindowSubstring(const string& text, const string& pattern) {
    if (pattern.empty()) return "";
    if (pattern.size() > text.size()) return "";

    vector<int> needed(256, 0);
    for (unsigned char letter : pattern) ++needed[letter];

    int required = 0;
    for (int count : needed) {
        if (count > 0) ++required;
    }

    vector<int> window(256, 0);
    int formed = 0;
    int left = 0;
    int bestLength = static_cast<int>(text.size()) + 1;
    int bestStart = 0;

    for (int right = 0; right < static_cast<int>(text.size()); ++right) {
        unsigned char letter = static_cast<unsigned char>(text[right]);
        ++window[letter];

        if (needed[letter] > 0 && window[letter] == needed[letter]) {
            ++formed;
        }

        while (formed == required) {
            int length = right - left + 1;
            if (length < bestLength) {
                bestLength = length;
                bestStart = left;
            }

            unsigned char outgoing = static_cast<unsigned char>(text[left]);
            --window[outgoing];

            if (needed[outgoing] > 0 && window[outgoing] < needed[outgoing]) {
                --formed;
            }
            ++left;
        }
    }

    if (bestLength > static_cast<int>(text.size())) return "";
    return text.substr(bestStart, bestLength);
}

// Two pointers on a sorted array: find a pair that sums to `target`.
pair<int, int> twoSumSorted(const vector<int>& values, int target) {
    int left = 0;
    int right = static_cast<int>(values.size()) - 1;

    while (left < right) {
        int sum = values[left] + values[right];
        if (sum == target) return {left, right};
        if (sum < target) ++left;
        else --right;
    }

    return {-1, -1};
}

int main() {
    vector<int> values = {2, 1, 5, 1, 3, 2};
    cout << "max sum of 3 consecutive values: "
         << maxSumSubarray(values, 3) << '\n';

    string text = "abcabcbb";
    cout << "longest unique substring of \"" << text << "\": "
         << longestUniqueSubstring(text) << " characters\n";

    string source = "ADOBECODEBANC";
    string pattern = "ABC";
    cout << "minimum window in \"" << source << "\" containing \"" << pattern
         << "\": \"" << minimumWindowSubstring(source, pattern) << "\"\n";

    vector<int> sorted = {1, 2, 3, 4, 6};
    auto [left, right] = twoSumSorted(sorted, 8);
    if (left != -1) {
        cout << "two sum 8: indices " << left << " and " << right
             << " (values " << sorted[left] << " + " << sorted[right] << ")\n";
    } else {
        cout << "two sum 8: no pair\n";
    }

    return 0;
}
