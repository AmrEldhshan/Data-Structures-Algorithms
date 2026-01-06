// #include <bits/stdc++.h>
#include <iostream>
#include <vector>
using namespace std;

/*
===========================================================
 Dynamic Interval Tree (Educational Implementation)
 ----------------------------------------------------------
 - Tree is ordered by lo endpoint (BST-style)
 - Each node is augmented with `max` = maximum hi in subtree
 - Assumes tree height is O(log n) (RB-tree idea)
===========================================================
*/

class IntervalTree {
private:
    /* ================= Node Definition ================= */
    struct Node {
        int lo, hi;      // interval [lo, hi]
        int max;         // maximum hi in subtree
        Node *left;
        Node *right;

        Node(int l, int h) {
            lo = l;
            hi = h;
            max = h;
            left = right = nullptr;
        }
    };

    Node* root = nullptr;

    /* ================= Utility ================= */

    // Check if two intervals overlap
    // Time: O(1)
    bool overlap(int l1, int h1, int l2, int h2) {
        return (l1 <= h2 && l2 <= h1);
    }

    /* ================= Insert ================= */
    /*
      Inserts an interval into the tree.
      Updates `max` along the insertion path.

      Time Complexity: O(log n)
      Space Complexity: O(log n) (recursion stack)
    */
    Node* insert(Node* node, int lo, int hi) {
        if (!node)
            return new Node(lo, hi);

        if (lo < node->lo)
            node->left = insert(node->left, lo, hi);
        else
            node->right = insert(node->right, lo, hi);

        // Update max value
        node->max = max(node->max, hi);
        return node;
    }

    /* ====================================================
       1) Search for ANY overlapping interval
          Time: O(log n)
          Space: O(1)
       ==================================================== */
    Node* searchAny(Node* node, int lo, int hi) {
        if (!node)
            return nullptr;

        // If current node overlaps, return it
        if (overlap(node->lo, node->hi, lo, hi))
            return node;

        // If left subtree may contain overlap, search it
        if (node->left && node->left->max >= lo)
            return searchAny(node->left, lo, hi);

        // Otherwise, go right
        return searchAny(node->right, lo, hi);
    }

    /* ====================================================
       2) Search for overlapping interval
          with SMALLEST lo endpoint
          Time: O(log n)
          Space: O(log n)
       ==================================================== */
    Node* searchMinLo(Node* node, int lo, int hi) {
        if (!node)
            return nullptr;

        // Search left subtree first
        if (node->left && node->left->max >= lo) {
            Node* res = searchMinLo(node->left, lo, hi);
            if (res) return res;
        }

        // Check current node
        if (overlap(node->lo, node->hi, lo, hi))
            return node;

        // Search right subtree
        return searchMinLo(node->right, lo, hi);
    }

    /* ====================================================
       3) Search for ALL overlapping intervals
          Time: O(log n + k)
          Space: O(log n + k)
       ==================================================== */
    void searchAll(Node* node, int lo, int hi,
                   vector<pair<int,int>>& result) {
        if (!node)
            return;

        // Search left subtree if overlap is possible
        if (node->left && node->left->max >= lo)
            searchAll(node->left, lo, hi, result);

        // Check current node
        if (overlap(node->lo, node->hi, lo, hi))
            result.push_back({node->lo, node->hi});

        // Search right subtree if overlap is possible
        if (node->right && node->lo <= hi)
            searchAll(node->right, lo, hi, result);
    }

public:
    /* ================= Public Interface ================= */

    // Insert interval
    void insert(int lo, int hi) {
        root = insert(root, lo, hi);
    }

    // Search for ANY overlapping interval
    bool searchAny(int lo, int hi, pair<int,int>& res) {
        Node* ans = searchAny(root, lo, hi);
        if (!ans) return false;
        res = {ans->lo, ans->hi};
        return true;
    }

    // Search for overlapping interval with smallest lo
    bool searchSmallestLo(int lo, int hi, pair<int,int>& res) {
        Node* ans = searchMinLo(root, lo, hi);
        if (!ans) return false;
        res = {ans->lo, ans->hi};
        return true;
    }

    // Search for ALL overlapping intervals
    vector<pair<int,int>> searchAll(int lo, int hi) {
        vector<pair<int,int>> result;
        searchAll(root, lo, hi, result);
        return result;
    }
};

/* ======================= MAIN ======================= */

int main() {
    IntervalTree tree;

    // Insert intervals
    tree.insert(15, 20);
    tree.insert(10, 30);
    tree.insert(17, 19);
    tree.insert(5, 20);
    tree.insert(12, 15);
    tree.insert(30, 40);

    int qlo = 14, qhi = 16;

    cout << "Query interval: [" << qlo << ", " << qhi << "]\n\n";

    // 1) Any overlapping interval
    pair<int,int> any;
    if (tree.searchAny(qlo, qhi, any))
        cout << "Any overlap: [" << any.first << ", "
             << any.second << "]\n";
    else
        cout << "No overlap found\n";

    // 2) Overlapping interval with smallest lo
    pair<int,int> minLo;
    if (tree.searchSmallestLo(qlo, qhi, minLo))
        cout << "Smallest lo overlap: [" << minLo.first
             << ", " << minLo.second << "]\n";

    // 3) All overlapping intervals
    auto all = tree.searchAll(qlo, qhi);
    cout << "\nAll overlapping intervals:\n";
    for (auto &p : all)
        cout << "[" << p.first << ", " << p.second << "]\n";

    return 0;
}
