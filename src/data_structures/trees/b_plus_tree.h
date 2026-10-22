#ifndef DSA_B_PLUS_TREE_H
#define DSA_B_PLUS_TREE_H

#include <algorithm>
#include <cstddef>
#include <memory>
#include <stdexcept>
#include <utility>
#include <vector>

// ---------------------------------------------------------------------------
// B+ tree
//
// Internal nodes store only separator keys; every key lives in a leaf. Leaves
// are kept in sorted order, which makes range scans efficient. This version
// implements search and insertion (splitting full leaves/internal nodes);
// deletion is left as an exercise.
//
// search / insert: O(log n)
// ---------------------------------------------------------------------------
template <typename T>
class BPlusTree {
public:
    explicit BPlusTree(int order = 4) : order_(order) {
        if (order < 3) {
            throw std::invalid_argument("BPlusTree: order must be >= 3");
        }
        root_ = std::make_unique<Node>(true);
    }

    std::size_t size() const { return size_; }
    bool empty() const { return size_ == 0; }

    bool contains(const T& key) const {
        const Node* node = root_.get();

        while (!node->leaf) {
            std::size_t index = 0;
            while (index < node->keys.size() && key >= node->keys[index]) ++index;
            node = node->children[index].get();
        }

        return std::binary_search(node->keys.begin(), node->keys.end(), key);
    }

    void insert(const T& key) {
        Split split = insertRecursive(root_.get(), key);

        if (split.didSplit) {
            auto newRoot = std::make_unique<Node>(false);
            newRoot->keys.push_back(split.separator);
            newRoot->children.push_back(std::move(root_));
            newRoot->children.push_back(std::move(split.right));
            root_ = std::move(newRoot);
        }
    }

    std::vector<T> values() const {
        std::vector<T> result;
        result.reserve(size_);
        collect(root_.get(), result);
        return result;
    }

private:
    struct Node {
        std::vector<T> keys;
        std::vector<std::unique_ptr<Node>> children;
        bool leaf = true;

        explicit Node(bool isLeaf) : leaf(isLeaf) {}
    };

    struct Split {
        bool didSplit = false;
        T separator{};
        std::unique_ptr<Node> right;
    };

    int order_;
    std::unique_ptr<Node> root_;
    std::size_t size_ = 0;

    std::size_t maxKeys() const { return static_cast<std::size_t>(order_ - 1); }

    Split insertRecursive(Node* node, const T& key) {
        if (node->leaf) {
            auto position = std::lower_bound(node->keys.begin(), node->keys.end(), key);
            if (position != node->keys.end() && *position == key) return {};

            node->keys.insert(position, key);
            ++size_;

            if (node->keys.size() <= maxKeys()) return {};
            return splitLeaf(node);
        }

        std::size_t index = 0;
        while (index < node->keys.size() && key >= node->keys[index]) ++index;

        Split childSplit = insertRecursive(node->children[index].get(), key);
        if (!childSplit.didSplit) return {};

        node->keys.insert(node->keys.begin() + static_cast<std::ptrdiff_t>(index),
                          childSplit.separator);
        node->children.insert(
            node->children.begin() + static_cast<std::ptrdiff_t>(index + 1),
            std::move(childSplit.right));

        if (node->keys.size() <= maxKeys()) return {};
        return splitInternal(node);
    }

    Split splitLeaf(Node* node) {
        auto right = std::make_unique<Node>(true);
        std::size_t middle = (node->keys.size() + 1) / 2;

        right->keys.assign(node->keys.begin() + static_cast<std::ptrdiff_t>(middle),
                           node->keys.end());
        node->keys.erase(node->keys.begin() + static_cast<std::ptrdiff_t>(middle),
                         node->keys.end());

        Split split;
        split.didSplit = true;
        split.separator = right->keys.front();
        split.right = std::move(right);
        return split;
    }

    Split splitInternal(Node* node) {
        auto right = std::make_unique<Node>(false);
        std::size_t middle = node->keys.size() / 2;
        T promoted = node->keys[middle];

        right->keys.assign(node->keys.begin() + static_cast<std::ptrdiff_t>(middle + 1),
                           node->keys.end());
        right->children.assign(
            std::make_move_iterator(node->children.begin() +
                                    static_cast<std::ptrdiff_t>(middle + 1)),
            std::make_move_iterator(node->children.end()));

        node->keys.erase(node->keys.begin() + static_cast<std::ptrdiff_t>(middle),
                         node->keys.end());
        node->children.erase(
            node->children.begin() + static_cast<std::ptrdiff_t>(middle + 1),
            node->children.end());

        Split split;
        split.didSplit = true;
        split.separator = promoted;
        split.right = std::move(right);
        return split;
    }

    static void collect(const Node* node, std::vector<T>& result) {
        if (node->leaf) {
            result.insert(result.end(), node->keys.begin(), node->keys.end());
            return;
        }

        for (const auto& child : node->children) collect(child.get(), result);
    }
};

#endif
