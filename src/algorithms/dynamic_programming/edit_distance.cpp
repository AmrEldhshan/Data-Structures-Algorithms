#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// ---------------------------------------------------------------------------
// Edit distance (Levenshtein distance)
//
// dp[i][j] = minimum number of single-character edits needed to turn
// a[0..i) into b[0..j).
//
//   insert : dp[i][j-1] + 1
//   delete : dp[i-1][j] + 1
//   replace: dp[i-1][j-1] + (a[i-1] != b[j-1])
//
// Time:  O(m * n)
// Space: O(m * n)
// ---------------------------------------------------------------------------
int editDistance(const string& a, const string& b) {
    int m = static_cast<int>(a.size());
    int n = static_cast<int>(b.size());

    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

    for (int i = 0; i <= m; ++i) dp[i][0] = i;
    for (int j = 0; j <= n; ++j) dp[0][j] = j;

    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            int replace = dp[i - 1][j - 1] + (a[i - 1] == b[j - 1] ? 0 : 1);
            int insert = dp[i][j - 1] + 1;
            int remove = dp[i - 1][j] + 1;
            dp[i][j] = min({replace, insert, remove});
        }
    }

    return dp[m][n];
}

void printOperations(const string& a, const string& b) {
    int m = static_cast<int>(a.size());
    int n = static_cast<int>(b.size());

    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
    for (int i = 0; i <= m; ++i) dp[i][0] = i;
    for (int j = 0; j <= n; ++j) dp[0][j] = j;

    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            int replace = dp[i - 1][j - 1] + (a[i - 1] == b[j - 1] ? 0 : 1);
            dp[i][j] = min({replace, dp[i][j - 1] + 1, dp[i - 1][j] + 1});
        }
    }

    vector<string> operations;
    int i = m;
    int j = n;

    while (i > 0 || j > 0) {
        if (i > 0 && j > 0 && a[i - 1] == b[j - 1]) {
            operations.push_back(string("keep '") + a[i - 1] + "'");
            --i;
            --j;
        } else if (i > 0 && j > 0 && dp[i][j] == dp[i - 1][j - 1] + 1) {
            operations.push_back(string("replace '") + a[i - 1] + "' with '" +
                                 b[j - 1] + "'");
            --i;
            --j;
        } else if (j > 0 && dp[i][j] == dp[i][j - 1] + 1) {
            operations.push_back(string("insert '") + b[j - 1] + "'");
            --j;
        } else {
            operations.push_back(string("delete '") + a[i - 1] + "'");
            --i;
        }
    }

    reverse(operations.begin(), operations.end());
    for (const string& operation : operations) {
        cout << "  " << operation << '\n';
    }
}

int main() {
    string a = "kitten";
    string b = "sitting";

    cout << "a = " << a << '\n';
    cout << "b = " << b << '\n';
    cout << "edit distance = " << editDistance(a, b) << "\n\n";

    cout << "one optimal sequence of edits:\n";
    printOperations(a, b);

    return 0;
}
