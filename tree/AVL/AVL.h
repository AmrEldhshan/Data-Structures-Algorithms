#ifndef AVL_H
#define AVL_H

#include <iostream>
using namespace std;

// Template class representing a node in the AVL tree
template <class T>
class AVLNode {
public:
    T value;                     // The value stored in the node
    AVLNode* leftChild;         // Pointer to the left child
    AVLNode* rightChild;        // Pointer to the right child
    int height;                 // Height of the node in the tree

    AVLNode(const T& val)
        : value(val), leftChild(nullptr), rightChild(nullptr), height(1) {}
};

// Template class representing the AVL tree itself
template <class T>
class AVL {
private:
    AVLNode<T>* root; // Root pointer for the AVL tree

    // Utility function to get the height of a node
    int getHeight(AVLNode<T>* node) {
        return node ? node->height : 0;
    }

    // Calculates the balance factor of a node
    int getBalanceFactor(AVLNode<T>* node) {
        return node ? getHeight(node->leftChild) - getHeight(node->rightChild) : 0;
    }

    // Right rotate the subtree rooted with unbalancedNode (LL case)
    AVLNode<T>* rotateRight(AVLNode<T>* unbalancedNode) {
        AVLNode<T>* newRoot = unbalancedNode->leftChild;
        AVLNode<T>* transferSubtree = newRoot->rightChild;

        // Perform rotation
        newRoot->rightChild = unbalancedNode;
        unbalancedNode->leftChild = transferSubtree;

        // Update heights after rotation
        unbalancedNode->height = 1 + max(getHeight(unbalancedNode->leftChild), getHeight(unbalancedNode->rightChild));
        newRoot->height = 1 + max(getHeight(newRoot->leftChild), getHeight(newRoot->rightChild));

        return newRoot;
    }

    // Left rotate the subtree rooted with unbalancedNode (RR case)
    AVLNode<T>* rotateLeft(AVLNode<T>* unbalancedNode) {
        AVLNode<T>* newRoot = unbalancedNode->rightChild;
        AVLNode<T>* transferSubtree = newRoot->leftChild;

        // Perform rotation
        newRoot->leftChild = unbalancedNode;
        unbalancedNode->rightChild = transferSubtree;

        // Update heights after rotation
        unbalancedNode->height = 1 + max(getHeight(unbalancedNode->leftChild), getHeight(unbalancedNode->rightChild));
        newRoot->height = 1 + max(getHeight(newRoot->leftChild), getHeight(newRoot->rightChild));

        return newRoot;
    }

    // Balances the subtree rooted at the given node
    AVLNode<T>* balance(AVLNode<T>* node) {
        if (!node) return node;

        // Update the height of the node
        node->height = 1 + max(getHeight(node->leftChild), getHeight(node->rightChild));

        // Get balance factor to check for imbalance
        int balanceFactor = getBalanceFactor(node);

        // Perform appropriate rotation based on imbalance type

        // Left Heavy
        if (balanceFactor > 1) { // left issue -> left is too long
            if (getBalanceFactor(node->leftChild) >= 0) {
                //   Left-Left Case
                return rotateRight(node);
            } else {
                // Left-Right Case
                node->leftChild = rotateLeft(node->leftChild);
                return rotateRight(node);
            }
        }

        // Right Heavy
        if (balanceFactor < -1) {
            if (getBalanceFactor(node->rightChild) <= 0) {
                // Right-Right Case
                return rotateLeft(node);
            } else {
                // Right-Left Case
                node->rightChild = rotateRight(node->rightChild);
                return rotateLeft(node);
            }
        }

        // Already balanced
        return node;
    }

    // Recursive function to insert a value and balance the subtree
    AVLNode<T>* insertRecursive(AVLNode<T>* currentNode, const T& key) {
        // Standard BST insertion
        if (!currentNode)
            return new AVLNode<T>(key);

        if (key < currentNode->value)
            currentNode->leftChild = insertRecursive(currentNode->leftChild, key);
        else if (key > currentNode->value)
            currentNode->rightChild = insertRecursive(currentNode->rightChild, key);
        else
            return currentNode; // Duplicate keys not allowed

        // Balance the node after insertion
        return balance(currentNode);
    }

    // Inorder traversal for displaying values
    void inorderTraversal(AVLNode<T>* node) const {
        if (node) {
            inorderTraversal(node->leftChild);
            cout << node->value << " ";
            inorderTraversal(node->rightChild);
        }
    }

    // Delete all nodes in the tree (postorder deletion)
    void deleteTree(AVLNode<T>* node) {
        if (node) {
            deleteTree(node->leftChild);
            deleteTree(node->rightChild);
            delete node;
        }
    }

public:
    // Constructor initializes empty tree
    AVL() : root(nullptr) {}

    // Destructor deletes entire tree
    ~AVL() {
        deleteTree(root);
    }

    // Public insert function
    void insert(const T& key) {
        root = insertRecursive(root, key);
    }

    // Display values in sorted order
    void displayInorder() const {
        inorderTraversal(root);
        cout << endl;
    }

    // Search function to check if a key exists
    bool search(const T& key) const {
        AVLNode<T>* currentNode = root;
        while (currentNode) {
            if (key == currentNode->value)
                return true;
            else if (key < currentNode->value)
                currentNode = currentNode->leftChild;
            else
                currentNode = currentNode->rightChild;
        }
        return false;
    }
};

#endif // AVL_H
