#ifndef DSA_PAIRING_HEAP_H
#define DSA_PAIRING_HEAP_H

#include <cstddef>
#include <functional>
#include <stdexcept>
#include <utility>
#include <vector>

// ---------------------------------------------------------------------------
// Pairing heap
//
// A meldable heap represented as a tree with left-child / next-sibling links.
// extractMin pairs the root's children, melds each pair, then melds the results
// from right to left.
//
// insert / meld: O(1)
// findMin: O(1)
// extractMin: O(log n) amortised
// ---------------------------------------------------------------------------
template <typename T, typename Compare = std::less<T>>
class PairingHeap {
public:
    PairingHeap() = default;
    explicit PairingHeap(Compare compare) : compare_(std::move(compare)) {}

    PairingHeap(const PairingHeap&) = delete;
    PairingHeap& operator=(const PairingHeap&) = delete;

    ~PairingHeap() { destroy(root_); }

    bool empty() const { return root_ == nullptr; }
    std::size_t size() const { return size_; }

    const T& minimum() const {
        if (root_ == nullptr) throw std::out_of_range("PairingHeap: empty");
        return root_->key;
    }

    void insert(const T& value) {
        Node* node = new Node(value);
        root_ = meld(root_, node);
        ++size_;
    }

    T extractMin() {
        if (root_ == nullptr) throw std::out_of_range("PairingHeap: empty");

        Node* oldRoot = root_;
        std::vector<Node*> children = detachChildren(oldRoot);

        std::vector<Node*> paired;
        paired.reserve((children.size() + 1) / 2);

        for (std::size_t i = 0; i < children.size(); i += 2) {
            if (i + 1 < children.size()) {
                paired.push_back(meld(children[i], children[i + 1]));
            } else {
                paired.push_back(children[i]);
            }
        }

        Node* result = nullptr;
        for (std::size_t i = paired.size(); i > 0; --i) {
            result = meld(result, paired[i - 1]);
        }

        root_ = result;
        T value = oldRoot->key;
        delete oldRoot;
        --size_;
        return value;
    }

private:
    struct Node {
        T key;
        Node* child = nullptr;
        Node* sibling = nullptr;
        Node* previous = nullptr;

        explicit Node(const T& value) : key(value) {}
    };

    Compare compare_;
    Node* root_ = nullptr;
    std::size_t size_ = 0;

    Node* meld(Node* a, Node* b) {
        if (a == nullptr) return b;
        if (b == nullptr) return a;

        if (compare_(b->key, a->key)) std::swap(a, b);

        b->previous = a;
        b->sibling = a->child;
        if (a->child != nullptr) a->child->previous = b;
        a->child = b;
        return a;
    }

    static std::vector<Node*> detachChildren(Node* node) {
        std::vector<Node*> children;
        Node* current = node->child;

        while (current != nullptr) {
            Node* next = current->sibling;
            current->sibling = nullptr;
            current->previous = nullptr;
            children.push_back(current);
            current = next;
        }

        node->child = nullptr;
        return children;
    }

    static void destroy(Node* node) {
        if (node == nullptr) return;
        destroy(node->child);
        destroy(node->sibling);
        delete node;
    }
};

#endif
