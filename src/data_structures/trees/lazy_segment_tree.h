#ifndef DSA_LAZY_SEGMENT_TREE_H
#define DSA_LAZY_SEGMENT_TREE_H

#include <algorithm>
#include <cstddef>
#include <vector>

// ---------------------------------------------------------------------------
// Segment tree with lazy propagation
//
// Range additions are stored in a `lazy` value and pushed to the children only
// when a query or update actually needs them. This keeps both range add and
// range sum at O(log n).
//
// Indexing: half-open intervals [left, right).
// ---------------------------------------------------------------------------
class LazySegmentTree {
public:
    explicit LazySegmentTree(const std::vector<long long>& values)
        : size_(static_cast<int>(values.size())),
          tree_(4 * std::max<std::size_t>(1, values.size()), 0),
          lazy_(4 * std::max<std::size_t>(1, values.size()), 0) {
        if (!values.empty()) build(1, 0, size_, values);
    }

    void add(int left, int right, long long value) {
        if (left < 0 || right > size_ || left >= right) return;
        update(1, 0, size_, left, right, value);
    }

    long long sum(int left, int right) {
        if (left < 0 || right > size_ || left >= right) return 0;
        return query(1, 0, size_, left, right);
    }

private:
    int size_;
    std::vector<long long> tree_;
    std::vector<long long> lazy_;

    void build(int node, int left, int right,
               const std::vector<long long>& values) {
        if (right - left == 1) {
            tree_[node] = values[left];
            return;
        }

        int middle = left + (right - left) / 2;
        build(2 * node, left, middle, values);
        build(2 * node + 1, middle, right, values);
        tree_[node] = tree_[2 * node] + tree_[2 * node + 1];
    }

    void apply(int node, int left, int right, long long value) {
        tree_[node] += value * (right - left);
        lazy_[node] += value;
    }

    void push(int node, int left, int right) {
        if (lazy_[node] == 0) return;

        int middle = left + (right - left) / 2;
        apply(2 * node, left, middle, lazy_[node]);
        apply(2 * node + 1, middle, right, lazy_[node]);
        lazy_[node] = 0;
    }

    void update(int node, int left, int right, int queryLeft,
                int queryRight, long long value) {
        if (queryRight <= left || right <= queryLeft) return;

        if (queryLeft <= left && right <= queryRight) {
            apply(node, left, right, value);
            return;
        }

        push(node, left, right);
        int middle = left + (right - left) / 2;
        update(2 * node, left, middle, queryLeft, queryRight, value);
        update(2 * node + 1, middle, right, queryLeft, queryRight, value);
        tree_[node] = tree_[2 * node] + tree_[2 * node + 1];
    }

    long long query(int node, int left, int right, int queryLeft,
                    int queryRight) {
        if (queryRight <= left || right <= queryLeft) return 0;

        if (queryLeft <= left && right <= queryRight) {
            return tree_[node];
        }

        push(node, left, right);
        int middle = left + (right - left) / 2;
        return query(2 * node, left, middle, queryLeft, queryRight) +
               query(2 * node + 1, middle, right, queryLeft, queryRight);
    }
};

#endif
