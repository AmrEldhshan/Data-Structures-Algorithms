#include <iostream>
#include <tuple>
#include <utility>
#include <vector>

using namespace std;

// ---------------------------------------------------------------------------
// Prefix sums and difference arrays
//
// Prefix sums answer range-sum queries in O(1) after O(n) preprocessing:
//   prefix[i] = values[0] + ... + values[i-1]
//   sum(l, r) = prefix[r + 1] - prefix[l]
//
// Difference arrays do the opposite: many range additions followed by one final
// reconstruction. To add v to [l, r]:
//   difference[l] += v
//   difference[r + 1] -= v
// A prefix sum of the difference array then gives the final values.
// ---------------------------------------------------------------------------
struct RangeSum {
    vector<long long> prefix;

    explicit RangeSum(const vector<int>& values)
        : prefix(values.size() + 1, 0) {
        for (size_t i = 0; i < values.size(); ++i) {
            prefix[i + 1] = prefix[i] + values[i];
        }
    }

    long long query(int left, int right) const {
        return prefix[right + 1] - prefix[left];
    }
};

vector<int> applyRangeUpdates(int size,
                              const vector<tuple<int, int, int>>& updates) {
    vector<int> difference(size + 1, 0);

    for (const auto& [left, right, value] : updates) {
        difference[left] += value;
        difference[right + 1] -= value;
    }

    vector<int> values(size, 0);
    int running = 0;
    for (int i = 0; i < size; ++i) {
        running += difference[i];
        values[i] = running;
    }

    return values;
}

int main() {
    vector<int> values = {3, 1, 4, 1, 5, 9, 2, 6};

    RangeSum sums(values);
    cout << "values: ";
    for (int value : values) cout << value << ' ';
    cout << "\n\nrange sums:\n";
    for (auto [left, right] : {pair<int, int>{0, 2}, {2, 5}, {0, 7}, {4, 4}}) {
        cout << "  sum[" << left << ".." << right << "] = "
             << sums.query(left, right) << '\n';
    }

    // Add 10 to [1, 3], 5 to [3, 6], and -2 to [0, 1].
    vector<tuple<int, int, int>> updates = {
        {1, 3, 10}, {3, 6, 5}, {0, 1, -2}
    };
    vector<int> updated = applyRangeUpdates(values.size(), updates);

    cout << "\nafter range updates: ";
    for (int value : updated) cout << value << ' ';
    cout << '\n';

    return 0;
}
