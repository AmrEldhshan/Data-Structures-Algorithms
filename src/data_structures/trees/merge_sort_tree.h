#ifndef DSA_MERGE_SORT_TREE_H
#define DSA_MERGE_SORT_TREE_H

#include <algorithm>
#include <cstddef>
#include <stdexcept>
#include <vector>

// ---------------------------------------------------------------------------
// Merge-sort tree
//
// A segment tree whose nodes store the sorted values of their range. It answers
// "how many values in [left, right) are <= x?" by decomposing the range into
// O(log n) nodes and binary-searching each node's sorted vector.
//
// Build: O(n log n)
// countLessOrEqual: O(log² n)
// kthSmallest: O(log V * log² n) using a value binary search
// ---------------------------------------------------------------------------
template <typename T>
class MergeSortTree {
public:
    explicit MergeSortTree(const std::vector<T>& values)
        : values_(values),
          sortedValues_(values),
          tree_(4 * std::max<std::size_t>(1, values.size())) {
        std::sort(sortedValues_.begin(), sortedValues_.end());
        if (!values.empty()) build(1, 0, static_cast<int>(values.size()));
    }

    // Number of elements <= value in the half-open range [left, right).
    int countLessOrEqual(int left, int right, const T& value) const {
        if (left < 0 || right > static_cast<int>(values_.size()) || left >= right) {
            return 0;
        }
        return count(1, 0, static_cast<int>(values_.size()), left, right, value);
    }

    // k is 1-based inside the range.
    T kthSmallest(int left, int right, int k) const {
        if (left < 0 || right > static_cast<int>(values_.size()) || left >= right) {
            throw std::out_of_range("MergeSortTree: invalid range");
        }
        if (k < 1 || k > right - left) {
            throw std::out_of_range("MergeSortTree: invalid k");
        }

        int low = 0;
        int high = static_cast<int>(sortedValues_.size()) - 1;

        while (low < high) {
            int middle = low + (high - low) / 2;
            if (countLessOrEqual(left, right, sortedValues_[middle]) >= k) {
                high = middle;
            } else {
                low = middle + 1;
            }
        }

        return sortedValues_[low];
    }

private:
    std::vector<T> values_;
    std::vector<T> sortedValues_;
    std::vector<std::vector<T>> tree_;

    void build(int node, int left, int right) {
        if (right - left == 1) {
            tree_[node] = {values_[left]};
            return;
        }

        int middle = left + (right - left) / 2;
        build(2 * node, left, middle);
        build(2 * node + 1, middle, right);

        const std::vector<T>& a = tree_[2 * node];
        const std::vector<T>& b = tree_[2 * node + 1];
        tree_[node].resize(a.size() + b.size());
        std::merge(a.begin(), a.end(), b.begin(), b.end(), tree_[node].begin());
    }

    int count(int node, int left, int right, int queryLeft, int queryRight,
              const T& value) const {
        if (queryRight <= left || right <= queryLeft) return 0;

        if (queryLeft <= left && right <= queryRight) {
            const std::vector<T>& sorted = tree_[node];
            return static_cast<int>(
                std::upper_bound(sorted.begin(), sorted.end(), value) - sorted.begin());
        }

        int middle = left + (right - left) / 2;
        return count(2 * node, left, middle, queryLeft, queryRight, value) +
               count(2 * node + 1, middle, right, queryLeft, queryRight, value);
    }
};

#endif
