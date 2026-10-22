#ifndef DSA_SPLAY_TREE_H
#define DSA_SPLAY_TREE_H

#include <cstddef>
#include <functional>
#include <stdexcept>
#include <vector>

// ---------------------------------------------------------------------------
// Splay tree
//
// A self-adjusting binary search tree. Every access splays the accessed node to
// the root using zig, zig-zig, and zig-zag rotations. Recently used keys become
// cheap to access again.
//
// Amortised: O(log n) per operation.
// Worst single operation: O(n).
// ---------------------------------------------------------------------------
template <typename T, typename Compare = std::less<T>>
class SplayTree {
public:
    explicit SplayTree(Compare compare = Compare()) : compare_(std::move(compare)) {}

    SplayTree(const SplayTree&) = delete;
    SplayTree& operator=(const SplayTree&) = delete;

    ~SplayTree() { clear(); }

    void clear() {
        destroy(root_);
        root_ = nullptr;
        count_ = 0;
    }

    std::size_t size() const { return count_; }
    bool empty() const { return root_ == nullptr; }

    bool contains(const T& key) {
        Node* node = findNode(key);
        if (node == nullptr) {
            if (last_ != nullptr) splay(last_);
            return false;
        }
        splay(node);
        return true;
    }

    void insert(const T& key) {
        if (root_ == nullptr) {
            root_ = new Node(key);
            ++count_;
            return;
        }

        Node* current = root_;
        Node* parent = nullptr;

        while (current != nullptr) {
            parent = current;

            if (compare_(key, current->key)) {
                current = current->left;
            } else if (compare_(current->key, key)) {
                current = current->right;
            } else {
                splay(current);
                return;
            }
        }

        Node* node = new Node(key);
        node->parent = parent;
        if (compare_(key, parent->key)) parent->left = node;
        else parent->right = node;

        ++count_;
        splay(node);
    }

    bool erase(const T& key) {
        Node* node = findNode(key);
        if (node == nullptr) {
            if (last_ != nullptr) splay(last_);
            return false;
        }

        splay(node);

        Node* left = node->left;
        Node* right = node->right;

        if (left != nullptr) left->parent = nullptr;
        if (right != nullptr) right->parent = nullptr;

        if (left == nullptr) {
            root_ = right;
        } else {
            root_ = left;
            Node* maximum = left;
            while (maximum->right != nullptr) maximum = maximum->right;
            splay(maximum);
            root_->right = right;
            if (right != nullptr) right->parent = root_;
            update(root_);
        }

        node->left = nullptr;
        node->right = nullptr;
        delete node;
        --count_;
        return true;
    }

    const T& minimum() {
        if (root_ == nullptr) throw std::out_of_range("SplayTree: empty");
        Node* node = root_;
        while (node->left != nullptr) node = node->left;
        splay(node);
        return root_->key;
    }

    const T& maximum() {
        if (root_ == nullptr) throw std::out_of_range("SplayTree: empty");
        Node* node = root_;
        while (node->right != nullptr) node = node->right;
        splay(node);
        return root_->key;
    }

    // 0-based order statistic.
    const T& kth(std::size_t index) {
        if (index >= count_) throw std::out_of_range("SplayTree: kth");

        Node* node = root_;
        while (node != nullptr) {
            std::size_t leftSize = sizeOf(node->left);

            if (index < leftSize) {
                node = node->left;
            } else if (index == leftSize) {
                splay(node);
                return root_->key;
            } else {
                index -= leftSize + 1;
                node = node->right;
            }
        }

        throw std::out_of_range("SplayTree: kth");
    }

    // Number of keys strictly smaller than `key`.
    std::size_t rank(const T& key) {
        Node* node = findNode(key);
        if (node == nullptr) {
            if (last_ != nullptr) splay(last_);
            std::size_t result = 0;
            const Node* current = root_;
            while (current != nullptr) {
                if (compare_(current->key, key)) {
                    result += sizeOf(current->left) + 1;
                    current = current->right;
                } else {
                    current = current->left;
                }
            }
            return result;
        }

        splay(node);
        return sizeOf(root_->left);
    }

    std::vector<T> inOrder() {
        std::vector<T> result;
        result.reserve(count_);
        collect(root_, result);
        return result;
    }

private:
    struct Node {
        T key;
        Node* left = nullptr;
        Node* right = nullptr;
        Node* parent = nullptr;
        std::size_t subtreeSize = 1;

        explicit Node(const T& value) : key(value) {}
    };

    Compare compare_;
    Node* root_ = nullptr;
    Node* last_ = nullptr;
    std::size_t count_ = 0;

    static std::size_t sizeOf(const Node* node) {
        return node == nullptr ? 0 : node->subtreeSize;
    }

    static void update(Node* node) {
        if (node != nullptr) {
            node->subtreeSize = 1 + sizeOf(node->left) + sizeOf(node->right);
        }
    }

    void rotateLeft(Node* node) {
        Node* pivot = node->right;
        node->right = pivot->left;
        if (pivot->left != nullptr) pivot->left->parent = node;

        pivot->parent = node->parent;
        if (node->parent == nullptr) root_ = pivot;
        else if (node == node->parent->left) node->parent->left = pivot;
        else node->parent->right = pivot;

        pivot->left = node;
        node->parent = pivot;

        update(node);
        update(pivot);
    }

    void rotateRight(Node* node) {
        Node* pivot = node->left;
        node->left = pivot->right;
        if (pivot->right != nullptr) pivot->right->parent = node;

        pivot->parent = node->parent;
        if (node->parent == nullptr) root_ = pivot;
        else if (node == node->parent->right) node->parent->right = pivot;
        else node->parent->left = pivot;

        pivot->right = node;
        node->parent = pivot;

        update(node);
        update(pivot);
    }

    void splay(Node* node) {
        while (node->parent != nullptr) {
            Node* parent = node->parent;
            Node* grandparent = parent->parent;

            if (grandparent == nullptr) {
                if (node == parent->left) rotateRight(parent);
                else rotateLeft(parent);
            } else if (node == parent->left && parent == grandparent->left) {
                rotateRight(grandparent);
                rotateRight(parent);
            } else if (node == parent->right && parent == grandparent->right) {
                rotateLeft(grandparent);
                rotateLeft(parent);
            } else if (node == parent->right && parent == grandparent->left) {
                rotateLeft(parent);
                rotateRight(grandparent);
            } else {
                rotateRight(parent);
                rotateLeft(grandparent);
            }
        }

        root_ = node;
        update(root_);
    }

    Node* findNode(const T& key) {
        last_ = nullptr;
        Node* node = root_;

        while (node != nullptr) {
            last_ = node;

            if (compare_(key, node->key)) {
                node = node->left;
            } else if (compare_(node->key, key)) {
                node = node->right;
            } else {
                return node;
            }
        }

        return nullptr;
    }

    static void collect(const Node* node, std::vector<T>& result) {
        if (node == nullptr) return;
        collect(node->left, result);
        result.push_back(node->key);
        collect(node->right, result);
    }

    static void destroy(Node* node) {
        if (node == nullptr) return;
        destroy(node->left);
        destroy(node->right);
        delete node;
    }
};

#endif
