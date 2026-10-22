#ifndef DSA_B_TREE_H
#define DSA_B_TREE_H

#include <algorithm>
#include <cstddef>
#include <iterator>
#include <memory>
#include <stdexcept>
#include <utility>
#include <vector>

// ---------------------------------------------------------------------------
// B-tree
//
// A multi-way search tree with a minimum degree `minimumDegree`. Every node
// holds at most `2t - 1` keys and at least `t - 1` keys (except the root).
// Insertion splits a full child before descending into it, so the tree stays
// balanced. Deletion is left as an exercise; search and insertion are the core.
//
// search / insert: O(log n)
// ---------------------------------------------------------------------------
template <typename T>
class BTree {
public:
    explicit BTree(int minimumDegree = 2) : minimumDegree_(minimumDegree) {
        if (minimumDegree < 2) {
            throw std::invalid_argument("BTree: minimum degree must be >= 2");
        }
        root_ = std::make_unique<Node>(true);
    }

    int minimumDegree() const { return minimumDegree_; }
    std::size_t size() const { return size_; }
    bool empty() const { return size_ == 0; }

    bool contains(const T& key) const { return search(root_.get(), key); }

    void insert(const T& key) {
        if (root_->keys.size() == maxKeys()) {
            auto newRoot = std::make_unique<Node>(false);
            newRoot->children.push_back(std::move(root_));
            splitChild(newRoot.get(), 0);
            root_ = std::move(newRoot);
        }

        insertNonFull(root_.get(), key);
    }

    std::vector<T> inOrder() const {
        std::vector<T> result;
        result.reserve(size_);
        traverse(root_.get(), result);
        return result;
    }

private:
    struct Node {
        std::vector<T> keys;
        std::vector<std::unique_ptr<Node>> children;
        bool leaf = true;

        explicit Node(bool isLeaf) : leaf(isLeaf) {}
    };

    int minimumDegree_;
    std::unique_ptr<Node> root_;
    std::size_t size_ = 0;

    std::size_t maxKeys() const {
        return static_cast<std::size_t>(2 * minimumDegree_ - 1);
    }

    std::size_t minKeys() const {
        return static_cast<std::size_t>(minimumDegree_ - 1);
    }

    bool search(const Node* node, const T& key) const {
        std::size_t index = 0;
        while (index < node->keys.size() && key > node->keys[index]) ++index;

        if (index < node->keys.size() && node->keys[index] == key) return true;
        if (node->leaf) return false;
        return search(node->children[index].get(), key);
    }

    void splitChild(Node* parent, std::size_t childIndex) {
        Node* fullChild = parent->children[childIndex].get();
        auto right = std::make_unique<Node>(fullChild->leaf);

        std::size_t middle = fullChild->keys.size() / 2;
        T promoted = fullChild->keys[middle];

        right->keys.assign(fullChild->keys.begin() + static_cast<std::ptrdiff_t>(middle + 1),
                           fullChild->keys.end());
        fullChild->keys.erase(fullChild->keys.begin() + static_cast<std::ptrdiff_t>(middle),
                              fullChild->keys.end());

        if (!fullChild->leaf) {
            right->children.assign(
                std::make_move_iterator(fullChild->children.begin() +
                                        static_cast<std::ptrdiff_t>(middle + 1)),
                std::make_move_iterator(fullChild->children.end()));
            fullChild->children.erase(
                fullChild->children.begin() + static_cast<std::ptrdiff_t>(middle + 1),
                fullChild->children.end());
        }

        parent->keys.insert(parent->keys.begin() +
                                static_cast<std::ptrdiff_t>(childIndex),
                            promoted);
        parent->children.insert(
            parent->children.begin() + static_cast<std::ptrdiff_t>(childIndex + 1),
            std::move(right));
    }

    void insertNonFull(Node* node, const T& key) {
        if (node->leaf) {
            auto position = std::lower_bound(node->keys.begin(), node->keys.end(), key);
            if (position != node->keys.end() && *position == key) return;
            node->keys.insert(position, key);
            ++size_;
            return;
        }

        std::size_t index = 0;
        while (index < node->keys.size() && key > node->keys[index]) ++index;

        if (index < node->keys.size() && node->keys[index] == key) return;

        if (node->children[index]->keys.size() == maxKeys()) {
            splitChild(node, index);
            if (key > node->keys[index]) ++index;
            else if (key == node->keys[index]) return;
        }

        insertNonFull(node->children[index].get(), key);
    }

    void traverse(const Node* node, std::vector<T>& result) const {
        for (std::size_t i = 0; i < node->keys.size(); ++i) {
            if (!node->leaf) traverse(node->children[i].get(), result);
            result.push_back(node->keys[i]);
        }

        if (!node->leaf) traverse(node->children.back().get(), result);
    }
};

#endif
