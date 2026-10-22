#include <algorithm>
#include <iostream>
#include <numeric>
#include <random>
#include <utility>
#include <vector>

using namespace std;

// ---------------------------------------------------------------------------
// Randomized algorithms
//
// Fisher-Yates shuffle: walk from the end, swap each position with a uniformly
// random position at or before it. Every permutation is equally likely.
//
// Reservoir sampling: choose k items from a stream of unknown length. Keep the
// first k; for item i (0-based, i >= k), replace a random reservoir slot with
// probability k / (i + 1).
//
// Time:  O(n)
// Space: O(1) shuffle, O(k) reservoir
// ---------------------------------------------------------------------------
template <typename T>
void fisherYatesShuffle(vector<T>& values, mt19937& rng) {
    for (int i = static_cast<int>(values.size()) - 1; i > 0; --i) {
        uniform_int_distribution<int> pick(0, i);
        swap(values[i], values[pick(rng)]);
    }
}

template <typename T>
vector<T> reservoirSample(const vector<T>& stream, int k, mt19937& rng) {
    if (k <= 0) return {};
    if (k >= static_cast<int>(stream.size())) return stream;

    vector<T> reservoir(stream.begin(), stream.begin() + k);

    for (int i = k; i < static_cast<int>(stream.size()); ++i) {
        uniform_int_distribution<int> pick(0, i);
        int slot = pick(rng);
        if (slot < k) reservoir[slot] = stream[i];
    }

    return reservoir;
}

int main() {
    mt19937 rng(12345); // fixed seed so the demo is repeatable

    vector<int> cards = {1, 2, 3, 4, 5, 6, 7, 8};
    fisherYatesShuffle(cards, rng);
    cout << "shuffled: ";
    for (int card : cards) cout << card << ' ';
    cout << '\n';

    vector<int> stream = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
    vector<int> sample = reservoirSample(stream, 3, rng);
    cout << "reservoir sample of 3: ";
    for (int value : sample) cout << value << ' ';
    cout << '\n';

    return 0;
}
