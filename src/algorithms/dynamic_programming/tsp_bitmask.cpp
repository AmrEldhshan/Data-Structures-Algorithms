#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>

using namespace std;

// ---------------------------------------------------------------------------
// Travelling salesman with bitmask DP
//
// dp[mask][i] = minimum cost of starting at city 0, visiting exactly the
// cities in `mask`, and ending at city i. `mask` always contains city 0.
//
// Transition: append city j that is not yet in the mask.
//
// Time:  O(2^n * n^2)
// Space: O(2^n * n)
// ---------------------------------------------------------------------------
const int INF = numeric_limits<int>::max() / 4;

int main() {
    // Distances between four cities.
    vector<vector<int>> distance = {
        {0, 10, 15, 20},
        {10, 0, 35, 25},
        {15, 35, 0, 30},
        {20, 25, 30, 0}
    };

    int n = static_cast<int>(distance.size());
    int fullMask = (1 << n) - 1;

    vector<vector<int>> dp(1 << n, vector<int>(n, INF));
    vector<vector<int>> parent(1 << n, vector<int>(n, -1));

    dp[1][0] = 0; // start at city 0 with only city 0 visited

    for (int mask = 1; mask <= fullMask; ++mask) {
        for (int last = 0; last < n; ++last) {
            if (dp[mask][last] == INF) continue;
            if ((mask & (1 << last)) == 0) continue;

            for (int next = 0; next < n; ++next) {
                if (mask & (1 << next)) continue;

                int nextMask = mask | (1 << next);
                int candidate = dp[mask][last] + distance[last][next];

                if (candidate < dp[nextMask][next]) {
                    dp[nextMask][next] = candidate;
                    parent[nextMask][next] = last;
                }
            }
        }
    }

    int best = INF;
    int lastCity = -1;
    for (int city = 1; city < n; ++city) {
        int tour = dp[fullMask][city] + distance[city][0];
        if (tour < best) {
            best = tour;
            lastCity = city;
        }
    }

    vector<int> tour;
    int mask = fullMask;
    int current = lastCity;
    while (current != -1) {
        tour.push_back(current);
        int previous = parent[mask][current];
        mask ^= (1 << current);
        current = previous;
    }
    reverse(tour.begin(), tour.end());

    cout << "minimum tour cost: " << best << '\n';
    cout << "tour: ";
    for (size_t i = 0; i < tour.size(); ++i) {
        if (i != 0) cout << " -> ";
        cout << tour[i];
    }
    cout << " -> 0\n";

    return 0;
}
