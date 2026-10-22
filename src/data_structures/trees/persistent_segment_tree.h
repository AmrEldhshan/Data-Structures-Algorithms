#ifndef DSA_PERSISTENT_SEGMENT_TREE_H
#define DSA_PERSISTENT_SEGMENT_TREE_H

#include <cstddef>
#include <stdexcept>
#include <vector>

// ---------------------------------------------------------------------------
// Persistent segment tree
//
// Every point update creates O(log n) new nodes and leaves the previous version
// untouched. A version is just the root index. Range-sum queries can be run on
// any historical version.
//
// Build: O(n)
// Update: O(log n) new nodes
// Query: O(log n)
// ---------------------------------------------------------------------------
class PersistentSegmentTree {
public:
    explicit PersistentSegmentTree(const std::vector<long long>& values)
        : size_(static_cast<int>(values.size())) {
        if (!values.empty()) {
            roots_.push_back(build(0, size_, values));
        } else {
            roots_.push_back(0);
            nodes_.push_back(Node{});
        }
    }

    int versionCount() const { return static_cast<int>(roots_.size()); }

    int update(int version, int index, long long value) {
        checkVersion(version);
        if (index < 0 || index >= size_) {
            throw std::out_of_range("PersistentSegmentTree: index");
        }

        roots_.push_back(updateNode(roots_[version], 0, size_, index, value));
        return static_cast<int>(roots_.size()) - 1;
    }

    long long sum(int version, int left, int right) const {
        checkVersion(version);
        if (left < 0 || right > size_ || left >= right) return 0;
        return query(roots_[version], 0, size_, left, right);
    }

private:
    struct Node {
        int left = 0;
        int right = 0;
        long long sum = 0;
    };

    int size_;
    std::vector<Node> nodes_{Node{}};
    std::vector<int> roots_;

    void checkVersion(int version) const {
        if (version < 0 || version >= versionCount()) {
            throw std::out_of_range("PersistentSegmentTree: version");
        }
    }

    int makeNode(int left, int right, long long sum) {
        nodes_.push_back(Node{left, right, sum});
        return static_cast<int>(nodes_.size()) - 1;
    }

    int build(int left, int right, const std::vector<long long>& values) {
        if (right - left == 1) return makeNode(0, 0, values[left]);

        int middle = left + (right - left) / 2;
        int leftChild = build(left, middle, values);
        int rightChild = build(middle, right, values);
        return makeNode(leftChild, rightChild,
                        nodes_[leftChild].sum + nodes_[rightChild].sum);
    }

    int updateNode(int node, int left, int right, int index, long long value) {
        if (right - left == 1) return makeNode(0, 0, value);

        int middle = left + (right - left) / 2;

        if (index < middle) {
            int newLeft = updateNode(nodes_[node].left, left, middle, index, value);
            return makeNode(newLeft, nodes_[node].right,
                            nodes_[newLeft].sum + nodes_[nodes_[node].right].sum);
        }

        int newRight = updateNode(nodes_[node].right, middle, right, index, value);
        return makeNode(nodes_[node].left, newRight,
                        nodes_[nodes_[node].left].sum + nodes_[newRight].sum);
    }

    long long query(int node, int left, int right, int queryLeft,
                    int queryRight) const {
        if (queryRight <= left || right <= queryLeft) return 0;
        if (queryLeft <= left && right <= queryRight) return nodes_[node].sum;

        int middle = left + (right - left) / 2;
        return query(nodes_[node].left, left, middle, queryLeft, queryRight) +
               query(nodes_[node].right, middle, right, queryLeft, queryRight);
    }
};

#endif
