#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// ---------------------------------------------------------------------------
// Unbounded knapsack
//
// Like 0/1 knapsack, but every item may be used any number of times. The only
// change is the direction of the capacity loop:
//
//   0/1 knapsack : for w = W down to weight   (each item once)
//   unbounded    : for w = weight up to W     (reuse allowed)
//
// Time:  O(nW)
// Space: O(W)
// ---------------------------------------------------------------------------
struct Item {
    string name;
    int weight;
    int value;
};

int unboundedKnapsack(const vector<Item>& items, int capacity) {
    vector<int> dp(capacity + 1, 0);

    for (int w = 1; w <= capacity; ++w) {
        for (const Item& item : items) {
            if (item.weight <= w) {
                dp[w] = max(dp[w], dp[w - item.weight] + item.value);
            }
        }
    }

    return dp[capacity];
}

int main() {
    vector<Item> items = {
        {"A", 2, 3},
        {"B", 3, 4},
        {"C", 4, 5},
        {"D", 5, 6}
    };
    int capacity = 8;

    cout << "capacity = " << capacity << '\n';
    cout << "maximum value = " << unboundedKnapsack(items, capacity) << '\n';

    // The table shows the best value for every smaller capacity too.
    vector<int> dp(capacity + 1, 0);
    for (int w = 1; w <= capacity; ++w) {
        for (const Item& item : items) {
            if (item.weight <= w) {
                dp[w] = max(dp[w], dp[w - item.weight] + item.value);
            }
        }
    }

    cout << "dp: ";
    for (int value : dp) cout << value << ' ';
    cout << '\n';

    return 0;
}
