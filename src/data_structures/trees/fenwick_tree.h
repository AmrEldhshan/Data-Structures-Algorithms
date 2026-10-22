#ifndef DSA_FENWICK_TREE_H
#define DSA_FENWICK_TREE_H

#include <stdexcept>
#include <vector>

// ---------------------------------------------------------------------------
// Fenwick tree (Binary Indexed Tree, BIT)
//
// Stores an array of numbers and supports:
//   add(index, delta)       point update
//   prefixSum(index)        sum of values[0..index]
//   rangeSum(left, right)   sum of values[left..right]
//
// The trick: index i in the internal array stores the sum of a block whose
// length is the lowest set bit of i. Walking i -= i & -i visits the blocks
// that cover [0, i], so both operations touch only O(log n) entries.
//
// 1-based indexing is used internally; the public API is 0-based.
//
// Time: O(log n) per operation, O(n) build.
// Space: O(n).
// ---------------------------------------------------------------------------
class FenwickTree {
public:
    explicit FenwickTree(int size) : tree_(size + 1, 0) {
        if (size < 0) throw std::invalid_argument("FenwickTree: negative size");
    }

    explicit FenwickTree(const std::vector<long long>& values)
        : tree_(values.size() + 1, 0) {
        for (int index = 0; index < static_cast<int>(values.size()); ++index) {
            add(index, values[index]);
        }
    }

    int size() const { return static_cast<int>(tree_.size()) - 1; }

    void add(int index, long long delta) {
        checkIndex(index);
        for (int i = index + 1; i <= size(); i += i & -i) {
            tree_[i] += delta;
        }
    }

    // Sum of values[0..index]. Use index == -1 for an empty prefix (returns 0).
    long long prefixSum(int index) const {
        if (index < -1 || index >= size()) {
            throw std::out_of_range("FenwickTree::prefixSum: index out of range");
        }

        long long total = 0;
        for (int i = index + 1; i > 0; i -= i & -i) {
            total += tree_[i];
        }
        return total;
    }

    // Sum of values[left..right], inclusive.
    long long rangeSum(int left, int right) const {
        checkIndex(left);
        checkIndex(right);
        if (left > right) throw std::invalid_argument("FenwickTree: left > right");
        return prefixSum(right) - prefixSum(left - 1);
    }

private:
    void checkIndex(int index) const {
        if (index < 0 || index >= size()) {
            throw std::out_of_range("FenwickTree: index out of range");
        }
    }

    std::vector<long long> tree_;
};

#endif // DSA_FENWICK_TREE_H
