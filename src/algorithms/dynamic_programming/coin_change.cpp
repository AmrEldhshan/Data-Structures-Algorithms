#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>

using namespace std;

// ---------------------------------------------------------------------------
// Coin change
//
// Two different questions, two different transitions:
//
//   minimum number of coins
//     dp[amount] = min(dp[amount - coin] + 1) over all coins
//
//   number of combinations
//     loop coins on the outside, amounts on the inside, so a set of coins is
//     counted once regardless of order. Swapping the loops counts ordered
//     sequences (permutations) instead.
//
// Time:  O(amount * number_of_coins)
// Space: O(amount)
// ---------------------------------------------------------------------------
const int INF = numeric_limits<int>::max() / 4;

int minimumCoins(const vector<int>& coins, int amount,
                 vector<int>& chosen) {
    vector<int> dp(amount + 1, INF);
    vector<int> lastCoin(amount + 1, -1);
    dp[0] = 0;

    for (int value = 1; value <= amount; ++value) {
        for (int coin : coins) {
            if (coin <= value && dp[value - coin] != INF &&
                dp[value - coin] + 1 < dp[value]) {
                dp[value] = dp[value - coin] + 1;
                lastCoin[value] = coin;
            }
        }
    }

    chosen.clear();
    if (dp[amount] == INF) return -1;

    for (int value = amount; value > 0; value -= lastCoin[value]) {
        chosen.push_back(lastCoin[value]);
    }
    reverse(chosen.begin(), chosen.end());
    return dp[amount];
}

long long countCombinations(const vector<int>& coins, int amount) {
    vector<long long> dp(amount + 1, 0);
    dp[0] = 1;

    // Coins outside: each unordered combination is counted exactly once.
    for (int coin : coins) {
        for (int value = coin; value <= amount; ++value) {
            dp[value] += dp[value - coin];
        }
    }

    return dp[amount];
}

long long countPermutations(const vector<int>& coins, int amount) {
    vector<long long> dp(amount + 1, 0);
    dp[0] = 1;

    // Amount outside and coins inside: order matters.
    for (int value = 1; value <= amount; ++value) {
        for (int coin : coins) {
            if (coin <= value) dp[value] += dp[value - coin];
        }
    }

    return dp[amount];
}

int main() {
    vector<int> coins = {1, 2, 5};
    int amount = 11;

    vector<int> chosen;
    int minimum = minimumCoins(coins, amount, chosen);

    cout << "coins: 1, 2, 5    amount: " << amount << "\n\n";
    cout << "minimum coins: " << minimum << "  (";
    for (int coin : chosen) cout << coin << ' ';
    cout << ")\n";
    cout << "combinations:  " << countCombinations(coins, amount) << '\n';
    cout << "permutations:  " << countPermutations(coins, amount) << '\n';

    return 0;
}
