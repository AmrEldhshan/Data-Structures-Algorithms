#ifndef BSTNODE_H
#define BSTNODE_H

#include <queue>
#include <iostream>
#include <memory>

using namespace std;

// Node class for BST
template <class T>
class BSTNode {
private:
    T key;
    BSTNode* left, * right;

public:
    // Default constructor
    BSTNode() {
        left = right = nullptr;
    }

    // Parameterized constructor
    BSTNode(const T& el, BSTNode* l = nullptr, BSTNode* r = nullptr) {
        key = el;
        left = l;
        right = r;
    }

    // Virtual destructor
    virtual ~BSTNode() = default;

    // Getters
    BSTNode* getLeft() const {
        return left;
    }

    BSTNode* getRight() const {
        return right;
    }

    const T& getKey() const {
        return key;
    }

    T& getKey() {
        return key;
    }

    // Setters
    void setLeft(BSTNode* node) {
        left = node;
    }

    void setRight(BSTNode* node) {
        right = node;
    }
};

// Binary Search Tree class
template <class T>
class BST {
protected:
    BSTNode<T>* root;

public:
    BST() : root(nullptr) {}

    // Virtual destructor
    virtual ~BST() {
        clear();
    }

    void clear() {
        clear(root);
        root = nullptr;
    }

    bool isEmpty() const {
        return root == nullptr;
    }

    const T* search(const T& el) const {
        BSTNode<T>* p = root;
        while (p != nullptr) {
            if (el == p->getKey()) {
                return &(p->getKey());
            }
            else if (el < p->getKey()) {
                p = p->getLeft();
            }
            else {
                p = p->getRight();
            }
        }
        return nullptr;
    }

    void insert(const T& el) {
        BSTNode<T>* newNode = new BSTNode<T>(el);
        if (root == nullptr) {
            root = newNode;
            return;
        }

        BSTNode<T>* parent = nullptr;
        BSTNode<T>* current = root;

        while (current != nullptr) {
            parent = current;
            if (el < current->getKey()) {
                current = current->getLeft();
            }
            else {
                current = current->getRight();
            }
        }

        if (el < parent->getKey()) {
            parent->setLeft(newNode);
        }
        else {
            parent->setRight(newNode);
        }
    }

    void breadthFirst() {
        if (root == nullptr) return;

        std::queue<BSTNode<T>*> queue;
        queue.push(root);

        while (!queue.empty()) {
            BSTNode<T>* p = queue.front();
            queue.pop();

            visit(p);

            if (p->getLeft() != nullptr) {
                queue.push(p->getLeft());
            }

            if (p->getRight() != nullptr) {
                queue.push(p->getRight());
            }
        }
    }

    void deleteNode(BSTNode<T>*& node) {
    if (node == nullptr) return;

    if (node->getLeft() == nullptr && node->getRight() == nullptr) {
        // No children
        delete node;
        node = nullptr;
    }
    else if (node->getLeft() != nullptr && node->getRight() == nullptr) {
        // Only left child
        BSTNode<T>* temp = node->getLeft();
        delete node;
        node = temp;
    }
    else if (node->getLeft() == nullptr && node->getRight() != nullptr) {
        // Only right child
        BSTNode<T>* temp = node->getRight();
        delete node;
        node = temp;
    }
    else {
        // Node has two children, find predecessor (max in left subtree)
        BSTNode<T>* predParent = node;
        BSTNode<T>* pred = node->getLeft();

        // Move to rightmost child in left subtree
        while (pred->getRight() != nullptr) {
            predParent = pred;
            pred = pred->getRight();
        }

        // Copy predecessor's key to current node
        node->getKey() = pred->getKey();

        // Delete the predecessor node
        if (predParent == node) {
            // Predecessor is direct left child
            predParent->setLeft(pred->getLeft());
        }
        else {
            // Predecessor is deeper in left subtree
            predParent->setRight(pred->getLeft());
        }

        delete pred;
    }
}

    // Public wrapper methods for tree traversals
    void inorder() {
        inorderTraversal(root);
    }

    void preorder() {
        preorderTraversal(root);
    }

    void postorder() {
        postorderTraversal(root);
    }

private:
    void clear(BSTNode<T>* node) {
        if (node != nullptr) {
            clear(node->getLeft());
            clear(node->getRight());
            delete node;
        }
    }

    void visit(BSTNode<T>* node) const {
        cout << node->getKey() << " ";
    }

    T predecessor(BSTNode<T>* node) {
        if (node == nullptr) return T();

        BSTNode<T>* current = node->getLeft();
        while (current && current->getRight() != nullptr) {
            current = current->getRight();
        }
        return current ? current->getKey() : T();
    }

    T successor(BSTNode<T>* node) {
        if (node == nullptr) return T();

        BSTNode<T>* current = node->getRight();
        while (current && current->getLeft() != nullptr) {
            current = current->getLeft();
        }
        return current ? current->getKey() : T();
    }

    // Private implementation of traversals
    void inorderTraversal(BSTNode<T>* p) { // LVR
        if (p != nullptr) {
            inorderTraversal(p->getLeft());
            visit(p);
            inorderTraversal(p->getRight());
        }
    }

    void preorderTraversal(BSTNode<T>* p) { // VLR
        if (p != nullptr) {
            visit(p);
            preorderTraversal(p->getLeft());
            preorderTraversal(p->getRight());
        }
    }

    void postorderTraversal(BSTNode<T>* p) { // LRV
        if (p != nullptr) {
            postorderTraversal(p->getLeft());
            postorderTraversal(p->getRight());
            visit(p);
        }
    }
};

#endif // BSTNODE_H
