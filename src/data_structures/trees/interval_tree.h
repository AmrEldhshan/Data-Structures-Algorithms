#ifndef INTERVAL_TREE_H
#define INTERVAL_TREE_H

#include <iostream>
#include <vector>
#include <stdexcept>
#include <algorithm>

template <typename T>
struct Interval {
    T low, high;
    Interval(T l = T(), T h = T()) : low(l), high(h) {}

    bool overlaps(const Interval& other) const {
        return !(high < other.low || other.high < low);
    }
};

template <typename T>
class IntervalTree {
private:
    struct Node {
        Interval<T> interval;
        T maxHigh;
        int height;

        Node* left;
        Node* right;

        Node(const Interval<T>& i)
            : interval(i),
              maxHigh(i.high),
              height(1),
              left(nullptr),
              right(nullptr) {}
    };

    Node* root = nullptr;

public:
    IntervalTree() = default;
    ~IntervalTree() { clear(); }

    IntervalTree(const IntervalTree&) = delete;
    IntervalTree& operator=(const IntervalTree&) = delete;

    // Insert interval
    void insert(const Interval<T>& i) {
        root = insertRec(root, i);
    }

    // Remove interval
    void remove(const Interval<T>& i) {
        root = removeRec(root, i);
    }

    // Search for ANY overlap (returns nullptr if none)
    const Interval<T>* search(const Interval<T>& target) const {
        Node* x = root;
        while (x) {
            if (x->interval.overlaps(target))
                return &x->interval;

            if (x->left && x->left->maxHigh >= target.low)
                x = x->left;
            else
                x = x->right;
        }
        return nullptr;
    }

    // Search for ALL overlapping intervals
    std::vector<Interval<T>> searchAll(const Interval<T>& target) const {
        std::vector<Interval<T>> result;
        searchAllRec(root, target, result);
        return result;
    }

    // Clear all nodes
    void clear() {
        clearRec(root);
        root = nullptr;
    }

    void print() const {
        printRec(root, 0);
    }

private:

    // AVL utilities
    int height(Node* n) const { return n ? n->height : 0; }

    int balanceFactor(Node* n) const {
        return n ? height(n->left) - height(n->right) : 0;
    }

    void update(Node* n) {
        if (!n) return;
        n->height = 1 + std::max(height(n->left), height(n->right));

        T leftMax = n->left ? n->left->maxHigh : std::numeric_limits<T>::min();
        T rightMax = n->right ? n->right->maxHigh : std::numeric_limits<T>::min();

        n->maxHigh = std::max({ n->interval.high, leftMax, rightMax });
    }

    Node* rotateRight(Node* y) {
        Node* x = y->left;
        Node* t2 = x->right;

        x->right = y;
        y->left = t2;

        update(y);
        update(x);

        return x;
    }

    Node* rotateLeft(Node* x) {
        Node* y = x->right;
        Node* t2 = y->left;

        y->left = x;
        x->right = t2;

        update(x);
        update(y);

        return y;
    }

    Node* balance(Node* n) {
        if (!n) return n;

        update(n);

        int bf = balanceFactor(n);

        // Left heavy
        if (bf > 1) {
            if (balanceFactor(n->left) < 0)
                n->left = rotateLeft(n->left);
            return rotateRight(n);
        }

        // Right heavy
        if (bf < -1) {
            if (balanceFactor(n->right) > 0)
                n->right = rotateRight(n->right);
            return rotateLeft(n);
        }

        return n;
    }

    Node* insertRec(Node* node, const Interval<T>& itv) {
        if (!node) return new Node(itv);

        if (itv.low < node->interval.low)
            node->left = insertRec(node->left, itv);
        else
            node->right = insertRec(node->right, itv);

        return balance(node);
    }

    Node* minNode(Node* n) {
        while (n && n->left) n = n->left;
        return n;
    }

    Node* removeRec(Node* node, const Interval<T>& itv) {
        if (!node) return nullptr;

        if (itv.low < node->interval.low)
            node->left = removeRec(node->left, itv);
        else if (itv.low > node->interval.low)
            node->right = removeRec(node->right, itv);
        else {
            // match found
            if (!node->left || !node->right) {
                Node* tmp = node->left ? node->left : node->right;
                delete node;
                return tmp;
            }

            Node* succ = minNode(node->right);
            node->interval = succ->interval;
            node->right = removeRec(node->right, succ->interval);
        }

        return balance(node);
    }

    void searchAllRec(Node* node, const Interval<T>& target,
                      std::vector<Interval<T>>& out) const {

        if (!node) return;

        if (node->interval.overlaps(target))
            out.push_back(node->interval);

        if (node->left && node->left->maxHigh >= target.low)
            searchAllRec(node->left, target, out);

        if (node->right && node->interval.low <= target.high)
            searchAllRec(node->right, target, out);
    }

    void clearRec(Node* n) {
        if (!n) return;
        clearRec(n->left);
        clearRec(n->right);
        delete n;
    }

    void printRec(Node* n, int depth) const {
        if (!n) return;
        printRec(n->right, depth + 1);
        std::cout << std::string(depth * 4, ' ')
                  << "[" << n->interval.low << ", " << n->interval.high
                  << "] (max=" << n->maxHigh << ")\n";
        printRec(n->left, depth + 1);
    }
};

#endif // INTERVAL_TREE_H
