#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// ---------------------------------------------------------------------------
// Longest palindromic subsequence
//
// dp[i][j] = length of the longest palindromic subsequence inside s[i..j].
//
//   s[i] == s[j] : dp[i][j] = dp[i+1][j-1] + 2
//   otherwise    : dp[i][j] = max(dp[i+1][j], dp[i][j-1])
//
// Unlike a palindromic substring, the characters do not need to be contiguous.
//
// Time:  O(n²)
// Space: O(n²)
// ---------------------------------------------------------------------------
int longestPalindromicSubsequence(const string& text) {
    int n = static_cast<int>(text.size());
    if (n == 0) return 0;

    vector<vector<int>> dp(n, vector<int>(n, 0));
    for (int i = 0; i < n; ++i) dp[i][i] = 1;

    for (int length = 2; length <= n; ++length) {
        for (int i = 0; i + length - 1 < n; ++i) {
            int j = i + length - 1;

            if (text[i] == text[j]) {
                dp[i][j] = dp[i + 1][j - 1] + 2;
            } else {
                dp[i][j] = max(dp[i + 1][j], dp[i][j - 1]);
            }
        }
    }

    return dp[0][n - 1];
}

int main() {
    string text = "bbabcbcab";

    cout << "text: " << text << '\n';
    cout << "longest palindromic subsequence length: "
         << longestPalindromicSubsequence(text) << '\n';
    cout << "\nExample: \"babcbab\" (length 7) is a subsequence.\n";

    return 0;
}
