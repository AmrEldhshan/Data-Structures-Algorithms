#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

// ---------------------------------------------------------------------------
// Longest increasing subsequence (LIS) in O(n log n)
//
// `tails[len - 1]` is the smallest possible tail of an increasing subsequence
// of length `len`. For each value x we binary-search the first tail >= x and
// replace it. Replacing keeps future extensions as easy as possible.
//
// The parent array remembers where each chosen value came from, so the actual
// subsequence can be reconstructed.
//
// Time:  O(n log n)
// Space: O(n)
// ---------------------------------------------------------------------------
vector<int> longestIncreasingSubsequence(const vector<int>& values) {
    if (values.empty()) return {};

    vector<int> tails;          // tails[len - 1] = smallest tail of length len
    vector<int> tailIndex;      // index in `values` of each tail
    vector<int> parent(values.size(), -1);

    for (int i = 0; i < static_cast<int>(values.size()); ++i) {
        auto position = lower_bound(tails.begin(), tails.end(), values[i]);

        int length = static_cast<int>(position - tails.begin());
        if (length > 0) parent[i] = tailIndex[length - 1];

        if (position == tails.end()) {
            tails.push_back(values[i]);
            tailIndex.push_back(i);
        } else {
            *position = values[i];
            tailIndex[length] = i;
        }
    }

    // Walk backwards from the last element of the longest subsequence.
    vector<int> sequence;
    for (int index = tailIndex.back(); index != -1; index = parent[index]) {
        sequence.push_back(values[index]);
    }
    reverse(sequence.begin(), sequence.end());
    return sequence;
}

int main() {
    vector<int> values = {10, 9, 2, 5, 3, 7, 101, 18};

    cout << "values: ";
    for (int value : values) cout << value << ' ';
    cout << '\n';

    vector<int> sequence = longestIncreasingSubsequence(values);
    cout << "LIS length: " << sequence.size() << '\n';
    cout << "one LIS:    ";
    for (int value : sequence) cout << value << ' ';
    cout << "\n\n";

    // The O(n^2) DP is easier to reason about. It is shown here for contrast.
    vector<int> dp(values.size(), 1);
    int best = 1;
    for (int i = 0; i < static_cast<int>(values.size()); ++i) {
        for (int j = 0; j < i; ++j) {
            if (values[j] < values[i]) dp[i] = max(dp[i], dp[j] + 1);
        }
        best = max(best, dp[i]);
    }
    cout << "O(n^2) DP also finds length " << best << '\n';

    return 0;
}
