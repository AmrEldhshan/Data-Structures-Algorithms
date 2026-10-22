#include <algorithm>
#include <iomanip>
#include <iostream>
#include <vector>

using namespace std;

// ---------------------------------------------------------------------------
// Fractional knapsack (greedy)
//
// Items can be split, so the best strategy is to take items in decreasing
// order of value per unit of weight. This is the greedy problem that looks
// almost identical to 0/1 knapsack, where the same strategy fails.
//
// Time:  O(n log n)
// Space: O(n)
// ---------------------------------------------------------------------------
struct Item {
    string name;
    int value;
    int weight;
};

double fractionalKnapsack(vector<Item> items, int capacity) {
    sort(items.begin(), items.end(), [](const Item& a, const Item& b) {
        return static_cast<double>(a.value) / a.weight >
               static_cast<double>(b.value) / b.weight;
    });

    double total = 0.0;

    for (const Item& item : items) {
        if (capacity == 0) break;

        int taken = min(capacity, item.weight);
        double fraction = static_cast<double>(taken) / item.weight;
        total += item.value * fraction;
        capacity -= taken;

        cout << "  take " << setw(4) << fixed << setprecision(2)
             << fraction * 100 << "% of " << item.name << '\n';
    }

    return total;
}

int main() {
    vector<Item> items = {
        {"gold", 60, 10},
        {"silver", 100, 20},
        {"bronze", 120, 30}
    };

    int capacity = 50;
    cout << "capacity: " << capacity << "\n";
    double best = fractionalKnapsack(items, capacity);
    cout << "maximum value = " << best << '\n';

    return 0;
}
