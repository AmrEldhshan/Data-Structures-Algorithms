// #include <bits/stdc++.h>
#include <iostream>
#include <vector>
using namespace std;

/*
============================================================
 Red-Black Interval Tree (CLRS-style)
 -----------------------------------------------------------
 - RB-Tree keyed by lo endpoint
 - Each node stores interval [lo, hi]
 - Augmented with max = maximum hi in subtree
============================================================
*/

enum Color { RED, BLACK };

class IntervalTree {
private:
    struct Node {
        int lo, hi;
        int max;          // maximum hi in subtree
        Color color;
        Node *left, *right, *parent;

        Node(int l, int h) {
            lo = l;
            hi = h;
            max = h;
            color = RED;
            left = right = parent = nullptr;
        }
    };

    Node* root = nullptr;

    /* ================= Utility ================= */

    bool overlap(int l1, int h1, int l2, int h2) {
        return (l1 <= h2 && l2 <= h1);
    }

    int getMax(Node* x) {
        return x ? x->max : INT_MIN;
    }

    void updateMax(Node* x) {
        if (!x) return;
        x->max = max({x->hi, getMax(x->left), getMax(x->right)});
    }

    /* ================= Rotations ================= */

    void leftRotate(Node* x) {
        Node* y = x->right;
        x->right = y->left;

        if (y->left)
            y->left->parent = x;

        y->parent = x->parent;

        if (!x->parent)
            root = y;
        else if (x == x->parent->left)
            x->parent->left = y;
        else
            x->parent->right = y;

        y->left = x;
        x->parent = y;

        updateMax(x);
        updateMax(y);
    }

    void rightRotate(Node* y) {
        Node* x = y->left;
        y->left = x->right;

        if (x->right)
            x->right->parent = y;

        x->parent = y->parent;

        if (!y->parent)
            root = x;
        else if (y == y->parent->left)
            y->parent->left = x;
        else
            y->parent->right = x;

        x->right = y;
        y->parent = x;

        updateMax(y);
        updateMax(x);
    }

    /* ================= RB Insert Fixup ================= */

    void insertFixup(Node* z) {
        while (z->parent && z->parent->color == RED) {
            if (z->parent == z->parent->parent->left) {
                Node* y = z->parent->parent->right; // uncle
                if (y && y->color == RED) {
                    z->parent->color = BLACK;
                    y->color = BLACK;
                    z->parent->parent->color = RED;
                    z = z->parent->parent;
                } else {
                    if (z == z->parent->right) {
                        z = z->parent;
                        leftRotate(z);
                    }
                    z->parent->color = BLACK;
                    z->parent->parent->color = RED;
                    rightRotate(z->parent->parent);
                }
            } else {
                Node* y = z->parent->parent->left;
                if (y && y->color == RED) {
                    z->parent->color = BLACK;
                    y->color = BLACK;
                    z->parent->parent->color = RED;
                    z = z->parent->parent;
                } else {
                    if (z == z->parent->left) {
                        z = z->parent;
                        rightRotate(z);
                    }
                    z->parent->color = BLACK;
                    z->parent->parent->color = RED;
                    leftRotate(z->parent->parent);
                }
            }
        }
        root->color = BLACK;
    }

    /* ================= Insert ================= */

    void insert(Node* z) {
        Node* y = nullptr;
        Node* x = root;

        while (x) {
            y = x;
            if (z->lo < x->lo)
                x = x->left;
            else
                x = x->right;
        }

        z->parent = y;
        if (!y)
            root = z;
        else if (z->lo < y->lo)
            y->left = z;
        else
            y->right = z;

        // update max on path to root
        Node* cur = z;
        while (cur) {
            updateMax(cur);
            cur = cur->parent;
        }

        insertFixup(z);
    }

    /* ==================================================
       1) Search ANY overlapping interval
       Time: O(log n)
       ================================================== */
    Node* searchAny(Node* node, int lo, int hi) {
        while (node && !overlap(node->lo, node->hi, lo, hi)) {
            if (node->left && node->left->max >= lo)
                node = node->left;
            else
                node = node->right;
        }
        return node;
    }

    /* ==================================================
       2) Search overlapping interval with SMALLEST lo
       ================================================== */
    Node* searchMinLo(Node* node, int lo, int hi) {
        if (!node)
            return nullptr;

        if (node->left && node->left->max >= lo) {
            Node* res = searchMinLo(node->left, lo, hi);
            if (res) return res;
        }

        if (overlap(node->lo, node->hi, lo, hi))
            return node;

        return searchMinLo(node->right, lo, hi);
    }

    /* ==================================================
       3) Search ALL overlapping intervals
       ================================================== */
    void searchAll(Node* node, int lo, int hi,
                   vector<pair<int,int>>& res) {
        if (!node) return;

        if (node->left && node->left->max >= lo)
            searchAll(node->left, lo, hi, res);

        if (overlap(node->lo, node->hi, lo, hi))
            res.push_back({node->lo, node->hi});

        if (node->right && node->lo <= hi)
            searchAll(node->right, lo, hi, res);
    }

public:
    /* ================= Public Interface ================= */

    void insert(int lo, int hi) {
        insert(new Node(lo, hi));
    }

    bool searchAny(int lo, int hi, pair<int,int>& res) {
        Node* ans = searchAny(root, lo, hi);
        if (!ans) return false;
        res = {ans->lo, ans->hi};
        return true;
    }

    bool searchSmallestLo(int lo, int hi, pair<int,int>& res) {
        Node* ans = searchMinLo(root, lo, hi);
        if (!ans) return false;
        res = {ans->lo, ans->hi};
        return true;
    }

    vector<pair<int,int>> searchAll(int lo, int hi) {
        vector<pair<int,int>> res;
        searchAll(root, lo, hi, res);
        return res;
    }
};

/* =========================== MAIN =========================== */

int main() {
    IntervalTree tree;

    tree.insert(15, 20);
    tree.insert(10, 30);
    tree.insert(17, 19);
    tree.insert(5, 20);
    tree.insert(12, 15);
    tree.insert(30, 40);

    int ql = 14, qh = 16;

    cout << "Query: [" << ql << ", " << qh << "]\n\n";

    pair<int,int> any;
    if (tree.searchAny(ql, qh, any))
        cout << "Any overlap: [" << any.first << ", " << any.second << "]\n";

    pair<int,int> minLo;
    if (tree.searchSmallestLo(ql, qh, minLo))
        cout << "Smallest lo overlap: [" << minLo.first << ", " << minLo.second << "]\n";

    auto all = tree.searchAll(ql, qh);
    cout << "\nAll overlapping intervals:\n";
    for (auto &p : all)
        cout << "[" << p.first << ", " << p.second << "]\n";

    return 0;
}
