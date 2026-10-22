#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

// ---------------------------------------------------------------------------
// Partition into two equal-sum subsets
//
// This is subset sum in disguise. If the total sum is odd, no split exists.
// Otherwise ask: is there a subset with sum total / 2?
//
// dp[s] = can some subset reach sum s?
//
// Time:  O(n * total)
// Space: O(total)
// ---------------------------------------------------------------------------
bool canPartition(const vector<int>& values) {
    int total = accumulate(values.begin(), values.end(), 0);
    if (total % 2 != 0) return false;

    int target = total / 2;
    vector<bool> dp(target + 1, false);
    dp[0] = true;

    for (int value : values) {
        for (int sum = target; sum >= value; --sum) {
            if (dp[sum - value]) dp[sum] = true;
        }
    }

    return dp[target];
}

int main() {
    for (const vector<int>& values : {
             vector<int>{1, 5, 11, 5},
             vector<int>{1, 2, 3, 5},
             vector<int>{1, 2, 3, 4, 5, 6, 7}}) {
        int total = accumulate(values.begin(), values.end(), 0);

        cout << "values: ";
        for (int value : values) cout << value << ' ';
        cout << " (sum " << total << ") -> "
             << (canPartition(values) ? "can partition" : "cannot partition")
             << '\n';
    }

    return 0;
}
