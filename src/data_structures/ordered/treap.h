#ifndef DSA_TREAP_H
#define DSA_TREAP_H

#include <cstdint>
#include <functional>
#include <memory>
#include <optional>
#include <random>
#include <stdexcept>
#include <utility>
#include <vector>

// ---------------------------------------------------------------------------
// Treap
//
// A treap is a binary search tree on the key and a min-heap on a random
// priority. The random priorities keep the expected height O(log n) without
// storing balance factors. Each node also stores its subtree size, which turns
// the treap into an order-statistic tree.
//
// Expected: O(log n) insert / erase / find / rank / kth.
// ---------------------------------------------------------------------------
template <typename Key, typename Value, typename Compare = std::less<Key>>
class Treap {
public:
    explicit Treap(Compare compare = Compare())
        : compare_(std::move(compare)), random_(0x9E3779B9U) {}

    Treap(const Treap&) = delete;
    Treap& operator=(const Treap&) = delete;

    bool insert(const Key& key, const Value& value) {
        bool inserted = false;
        root_ = insert(std::move(root_), key, value, inserted);
        return inserted;
    }

    bool erase(const Key& key) {
        bool erased = false;
        root_ = erase(std::move(root_), key, erased);
        return erased;
    }

    bool contains(const Key& key) const {
        return findNode(root_.get(), key) != nullptr;
    }

    Value* findValue(const Key& key) {
        Node* node = findNode(root_.get(), key);
        return node == nullptr ? nullptr : &node->value;
    }

    const Value* findValue(const Key& key) const {
        const Node* node = findNode(root_.get(), key);
        return node == nullptr ? nullptr : &node->value;
    }

    std::size_t size() const { return sizeOf(root_); }
    bool empty() const { return root_ == nullptr; }
    void clear() { root_.reset(); }

    const Key& minimum() const {
        if (empty()) throw std::out_of_range("Treap: empty");
        const Node* node = root_.get();
        while (node->left) node = node->left.get();
        return node->key;
    }

    const Key& maximum() const {
        if (empty()) throw std::out_of_range("Treap: empty");
        const Node* node = root_.get();
        while (node->right) node = node->right.get();
        return node->key;
    }

    // 0-based order statistic.
    const Key& kth(std::size_t index) const {
        if (index >= size()) throw std::out_of_range("Treap: kth");

        const Node* node = root_.get();
        while (node != nullptr) {
            std::size_t leftSize = sizeOf(node->left);

            if (index < leftSize) {
                node = node->left.get();
            } else if (index == leftSize) {
                return node->key;
            } else {
                index -= leftSize + 1;
                node = node->right.get();
            }
        }

        throw std::out_of_range("Treap: kth");
    }

    // Number of keys strictly less than `key`.
    std::size_t rank(const Key& key) const {
        std::size_t result = 0;
        const Node* node = root_.get();

        while (node != nullptr) {
            if (compare_(node->key, key)) {
                result += sizeOf(node->left) + 1;
                node = node->right.get();
            } else {
                node = node->left.get();
            }
        }

        return result;
    }

    std::optional<Key> lowerBound(const Key& key) const {
        const Node* result = nullptr;
        const Node* node = root_.get();

        while (node != nullptr) {
            if (!compare_(node->key, key)) {
                result = node;
                node = node->left.get();
            } else {
                node = node->right.get();
            }
        }

        if (result == nullptr) return std::nullopt;
        return result->key;
    }

    std::optional<Key> upperBound(const Key& key) const {
        const Node* result = nullptr;
        const Node* node = root_.get();

        while (node != nullptr) {
            if (compare_(key, node->key)) {
                result = node;
                node = node->left.get();
            } else {
                node = node->right.get();
            }
        }

        if (result == nullptr) return std::nullopt;
        return result->key;
    }

    std::vector<Key> keys() const {
        std::vector<Key> result;
        result.reserve(size());
        collectKeys(root_.get(), result);
        return result;
    }

    std::vector<std::pair<Key, Value>> entries() const {
        std::vector<std::pair<Key, Value>> result;
        result.reserve(size());
        collectEntries(root_.get(), result);
        return result;
    }

private:
    struct Node {
        Key key;
        Value value;
        std::uint32_t priority;
        std::size_t subtreeSize = 1;
        std::unique_ptr<Node> left;
        std::unique_ptr<Node> right;

        Node(const Key& k, const Value& v, std::uint32_t p)
            : key(k), value(v), priority(p) {}
    };

    Compare compare_;
    std::mt19937 random_;
    std::unique_ptr<Node> root_;

    static std::size_t sizeOf(const std::unique_ptr<Node>& node) {
        return node == nullptr ? 0 : node->subtreeSize;
    }

    static std::size_t sizeOf(const Node* node) {
        return node == nullptr ? 0 : node->subtreeSize;
    }

    static void update(Node* node) {
        if (node != nullptr) {
            node->subtreeSize = 1 + sizeOf(node->left) + sizeOf(node->right);
        }
    }

    static std::unique_ptr<Node> rotateRight(std::unique_ptr<Node> root) {
        std::unique_ptr<Node> newRoot = std::move(root->left);
        root->left = std::move(newRoot->right);
        update(root.get());
        newRoot->right = std::move(root);
        update(newRoot.get());
        return newRoot;
    }

    static std::unique_ptr<Node> rotateLeft(std::unique_ptr<Node> root) {
        std::unique_ptr<Node> newRoot = std::move(root->right);
        root->right = std::move(newRoot->left);
        update(root.get());
        newRoot->left = std::move(root);
        update(newRoot.get());
        return newRoot;
    }

    std::unique_ptr<Node> insert(std::unique_ptr<Node> node, const Key& key,
                                 const Value& value, bool& inserted) {
        if (node == nullptr) {
            inserted = true;
            return std::make_unique<Node>(key, value,
                                          static_cast<std::uint32_t>(random_()));
        }

        if (compare_(key, node->key)) {
            node->left = insert(std::move(node->left), key, value, inserted);
            if (node->left->priority < node->priority) {
                node = rotateRight(std::move(node));
            }
        } else if (compare_(node->key, key)) {
            node->right = insert(std::move(node->right), key, value, inserted);
            if (node->right->priority < node->priority) {
                node = rotateLeft(std::move(node));
            }
        } else {
            node->value = value;
            inserted = false;
        }

        update(node.get());
        return node;
    }

    std::unique_ptr<Node> erase(std::unique_ptr<Node> node, const Key& key,
                                bool& erased) {
        if (node == nullptr) return node;

        if (compare_(key, node->key)) {
            node->left = erase(std::move(node->left), key, erased);
        } else if (compare_(node->key, key)) {
            node->right = erase(std::move(node->right), key, erased);
        } else {
            erased = true;

            if (node->left == nullptr) return std::move(node->right);
            if (node->right == nullptr) return std::move(node->left);

            if (node->left->priority < node->right->priority) {
                node = rotateRight(std::move(node));
                node->right = erase(std::move(node->right), key, erased);
            } else {
                node = rotateLeft(std::move(node));
                node->left = erase(std::move(node->left), key, erased);
            }
        }

        update(node.get());
        return node;
    }

    Node* findNode(Node* node, const Key& key) const {
        while (node != nullptr) {
            if (compare_(key, node->key)) {
                node = node->left.get();
            } else if (compare_(node->key, key)) {
                node = node->right.get();
            } else {
                return node;
            }
        }
        return nullptr;
    }

    static void collectKeys(const Node* node, std::vector<Key>& result) {
        if (node == nullptr) return;
        collectKeys(node->left.get(), result);
        result.push_back(node->key);
        collectKeys(node->right.get(), result);
    }

    static void collectEntries(const Node* node,
                               std::vector<std::pair<Key, Value>>& result) {
        if (node == nullptr) return;
        collectEntries(node->left.get(), result);
        result.push_back({node->key, node->value});
        collectEntries(node->right.get(), result);
    }
};

#endif
