#ifndef DSA_SPARSE_TABLE_H
#define DSA_SPARSE_TABLE_H

#include <algorithm>
#include <stdexcept>
#include <vector>

// ---------------------------------------------------------------------------
// Sparse table for range-minimum queries (RMQ)
//
// table[k][i] stores the minimum of the block of length 2^k starting at i.
// A query [left, right] picks the largest k with 2^k <= length and combines
// the two overlapping blocks of length 2^k that cover the range. Because min
// is idempotent, overlapping is harmless.
//
// Build: O(n log n)
// Query: O(1)
// Space: O(n log n)
//
// The same layout works for any idempotent operation (min, max, gcd, ...).
// Only the build/query combine step would change.
// ---------------------------------------------------------------------------
class SparseTable {
public:
    explicit SparseTable(const std::vector<int>& values) : values_(values) {
        build();
    }

    bool empty() const { return values_.empty(); }

    int size() const { return static_cast<int>(values_.size()); }

    // Minimum of values[left..right], inclusive.
    int rangeMin(int left, int right) const {
        if (left < 0 || right >= size() || left > right) {
            throw std::out_of_range("SparseTable::rangeMin: invalid range");
        }

        int length = right - left + 1;
        int level = 0;
        while ((1 << (level + 1)) <= length) ++level;

        int block = 1 << level;
        return std::min(table_[level][left], table_[level][right - block + 1]);
    }

private:
    void build() {
        int n = size();
        if (n == 0) return;

        int levels = 1;
        while ((1 << levels) <= n) ++levels;

        table_.assign(levels, std::vector<int>(n));
        table_[0] = values_;

        for (int level = 1; level < levels; ++level) {
            int half = 1 << (level - 1);
            for (int i = 0; i + (1 << level) <= n; ++i) {
                table_[level][i] =
                    std::min(table_[level - 1][i],
                             table_[level - 1][i + half]);
            }
        }
    }

    std::vector<int> values_;
    std::vector<std::vector<int>> table_;
};

#endif // DSA_SPARSE_TABLE_H
