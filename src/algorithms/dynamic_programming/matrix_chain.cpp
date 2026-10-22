#include <algorithm>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

using namespace std;

// ---------------------------------------------------------------------------
// Matrix chain multiplication
//
// Multiplying matrices is associative, so the order matters for the cost.
// For dimensions p[0] x p[1], p[1] x p[2], ..., p[n-1] x p[n]:
//
//   dp[i][j] = minimum cost to multiply matrices i..j
//   dp[i][j] = min over k of dp[i][k] + dp[k+1][j] + p[i] * p[k+1] * p[j+1]
//
// `split[i][j]` stores the k that produced the minimum, which lets us print
// the parenthesisation.
//
// Time:  O(n³)
// Space: O(n²)
// ---------------------------------------------------------------------------
string parenthesise(const vector<vector<int>>& split, int i, int j) {
    if (i == j) return "A" + to_string(i + 1);

    int k = split[i][j];
    return "(" + parenthesise(split, i, k) + " x " +
           parenthesise(split, k + 1, j) + ")";
}

int main() {
    // A1: 30x35, A2: 35x15, A3: 15x5, A4: 5x10, A5: 10x20, A6: 20x25
    vector<int> p = {30, 35, 15, 5, 10, 20, 25};
    int n = static_cast<int>(p.size()) - 1;

    const int INF = numeric_limits<int>::max() / 4;
    vector<vector<int>> dp(n, vector<int>(n, 0));
    vector<vector<int>> split(n, vector<int>(n, -1));

    for (int length = 2; length <= n; ++length) {
        for (int i = 0; i + length - 1 < n; ++i) {
            int j = i + length - 1;
            dp[i][j] = INF;

            for (int k = i; k < j; ++k) {
                int cost = dp[i][k] + dp[k + 1][j] +
                           p[i] * p[k + 1] * p[j + 1];

                if (cost < dp[i][j]) {
                    dp[i][j] = cost;
                    split[i][j] = k;
                }
            }
        }
    }

    cout << "dimensions: ";
    for (int value : p) cout << value << ' ';
    cout << "\n\n";
    cout << "minimum scalar multiplications: " << dp[0][n - 1] << '\n';
    cout << "optimal order: " << parenthesise(split, 0, n - 1) << '\n';

    return 0;
}
