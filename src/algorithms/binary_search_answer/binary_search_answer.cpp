#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

// ---------------------------------------------------------------------------
// Binary search on the answer
//
// Sometimes we do not search an array; we search a monotone predicate over a
// range of possible answers. "Can we ship everything in D days with capacity C?"
// is false for small C and true for large C, so binary search finds the first
// true capacity.
//
// Time:  O(n log(sum(weights)))
// Space: O(1)
// ---------------------------------------------------------------------------
int daysNeeded(const vector<int>& weights, int capacity) {
    int days = 1;
    int currentLoad = 0;

    for (int weight : weights) {
        if (currentLoad + weight > capacity) {
            ++days;
            currentLoad = 0;
        }
        currentLoad += weight;
    }

    return days;
}

int minimumCapacity(const vector<int>& weights, int days) {
    int low = *max_element(weights.begin(), weights.end());
    int high = accumulate(weights.begin(), weights.end(), 0);

    while (low < high) {
        int middle = low + (high - low) / 2;

        if (daysNeeded(weights, middle) <= days) {
            high = middle;
        } else {
            low = middle + 1;
        }
    }

    return low;
}

int main() {
    vector<int> weights = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int days = 5;

    cout << "weights: ";
    for (int weight : weights) cout << weight << ' ';
    cout << "\ndays: " << days << '\n';
    cout << "minimum capacity: " << minimumCapacity(weights, days) << '\n';

    // Show the predicate for a few capacities.
    for (int capacity : {10, 14, 15, 20}) {
        cout << "  capacity " << capacity << " needs "
             << daysNeeded(weights, capacity) << " days\n";
    }

    return 0;
}
