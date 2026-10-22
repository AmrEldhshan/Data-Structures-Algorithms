#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

// ---------------------------------------------------------------------------
// Rod cutting
//
// A rod of length n can be cut into pieces. price[length - 1] is the selling
// price of a piece of that length. Maximise total revenue.
//
//   dp[length] = max(price[cut] + dp[length - cut]) for 1 <= cut <= length
//
// Time:  O(n²)
// Space: O(n)
// ---------------------------------------------------------------------------
int main() {
    vector<int> price = {1, 5, 8, 9, 10, 17, 17, 20};
    int length = static_cast<int>(price.size());

    vector<int> dp(length + 1, 0);
    vector<int> firstCut(length + 1, 0);

    for (int current = 1; current <= length; ++current) {
        for (int cut = 1; cut <= current; ++cut) {
            int revenue = price[cut - 1] + dp[current - cut];
            if (revenue > dp[current]) {
                dp[current] = revenue;
                firstCut[current] = cut;
            }
        }
    }

    cout << "prices: ";
    for (int value : price) cout << value << ' ';
    cout << "\n\n";
    cout << "best revenue for length " << length << ": " << dp[length]
         << "\n";

    cout << "cuts: ";
    for (int remaining = length; remaining > 0; remaining -= firstCut[remaining]) {
        cout << firstCut[remaining] << ' ';
    }
    cout << '\n';

    return 0;
}
