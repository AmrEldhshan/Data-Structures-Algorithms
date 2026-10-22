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

        newRoot->rightChild = unbalancedNode;
        unbalancedNode->leftChild = transferSubtree;

        unbalancedNode->height = 1 + max(getHeight(unbalancedNode->leftChild), getHeight(unbalancedNode->rightChild));
        newRoot->height = 1 + max(getHeight(newRoot->leftChild), getHeight(newRoot->rightChild));

        return newRoot;
    }

    // Left rotate the subtree rooted with unbalancedNode (RR case)
    AVLNode<T>* rotateLeft(AVLNode<T>* unbalancedNode) {
        AVLNode<T>* newRoot = unbalancedNode->rightChild;
        AVLNode<T>* transferSubtree = newRoot->leftChild;

        newRoot->leftChild = unbalancedNode;
        unbalancedNode->rightChild = transferSubtree;

        unbalancedNode->height = 1 + max(getHeight(unbalancedNode->leftChild), getHeight(unbalancedNode->rightChild));
        newRoot->height = 1 + max(getHeight(newRoot->leftChild), getHeight(newRoot->rightChild));

        return newRoot;
    }

    // Balances the subtree rooted at the given node
    AVLNode<T>* balance(AVLNode<T>* node) {
        if (!node) return node;

        node->height = 1 + max(getHeight(node->leftChild), getHeight(node->rightChild));
        int balanceFactor = getBalanceFactor(node);

        // Left heavy
        if (balanceFactor > 1) {
            if (getBalanceFactor(node->leftChild) >= 0) {
                return rotateRight(node); // Left-Left
            } else {
                node->leftChild = rotateLeft(node->leftChild); // Left-Right
                return rotateRight(node);
            }
        }

        // Right heavy
        if (balanceFactor < -1) {
            if (getBalanceFactor(node->rightChild) <= 0) {
                return rotateLeft(node); // Right-Right
            } else {
                node->rightChild = rotateRight(node->rightChild); // Right-Left
                return rotateLeft(node);
            }
        }

        return node; // Balanced
    }

    // Recursive function to insert a value
    AVLNode<T>* insertRecursive(AVLNode<T>* currentNode, const T& key) {
        if (!currentNode)
            return new AVLNode<T>(key);

        if (key < currentNode->value)
            currentNode->leftChild = insertRecursive(currentNode->leftChild, key);
        else if (key > currentNode->value)
            currentNode->rightChild = insertRecursive(currentNode->rightChild, key);
        else
            return currentNode; // Duplicate keys not allowed

        return balance(currentNode);
    }

    // Find node with minimum value (used in delete)
    AVLNode<T>* minValueNode(AVLNode<T>* node) {
        AVLNode<T>* current = node;
        while (current->leftChild)
            current = current->leftChild;
        return current;
    }

    // Recursive function to delete a node
    AVLNode<T>* deleteRecursive(AVLNode<T>* node, const T& key) {
        if (!node)
            return node;

        if (key < node->value) {
            node->leftChild = deleteRecursive(node->leftChild, key);
        } else if (key > node->value) {
            node->rightChild = deleteRecursive(node->rightChild, key);
        } else {
            // Node with 0 or 1 child
            if (!node->leftChild || !node->rightChild) {
                AVLNode<T>* temp = node->leftChild ? node->leftChild : node->rightChild;

                if (!temp) {
                    temp = node;
                    node = nullptr;
                } else {
                    *node = *temp;
                }
                delete temp;
            } else {
                // Node with 2 children
                AVLNode<T>* temp = minValueNode(node->rightChild);
                node->value = temp->value;
                node->rightChild = deleteRecursive(node->rightChild, temp->value);
            }
        }

        if (!node)
            return node;

        node->height = 1 + max(getHeight(node->leftChild), getHeight(node->rightChild));
        return balance(node);
    }

    // Inorder traversal for display
    void inorderTraversal(AVLNode<T>* node) const {
        if (node) {
            inorderTraversal(node->leftChild);
            cout << node->value << " ";
            inorderTraversal(node->rightChild);
        }
    }

    // Delete the entire tree (postorder)
    void deleteTree(AVLNode<T>* node) {
        if (node) {
            deleteTree(node->leftChild);
            deleteTree(node->rightChild);
            delete node;
        }
    }

public:
    AVL() : root(nullptr) {}
    ~AVL() {
        deleteTree(root);
    }

    // Public insert function
    void insert(const T& key) {
        root = insertRecursive(root, key);
    }

    // Public delete function
    void deleteNode(const T& key) {
        root = deleteRecursive(root, key);
    }

    // Display sorted values
    void displayInorder() const {
        inorderTraversal(root);
        cout << endl;
    }

    // Search key existence
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
