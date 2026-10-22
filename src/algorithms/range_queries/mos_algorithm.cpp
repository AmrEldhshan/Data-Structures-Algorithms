#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

// ---------------------------------------------------------------------------
// Mo's algorithm
//
// Answer offline range queries by reordering them so that consecutive queries
// move the current window as little as possible. Sort by the left endpoint's
// block, and alternate the right-endpoint direction for odd blocks.
//
// With block size sqrt(n), the total movement is O((n + q) sqrt(n)).
// ---------------------------------------------------------------------------
struct Query {
    int left;
    int right;
    int index;
};

vector<long long> rangeSums(const vector<int>& values,
                            const vector<Query>& queries) {
    int n = static_cast<int>(values.size());
    int blockSize = max(1, static_cast<int>(sqrt(n)));

    vector<Query> ordered = queries;
    sort(ordered.begin(), ordered.end(), [blockSize](const Query& a, const Query& b) {
        int blockA = a.left / blockSize;
        int blockB = b.left / blockSize;
        if (blockA != blockB) return blockA < blockB;
        return (blockA % 2 == 0) ? a.right < b.right : a.right > b.right;
    });

    vector<long long> answers(queries.size(), 0);
    long long currentSum = 0;
    int currentLeft = 0;
    int currentRight = -1;

    auto add = [&](int index) { currentSum += values[index]; };
    auto remove = [&](int index) { currentSum -= values[index]; };

    for (const Query& query : ordered) {
        while (currentLeft > query.left) add(--currentLeft);
        while (currentRight < query.right) add(++currentRight);
        while (currentLeft < query.left) remove(currentLeft++);
        while (currentRight > query.right) remove(currentRight--);

        answers[query.index] = currentSum;
    }

    return answers;
}

int main() {
    vector<int> values = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5};
    vector<Query> queries = {
        {0, 2, 0}, {3, 6, 1}, {1, 5, 2}, {0, 10, 3}, {7, 9, 4}
    };

    vector<long long> answers = rangeSums(values, queries);

    cout << "values: ";
    for (int value : values) cout << value << ' ';
    cout << "\n\nrange sums:\n";
    for (const Query& query : queries) {
        cout << "  sum[" << query.left << ", " << query.right << "] = "
             << answers[query.index] << '\n';
    }

    return 0;
}
