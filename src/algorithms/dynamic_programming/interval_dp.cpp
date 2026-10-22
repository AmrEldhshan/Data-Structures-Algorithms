#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

// ---------------------------------------------------------------------------
// Interval DP: burst balloons
//
// Add a virtual balloon with value 1 at each end. If balloon k is the LAST one
// burst inside (left, right), it earns
//
//   nums[left] * nums[k] * nums[right]
//
// plus the best results for the two sides. Trying every k gives an interval DP.
//
// Time:  O(n³)
// Space: O(n²)
// ---------------------------------------------------------------------------
int maxCoins(vector<int> balloons) {
    balloons.insert(balloons.begin(), 1);
    balloons.push_back(1);

    int n = static_cast<int>(balloons.size());
    vector<vector<int>> dp(n, vector<int>(n, 0));

    for (int length = 2; length < n; ++length) {
        for (int left = 0; left + length < n; ++left) {
            int right = left + length;

            for (int last = left + 1; last < right; ++last) {
                int coins = balloons[left] * balloons[last] * balloons[right];
                int candidate = coins + dp[left][last] + dp[last][right];
                dp[left][right] = max(dp[left][right], candidate);
            }
        }
    }

    return dp[0][n - 1];
}

int main() {
    for (const vector<int>& balloons : {
             vector<int>{3, 1, 5, 8},
             vector<int>{1, 5},
             vector<int>{2, 4, 3, 5}}) {
        cout << "balloons: ";
        for (int value : balloons) cout << value << ' ';
        cout << "-> max coins = " << maxCoins(balloons) << '\n';
    }

    return 0;
}
