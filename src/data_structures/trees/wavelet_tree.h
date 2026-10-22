#ifndef DSA_WAVELET_TREE_H
#define DSA_WAVELET_TREE_H

#include <algorithm>
#include <cstddef>
#include <memory>
#include <stdexcept>
#include <vector>

// ---------------------------------------------------------------------------
// Wavelet tree
//
// A wavelet tree recursively partitions values by their median. Each node stores
// a prefix count of how many values went left. This supports rank/select and
// range k-th smallest queries without a full merge-sort tree.
//
// Build: O(n log σ), where σ is the number of distinct values
// countLess: O(log σ)
// kthSmallest: O(log σ)
// ---------------------------------------------------------------------------
class WaveletTree {
public:
    explicit WaveletTree(const std::vector<int>& values) : size_(values.size()) {
        if (values.empty()) return;

        int low = *std::min_element(values.begin(), values.end());
        int high = *std::max_element(values.begin(), values.end());
        root_ = build(values, low, high);
    }

    // Number of values < value in [left, right).
    int countLess(int left, int right, int value) const {
        if (root_ == nullptr) return 0;
        return countLess(root_.get(), left, right, value);
    }

    int countLessOrEqual(int left, int right, int value) const {
        return countLess(left, right, value + 1);
    }

    // k is 1-based inside [left, right).
    int kthSmallest(int left, int right, int k) const {
        if (root_ == nullptr) throw std::out_of_range("WaveletTree: empty");
        if (k < 1 || left < 0 || right > static_cast<int>(size_) ||
            left >= right || k > right - left) {
            throw std::out_of_range("WaveletTree: invalid query");
        }
        return kthSmallest(root_.get(), left, right, k);
    }

private:
    struct Node {
        int low = 0;
        int high = 0;
        std::vector<int> prefixZeros;
        std::unique_ptr<Node> left;
        std::unique_ptr<Node> right;
    };

    std::unique_ptr<Node> root_;
    std::size_t size_ = 0;

    std::unique_ptr<Node> build(const std::vector<int>& values, int low, int high) {
        auto node = std::make_unique<Node>();
        node->low = low;
        node->high = high;
        node->prefixZeros.resize(values.size() + 1, 0);

        if (low == high || values.empty()) return node;

        int middle = low + (high - low) / 2;
        std::vector<int> leftValues;
        std::vector<int> rightValues;
        leftValues.reserve(values.size());
        rightValues.reserve(values.size());

        for (std::size_t i = 0; i < values.size(); ++i) {
            bool goesLeft = values[i] <= middle;
            node->prefixZeros[i + 1] = node->prefixZeros[i] + (goesLeft ? 1 : 0);
            if (goesLeft) leftValues.push_back(values[i]);
            else rightValues.push_back(values[i]);
        }

        node->left = build(leftValues, low, middle);
        node->right = build(rightValues, middle + 1, high);
        return node;
    }

    int countLess(const Node* node, int left, int right, int value) const {
        if (node == nullptr || left >= right) return 0;
        if (value <= node->low) return 0;
        if (value > node->high) return right - left;

        int middle = node->low + (node->high - node->low) / 2;
        int zerosLeft = node->prefixZeros[left];
        int zerosRight = node->prefixZeros[right];
        int leftCount = zerosRight - zerosLeft;

        if (value <= middle) {
            return countLess(node->left.get(), zerosLeft, zerosRight, value);
        }

        return leftCount +
               countLess(node->right.get(), left - zerosLeft, right - zerosRight,
                         value);
    }

    int kthSmallest(const Node* node, int left, int right, int k) const {
        if (node->low == node->high) return node->low;

        int zerosLeft = node->prefixZeros[left];
        int zerosRight = node->prefixZeros[right];
        int leftCount = zerosRight - zerosLeft;

        if (k <= leftCount) {
            return kthSmallest(node->left.get(), zerosLeft, zerosRight, k);
        }

        return kthSmallest(node->right.get(), left - zerosLeft, right - zerosRight,
                           k - leftCount);
    }
};

#endif
