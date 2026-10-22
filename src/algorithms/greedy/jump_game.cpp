#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

// ---------------------------------------------------------------------------
// Jump game
//
// `reach` is the furthest index reachable with the current number of jumps.
// Scan the array; when the scan passes the current reach, one more jump is
// needed. If the reach never advances past a zero, the end is unreachable.
//
// Time:  O(n)
// Space: O(1)
// ---------------------------------------------------------------------------
int minimumJumps(const vector<int>& steps) {
    int jumps = 0;
    int currentEnd = 0;
    int farthest = 0;

    for (int i = 0; i < static_cast<int>(steps.size()) - 1; ++i) {
        farthest = max(farthest, i + steps[i]);

        if (i == currentEnd) {
            if (farthest == currentEnd) return -1; // stuck
            ++jumps;
            currentEnd = farthest;
        }
    }

    return jumps;
}

bool canReachEnd(const vector<int>& steps) {
    int farthest = 0;

    for (int i = 0; i < static_cast<int>(steps.size()); ++i) {
        if (i > farthest) return false;
        farthest = max(farthest, i + steps[i]);
    }

    return true;
}

int main() {
    for (const vector<int>& steps : {
             vector<int>{2, 3, 1, 1, 4},
             vector<int>{2, 3, 0, 1, 4},
             vector<int>{3, 2, 1, 0, 4}}) {
        cout << "steps: ";
        for (int step : steps) cout << step << ' ';
        cout << "\n  can reach: " << (canReachEnd(steps) ? "yes" : "no")
             << ", minimum jumps: " << minimumJumps(steps) << "\n";
    }

    return 0;
}
