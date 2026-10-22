#ifndef SEPARATE_CHAINING_VARIANTS_H
#define SEPARATE_CHAINING_VARIANTS_H

#include <iostream>
#include <algorithm>
using namespace std;

/*
=====================================================================
Separate Chaining Variants (Open Hashing)
=====================================================================
Concept:
    When two keys hash to the same index (collision), we store them
    in a data structure (Linked List, BST, AVL) located at that index.

Hash Function:
    h(key) = key % table_size

Goal:
    Compare different internal structures for handling collisions:
    1. Linked List
    2. Binary Search Tree (BST)
    3. AVL Tree (Self-Balancing BST)
=====================================================================
*/


// =================================================================
// 1️⃣ Linked List Implementation
// =================================================================
class SeparateChaining_LinkedList {
private:
    struct Node {
        int key;
        Node* next;
        explicit Node(int k) : key(k), next(nullptr) {}
    };

    int table_size;
    Node** table;

    int hash(int key) const {
        return key % table_size;
    }

public:
    explicit SeparateChaining_LinkedList(int size) {
        table_size = size;
        table = new Node*[table_size];
        for (int i = 0; i < table_size; ++i)
            table[i] = nullptr;
    }

    ~SeparateChaining_LinkedList() {
        for (int i = 0; i < table_size; ++i) {
            Node* curr = table[i];
            while (curr) {
                Node* temp = curr;
                curr = curr->next;
                delete temp;
            }
        }
        delete[] table;
    }

    void insert(int key) {
        int index = hash(key);
        Node* newNode = new Node(key);
        newNode->next = table[index];
        table[index] = newNode;
        cout << "[LinkedList] Insert " << key << " -> Index " << index << endl;
    }

    bool search(int key) const {
        int index = hash(key);
        Node* curr = table[index];
        while (curr) {
            if (curr->key == key) return true;
            curr = curr->next;
        }
        return false;
    }

    void display() const {
        cout << "\n[Linked List Hash Table]\n";
        for (int i = 0; i < table_size; ++i) {
            cout << "[" << i << "] -> ";
            Node* curr = table[i];
            while (curr) {
                cout << curr->key << " -> ";
                curr = curr->next;
            }
            cout << "NULL\n";
        }
    }
};



// =================================================================
// 2️⃣ Binary Search Tree (BST) Implementation
// =================================================================
class SeparateChaining_BST {
private:
    struct Node {
        int key;
        Node* left;
        Node* right;
        explicit Node(int k) : key(k), left(nullptr), right(nullptr) {}
    };

    int table_size;
    Node** table;

    int hash(int key) const {
        return key % table_size;
    }

    Node* insertNode(Node* root, int key) {
        if (!root) return new Node(key);
        if (key < root->key)
            root->left = insertNode(root->left, key);
        else if (key > root->key)
            root->right = insertNode(root->right, key);
        return root;
    }

    bool searchNode(Node* root, int key) const {
        if (!root) return false;
        if (root->key == key) return true;
        if (key < root->key) return searchNode(root->left, key);
        else return searchNode(root->right, key);
    }

    void displayNode(Node* root) const {
        if (!root) return;
        displayNode(root->left);
        cout << root->key << " ";
        displayNode(root->right);
    }

    void freeTree(Node* root) {
        if (!root) return;
        freeTree(root->left);
        freeTree(root->right);
        delete root;
    }

public:
    explicit SeparateChaining_BST(int size) {
        table_size = size;
        table = new Node*[table_size];
        for (int i = 0; i < table_size; ++i)
            table[i] = nullptr;
    }

    ~SeparateChaining_BST() {
        for (int i = 0; i < table_size; ++i)
            freeTree(table[i]);
        delete[] table;
    }

    void insert(int key) {
        int index = hash(key);
        table[index] = insertNode(table[index], key);
        cout << "[BST] Insert " << key << " -> Index " << index << endl;
    }

    bool search(int key) const {
        int index = hash(key);
        return searchNode(table[index], key);
    }

    void display() const {
        cout << "\n[BST Hash Table]\n";
        for (int i = 0; i < table_size; ++i) {
            cout << "[" << i << "] -> ";
            displayNode(table[i]);
            cout << endl;
        }
    }
};



// =================================================================
// 3️⃣ AVL Tree Implementation
// =================================================================
class SeparateChaining_AVL {
private:
    struct Node {
        int key, height;
        Node* left;
        Node* right;
        explicit Node(int k) : key(k), height(1), left(nullptr), right(nullptr) {}
    };

    int table_size;
    Node** table;

    int hash(int key) const {
        return key % table_size;
    }

    int height(Node* n) { return n ? n->height : 0; }

    int getBalance(Node* n) {
        return n ? height(n->left) - height(n->right) : 0;
    }

    Node* rightRotate(Node* y) {
        Node* x = y->left;
        Node* T2 = x->right;
        x->right = y;
        y->left = T2;
        y->height = max(height(y->left), height(y->right)) + 1;
        x->height = max(height(x->left), height(x->right)) + 1;
        return x;
    }

    Node* leftRotate(Node* x) {
        Node* y = x->right;
        Node* T2 = y->left;
        y->left = x;
        x->right = T2;
        x->height = max(height(x->left), height(x->right)) + 1;
        y->height = max(height(y->left), height(y->right)) + 1;
        return y;
    }

    Node* insertNode(Node* node, int key) {
        if (!node) return new Node(key);
        if (key < node->key)
            node->left = insertNode(node->left, key);
        else if (key > node->key)
            node->right = insertNode(node->right, key);
        else
            return node; // no duplicates

        node->height = 1 + max(height(node->left), height(node->right));

        int balance = getBalance(node);

        // LL Case
        if (balance > 1 && key < node->left->key)
            return rightRotate(node);
        // RR Case
        if (balance < -1 && key > node->right->key)
            return leftRotate(node);
        // LR Case
        if (balance > 1 && key > node->left->key) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
        // RL Case
        if (balance < -1 && key < node->right->key) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }
        return node;
    }

    void inorder(Node* root) const {
        if (!root) return;
        inorder(root->left);
        cout << root->key << " ";
        inorder(root->right);
    }

    void freeTree(Node* root) {
        if (!root) return;
        freeTree(root->left);
        freeTree(root->right);
        delete root;
    }

public:
    explicit SeparateChaining_AVL(int size) {
        table_size = size;
        table = new Node*[table_size];
        for (int i = 0; i < table_size; ++i)
            table[i] = nullptr;
    }

    ~SeparateChaining_AVL() {
        for (int i = 0; i < table_size; ++i)
            freeTree(table[i]);
        delete[] table;
    }

    void insert(int key) {
        int index = hash(key);
        table[index] = insertNode(table[index], key);
        cout << "[AVL] Insert " << key << " -> Index " << index << endl;
    }

    bool search(int key) const {
        int index = hash(key);
        Node* curr = table[index];
        while (curr) {
            if (curr->key == key) return true;
            curr = (key < curr->key) ? curr->left : curr->right;
        }
        return false;
    }

    void display() const {
        cout << "\n[AVL Hash Table]\n";
        for (int i = 0; i < table_size; ++i) {
            cout << "[" << i << "] -> ";
            inorder(table[i]);
            cout << endl;
        }
    }
};




/*
=====================================================================
📊 Analysis of Separate Chaining using LinkedList, BST, and AVL Trees
---------------------------------------------------------------------
Definitions:
    n = total number of keys
    m = table size (number of hash buckets)
    α = load factor = n/m

---------------------------------------------------------------------
Best Case:
    Keys are uniformly distributed.
    Each bucket contains ~ n/m elements.
---------------------------------------------------------------------

Case 1 (Worst Case - BST):
    Keys come in sorted order → BST becomes skewed.
    Height = n/m
    Complexity: O(n/m) = O(n / table_size)

Case 2 (Balanced BST - Average Case):
    Keys are in random order (tree nearly balanced).
    Height ≈ log(n/m)
    Complexity: O(log(n/m))

Fix (AVL Tree):
    AVL is self-balancing:
        | height(left) - height(right) | ≤ 1
    Guarantees: height = O(log n)
    So all operations:
        Insert, Search, Delete = O(log n)

---------------------------------------------------------------------
Summary Table:
    Structure       | Best Case   | Worst Case   | Average Case
    ----------------|-------------|--------------|---------------
    Linked List     | O(1)        | O(n/m)       | O(1 + α)
    BST             | O(log(n/m)) | O(n/m)       | O(log(n/m))
    AVL             | O(log(n/m)) | O(log(n/m))  | O(log(n/m))
---------------------------------------------------------------------
=====================================================================
*/

#endif // SEPARATE_CHAINING_VARIANTS_H
