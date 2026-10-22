#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// ---------------------------------------------------------------------------
// Longest common subsequence (LCS)
//
// dp[i][j] = length of the LCS of a[0..i) and b[0..j).
//
//   a[i-1] == b[j-1] : dp[i][j] = dp[i-1][j-1] + 1
//   otherwise        : dp[i][j] = max(dp[i-1][j], dp[i][j-1])
//
// A subsequence keeps order but may skip characters; a substring may not skip.
//
// Time:  O(m * n)
// Space: O(m * n)  (the table can be reduced to O(min(m, n)) if only the
//                   length is needed)
// ---------------------------------------------------------------------------
string longestCommonSubsequence(const string& a, const string& b) {
    int m = static_cast<int>(a.size());
    int n = static_cast<int>(b.size());

    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (a[i - 1] == b[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            } else {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }

    // Reconstruct by walking back through the table.
    string result;
    int i = m;
    int j = n;
    while (i > 0 && j > 0) {
        if (a[i - 1] == b[j - 1]) {
            result.push_back(a[i - 1]);
            --i;
            --j;
        } else if (dp[i - 1][j] >= dp[i][j - 1]) {
            --i;
        } else {
            --j;
        }
    }

    reverse(result.begin(), result.end());
    return result;
}

int main() {
    string a = "ABCBDAB";
    string b = "BDCABA";

    string lcs = longestCommonSubsequence(a, b);
    cout << "a = " << a << '\n';
    cout << "b = " << b << '\n';
    cout << "LCS length: " << lcs.size() << '\n';
    cout << "LCS:        " << lcs << '\n';

    // There can be several LCS strings of the same length. This depends on
    // which predecessor the reconstruction chooses when both are equal.
    cout << "\nOther LCS answers of the same length may also be valid.\n";

    return 0;
}
