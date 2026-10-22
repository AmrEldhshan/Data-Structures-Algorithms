#ifndef DSA_DISJOINT_SPARSE_TABLE_H
#define DSA_DISJOINT_SPARSE_TABLE_H

#include <algorithm>
#include <bit>
#include <cstddef>
#include <stdexcept>
#include <vector>

// ---------------------------------------------------------------------------
// Disjoint sparse table
//
// Builds a table over power-of-two blocks. For a query [left, right], the
// highest bit where left and right differ selects a level; the answer is the
// minimum of a suffix of left's block and a prefix of right's block. Those two
// pieces are disjoint and together cover [left, right].
//
// Build: O(n log n)
// Query: O(1)
// ---------------------------------------------------------------------------
template <typename T, typename Compare = std::less<T>>
class DisjointSparseTable {
public:
    explicit DisjointSparseTable(const std::vector<T>& values, Compare compare = Compare())
        : values_(values), compare_(std::move(compare)) {
        if (values_.empty()) return;

        int levels = 1;
        while ((1 << levels) < static_cast<int>(values_.size())) ++levels;

        prefix_.assign(levels, std::vector<T>(values_.size()));
        suffix_.assign(levels, std::vector<T>(values_.size()));

        for (int level = 0; level < levels; ++level) {
            int blockSize = 1 << level;

            for (int start = 0; start < static_cast<int>(values_.size());
                 start += 2 * blockSize) {
                int middle = std::min(static_cast<int>(values_.size()),
                                      start + blockSize);
                int end = std::min(static_cast<int>(values_.size()),
                                   start + 2 * blockSize);

                if (start < middle) {
                    suffix_[level][middle - 1] = values_[middle - 1];
                    for (int i = middle - 2; i >= start; --i) {
                        suffix_[level][i] = better(suffix_[level][i + 1], values_[i]);
                    }
                }

                if (middle < end) {
                    prefix_[level][middle] = values_[middle];
                    for (int i = middle + 1; i < end; ++i) {
                        prefix_[level][i] = better(prefix_[level][i - 1], values_[i]);
                    }
                }
            }
        }
    }

    T query(int left, int right) const {
        if (values_.empty()) throw std::out_of_range("DisjointSparseTable: empty");
        if (left < 0 || right >= static_cast<int>(values_.size()) || left > right) {
            throw std::out_of_range("DisjointSparseTable: invalid range");
        }

        if (left == right) return values_[left];

        int level = 31 - std::countl_zero(static_cast<unsigned>(left ^ right));
        return better(suffix_[level][left], prefix_[level][right]);
    }

private:
    std::vector<T> values_;
    Compare compare_;
    std::vector<std::vector<T>> prefix_;
    std::vector<std::vector<T>> suffix_;

    T better(const T& a, const T& b) const {
        return compare_(b, a) ? b : a;
    }
};

#endif
