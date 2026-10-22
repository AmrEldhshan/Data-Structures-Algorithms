/*
 * Red-Black Tree — Template Implementation (Commented)
 * ---------------------------------------------------
 * This header is a fully working, header-only Red-Black Tree with
 * extensive inline comments explaining the core ideas, the
 * insertion cases (1/2/3) and deletion cases (1/2/3/4) so the
 * algorithm is easier to follow.
 *
 * Notes:
 *  - This implementation follows the CLRS notation (Introduction to Algorithms).
 *  - NULL leaves are represented by nullptr and conceptually BLACK.
 *  - insert() always inserts a RED node; fixInsertion() restores properties.
 *  - remove() does a standard BST delete and calls fixDeletion() if
 *    a BLACK node was removed (to restore black-height invariants).
 */

#ifndef REDBTREE_H
#define REDBTREE_H

#include <iostream>
using namespace std;

enum Color { RED, BLACK };

// Node structure
template <typename T>
struct RBNode {
    T key;            // stored value
    Color color;      // RED or BLACK
    RBNode *left, *right, *parent; // BST pointers

    RBNode(T k)
        : key(k), color(RED), left(nullptr), right(nullptr), parent(nullptr) {}
};

// Red-Black Tree class
template <typename T>
class RedBlackTree {
private:
    RBNode<T>* root;

    // Core operations
    void rotateLeft(RBNode<T>*&);
    void rotateRight(RBNode<T>*&);
    void fixInsertion(RBNode<T>*&);
    void fixDeletion(RBNode<T>*&);
    void transplant(RBNode<T>*, RBNode<T>*);
    RBNode<T>* minimum(RBNode<T>*) const;

    // Helpers
    void inorderHelper(RBNode<T>*) const;
    RBNode<T>* searchHelper(RBNode<T>*, T) const;
    void destroyTree(RBNode<T>*);

public:
    RedBlackTree();
    ~RedBlackTree();

    void insert(T);
    void remove(T);
    bool search(T) const;
    void inorder() const;
};


// ===============================================
// ============= IMPLEMENTATION ==================
// ===============================================

template <typename T>
RedBlackTree<T>::RedBlackTree() : root(nullptr) {}

template <typename T>
RedBlackTree<T>::~RedBlackTree() {
    destroyTree(root);
}

template <typename T>
void RedBlackTree<T>::destroyTree(RBNode<T>* node) {
    if (!node) return;
    destroyTree(node->left);
    destroyTree(node->right);
    delete node;
}

// ---------------- Rotations ----------------
// rotateLeft(x): assumes x is not null and x->right != null
// After rotation, y (x->right) takes x's position and x becomes y's left child.
// Rotations preserve the binary-search-tree property while changing shape.
template <typename T>
void RedBlackTree<T>::rotateLeft(RBNode<T>*& x) {
    RBNode<T>* y = x->right; // y will move up to x's position
    x->right = y->left;      // transfer y's left subtree to x->right
    if (y->left != nullptr){
        y->left->parent = x; // fix parent pointer
    }

    y->parent = x->parent;   // link y with x's parent

    if (x->parent == nullptr)
        root = y;            // x was root
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;

    y->left = x;             // finish rotation
    x->parent = y;
}

// rotateRight(x): mirror of rotateLeft
template <typename T>
void RedBlackTree<T>::rotateRight(RBNode<T>*& x) {
    RBNode<T>* y = x->left;  // y will move up to x's position
    x->left = y->right;      // transfer y's right subtree to x->left
    if (y->right != nullptr)
        y->right->parent = x;

    y->parent = x->parent;

    if (x->parent == nullptr)
        root = y;
    else if (x == x->parent->right)
        x->parent->right = y;
    else
        x->parent->left = y;

    y->right = x;
    x->parent = y;
}

// ---------------- Insert ----------------
// Standard BST insert followed by fixInsertion to maintain RB properties.
// Insertion always adds a RED node. fixInsertion resolves violations.
template <typename T>
void RedBlackTree<T>::insert(T key) {
    RBNode<T>* newNode = new RBNode<T>(key);
    RBNode<T>* y = nullptr;
    RBNode<T>* x = root;

    // BST insertion to find parent y for newNode
    while (x != nullptr) {
        y = x;
        if (newNode->key < x->key)
            x = x->left;
        else
            x = x->right;
    }

    newNode->parent = y;
    if (y == nullptr)
        root = newNode;          // tree was empty, new node is root
    else if (newNode->key < y->key)
        y->left = newNode;
    else
        y->right = newNode;

    // Fix Red-Black Tree properties. This may recolor/rotate up the tree.
    fixInsertion(newNode);
}

/*
 * fixInsertion(z) — restore RB properties after inserting z (which is RED)
 * ---------------------------------------------------------------------
 * While z's parent exists and is RED there is a red-red violation (a RED node
 * cannot have a RED child). We inspect z's uncle (parent's sibling) to decide
 * which case applies. CLRS defines three cases (we show both the "left-parent"
 * and mirror "right-parent" variants):
 *
 * Case 1 (recolor): parent and uncle are RED.
 *   - Action: color parent and uncle BLACK, color grandparent RED, and move z = grandparent
 *   - Effect: violation may have moved up; loop continues.
 *
 * Case 2 (rotation to convert to Case 3): parent is RED, uncle is BLACK (or nullptr),
 *   and z is the "inner" child (e.g., z is parent's right child when parent is left child of grandparent).
 *   - Action: rotate at parent (left if parent is left child of grandparent; right if parent is right child)
 *   - Effect: z becomes the outer child and we fall through to Case 3.
 *
 * Case 3 (rotation + recolor): parent is RED, uncle is BLACK (or nullptr),
 *   and z is the "outer" child.
 *   - Action: color parent BLACK, color grandparent RED, rotate at grandparent (right if parent was left, left if parent was right)
 *   - Effect: local subtree satisfies RB properties.
 */
template <typename T>
void RedBlackTree<T>::fixInsertion(RBNode<T>*& z) {
    while (z != root && z->parent->color == RED) {
        // If parent is left child of grandparent
        if (z->parent == z->parent->parent->left) {
            RBNode<T>* y = z->parent->parent->right; // uncle
            if (y && y->color == RED) {
                // === Case 1 (uncle RED): recolor and move up ===
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent; // continue fixing at grandparent
            } else {
                if (z == z->parent->right) {
                    // === Case 2: z is right child (inner) ===
                    // Rotate left at parent to convert to Case 3
                    z = z->parent;
                    rotateLeft(z);
                }
                // === Case 3: z is left child (outer) ===
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                rotateRight(z->parent->parent);
            }
        } else {
            // Mirror: parent is right child of grandparent
            RBNode<T>* y = z->parent->parent->left; // uncle
            if (y && y->color == RED) {
                // === Case 1 (mirror): recolor and move up ===
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->left) {
                    // === Case 2 (mirror): z is left child -> rotate right at parent ===
                    z = z->parent;
                    rotateRight(z);
                }
                // === Case 3 (mirror): recolor and rotate left at grandparent ===
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                rotateLeft(z->parent->parent);
            }
        }
    }
    // Ensure root is BLACK (property of RB trees)
    if (root) root->color = BLACK;
}

// ---------------- Delete ----------------
// Removal follows CLRS algorithm: do a BST delete, track the node y that was
// actually removed (or moved) and its original color. If a BLACK node was
// removed then the black-height property may be violated and fixDeletion(x)
// restores it. fixDeletion handles four main cases (and mirrors):
//
// Case 1: Sibling w is RED.
//   - Action: recolor w and parent, rotate at parent — transforms the situation
//     so sibling is BLACK and one of the other cases applies.
//
// Case 2: Sibling w is BLACK and both of w's children are BLACK.
//   - Action: color w RED and move x up to parent (reduces black-count on path),
//     continuing the loop.
//
// Case 3: Sibling w is BLACK, w's far child is BLACK, and w's near child is RED.
//   - Action: recolor near child and w, rotate at w to convert to Case 4.
//
// Case 4: Sibling w is BLACK and w's far child is RED.
//   - Action: recolor w with parent's color, color parent BLACK, color w's far child BLACK,
//     rotate at parent — done, set x = root to exit loop.

template <typename T>
RBNode<T>* RedBlackTree<T>::minimum(RBNode<T>* node) const {
    while (node->left != nullptr)
        node = node->left;
    return node;
}

template <typename T>
void RedBlackTree<T>::transplant(RBNode<T>* u, RBNode<T>* v) {
    // Replace subtree rooted at u with subtree rooted at v
    if (u->parent == nullptr)
        root = v;
    else if (u == u->parent->left)
        u->parent->left = v;
    else
        u->parent->right = v;
    if (v != nullptr)
        v->parent = u->parent;
}

template <typename T>
void RedBlackTree<T>::remove(T key) {
    RBNode<T>* z = searchHelper(root, key);
    if (!z) return; // key not found

    RBNode<T>* y = z;           // node to be removed or moved
    RBNode<T>* x;               // node that will replace y (may be nullptr)
    Color yOriginalColor = y->color;

    if (z->left == nullptr) {
        // No left child: replace z with its right child
        x = z->right;
        transplant(z, z->right);
    } else if (z->right == nullptr) {
        // No right child: replace z with its left child
        x = z->left;
        transplant(z, z->left);
    } else {
        // Two children: find successor y (minimum of z->right)
        y = minimum(z->right);
        yOriginalColor = y->color;
        x = y->right; // x is successor's right child (may be nullptr)
        if (y->parent == z) {
            // Successor is direct child of z
            if (x) x->parent = y;
        } else {
            // Replace y with its right child
            transplant(y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        // Replace z with y
        transplant(z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color; // copy color
    }

    // z is removed from memory; if the removed node was BLACK we must fix
    // the potential violation. x is the node that replaced y (might be nullptr)
    delete z;
    if (yOriginalColor == BLACK)
        fixDeletion(x);
}

/*
 * fixDeletion(x) — restore RB properties when a BLACK node was removed
 * ------------------------------------------------------------------
 * The parameter x is the node that replaced the (removed) node y. x may be
 * nullptr which conceptually means a BLACK leaf.
 * The loop continues until x becomes root or the extra-black is resolved.
 */
template <typename T>
void RedBlackTree<T>::fixDeletion(RBNode<T>*& x) {
    // Note: Many checks below must treat nullptr as a BLACK leaf.
    while (x != root && (!x || x->color == BLACK)) {
        // Determine if x is left or right child of its parent. But x can be nullptr,
        // so we must look at parent's pointers. If x is nullptr, we assume it is the
        // 'left' branch when comparing to parent->left/right (the code below uses x == x->parent->left
        // only when x is non-null; otherwise we must compare parent's pointers directly).

        // To simplify and keep behavior consistent with CLRS, we will assume x is non-null
        // while checking parity; if x==nullptr we use its parent to find sibling.

        if (x && x->parent && x == x->parent->left) {
            RBNode<T>* w = x->parent->right; // sibling
            // Case 1: sibling is RED -> make it BLACK and rotate around parent
            if (w && w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                rotateLeft(x->parent);
                w = x->parent->right;
            }
            // Now sibling is BLACK
            if ((!w->left || w->left->color == BLACK) && (!w->right || w->right->color == BLACK)) {
                // Case 2: both sibling's children are BLACK
                w->color = RED;
                x = x->parent; // move up the tree and continue
            } else {
                if (!w->right || w->right->color == BLACK) {
                    // Case 3: sibling's far child BLACK, near child RED
                    if (w->left) w->left->color = BLACK;
                    w->color = RED;
                    rotateRight(w);
                    w = x->parent->right;
                }
                // Case 4: sibling's far child RED
                w->color = x->parent->color;
                x->parent->color = BLACK;
                if (w->right) w->right->color = BLACK;
                rotateLeft(x->parent);
                x = root; // done
            }
        } else if (x && x->parent) {
            // Mirror cases: x is right child of parent
            RBNode<T>* w = x->parent->left;
            if (w && w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                rotateRight(x->parent);
                w = x->parent->left;
            }
            if ((!w->right || w->right->color == BLACK) && (!w->left || w->left->color == BLACK)) {
                w->color = RED;
                x = x->parent;
            } else {
                if (!w->left || w->left->color == BLACK) {
                    if (w->right) w->right->color = BLACK;
                    w->color = RED;
                    rotateLeft(w);
                    w = x->parent->left;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                if (w->left) w->left->color = BLACK;
                rotateRight(x->parent);
                x = root;
            }
        } else {
            // If x is nullptr (rare path) or parent is null, break to avoid deref
            break;
        }
    }
    if (x) x->color = BLACK; // remove extra-black if any
}

// ---------------- Traversal & Search ----------------
template <typename T>
void RedBlackTree<T>::inorderHelper(RBNode<T>* node) const {
    if (node == nullptr) return;
    inorderHelper(node->left);
    cout << node->key << " (" << (node->color == RED ? "R" : "B") << ") ";
    inorderHelper(node->right);
}

template <typename T>
void RedBlackTree<T>::inorder() const {
    inorderHelper(root);
    cout << endl;
}

template <typename T>
RBNode<T>* RedBlackTree<T>::searchHelper(RBNode<T>* node, T key) const {
    if (node == nullptr || node->key == key)
        return node;
    if (key < node->key)
        return searchHelper(node->left, key);
    return searchHelper(node->right, key);
}

template <typename T>
bool RedBlackTree<T>::search(T key) const {
    return searchHelper(root, key) != nullptr;
}

#endif // REDBTREE_H
