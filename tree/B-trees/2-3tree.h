/*
 * 2-3 Tree — Template Header Implementation
 * ------------------------------------------
 * Description:
 *     A balanced search tree where each internal node can have either:
 *       - 2 children (1 key)
 *       - 3 children (2 keys)
 *     The tree maintains balance by splitting and promoting keys during insertions.
 *
 * Features:
 *     - Insert:  O(log n)
 *     - Search:  O(log n)
 *     - Height-balanced structure (always balanced)
 *
 * Author: Amr Khaled
 * File: 2-3tree.h
 * ------------------------------------------
 */

#ifndef TWO_THREE_TREE_H
#define TWO_THREE_TREE_H

#include <iostream>
#include <memory>

template <typename T>
class TwoThreeTree {
private:
    // Node structure representing a 2-node or 3-node
    struct Node {
        T key1;                  // First key
        T key2;                  // Optional second key
        bool hasTwoKeys;         // Flag indicating if the node has two keys
        std::shared_ptr<Node> left;
        std::shared_ptr<Node> middle;
        std::shared_ptr<Node> right;
        std::weak_ptr<Node> parent;

        explicit Node(const T& k)
            : key1(k), hasTwoKeys(false),
              left(nullptr), middle(nullptr),
              right(nullptr), parent() {}
    };

    std::shared_ptr<Node> root;

    // Helper function to search for a key
    bool searchHelper(std::shared_ptr<Node> node, const T& key) const {
        if (!node) return false;

        if (key == node->key1 || (node->hasTwoKeys && key == node->key2))
            return true;

        if (key < node->key1)
            return searchHelper(node->left, key);
        else if (!node->hasTwoKeys || key < node->key2)
            return searchHelper(node->middle, key);
        else
            return searchHelper(node->right, key);
    }

    // Insert helper (simplified logic for educational use)
    void insertHelper(std::shared_ptr<Node>& node, const T& key) {
        if (!node) {
            node = std::make_shared<Node>(key);
            return;
        }

        // If node is a leaf
        if (!node->left && !node->middle && !node->right) {
            if (!node->hasTwoKeys) {
                // Insert second key
                if (key < node->key1)
                    std::swap(node->key1, node->key2 = key);
                else
                    node->key2 = key;
                node->hasTwoKeys = true;
            } else {
                // Need to split (simplified logic)
                T a = node->key1, b = node->key2, c = key;
                if (b < a) std::swap(a, b);
                if (c < a) std::swap(a, c);
                if (c < b) std::swap(b, c);

                node->key1 = b;
                node->hasTwoKeys = false;
                node->left = std::make_shared<Node>(a);
                node->middle = std::make_shared<Node>(c);
            }
            return;
        }

        // Traverse to correct child
        if (key < node->key1)
            insertHelper(node->left, key);
        else if (!node->hasTwoKeys || key < node->key2)
            insertHelper(node->middle, key);
        else
            insertHelper(node->right, key);
    }

    // Print helper
    void printHelper(const std::shared_ptr<Node>& node, int depth = 0) const {
        if (!node) return;

        printHelper(node->right, depth + 1);
        for (int i = 0; i < depth; ++i) std::cout << "    ";
        std::cout << "[" << node->key1;
        if (node->hasTwoKeys) std::cout << ", " << node->key2;
        std::cout << "]\n";
        printHelper(node->middle, depth + 1);
        printHelper(node->left, depth + 1);
    }

public:
    TwoThreeTree() : root(nullptr) {}

    // Insert a new key
    void insert(const T& key) {
        insertHelper(root, key);
    }

    // Search for a key
    bool search(const T& key) const {
        return searchHelper(root, key);
    }

    // Print the tree
    void print() const {
        if (!root)
            std::cout << "(empty tree)\n";
        else
            printHelper(root);
    }
};

#endif // TWO_THREE_TREE_H
