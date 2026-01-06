#include <bits/stdc++.h>
using namespace std;

/*
===========================================================
 Segment Tree for Interval Overlap Queries (Static)
===========================================================

- Stores static input intervals [lo, hi)
- Allows reporting all intervals overlapping a query interval
- Allows single-point query
- Uses canonical representation

-----------------------------------------------------------
 Time Complexity:
 -----------------------------------------------------------
 Build Tree Structure:      O(n log n)
 Insert all intervals:      O(n log n)
 Query overlapping:         O(log n + k)
 Single point query:        O(log n + k)

-----------------------------------------------------------
 Space Complexity:
 -----------------------------------------------------------
 Segment tree nodes:        O(n)
 Interval attachments:     O(n log n)
 Total:                    O(n log n)
===========================================================
*/

// ---------------- Interval Structure ----------------
struct Interval {
    int lo, hi;   // right-open interval [lo, hi)

    Interval(int l, int h) : lo(l), hi(h) {}

    // check overlap with another interval
    bool overlaps(const Interval& other) const {
        return lo < other.hi && other.lo < hi;
    }

    // check if contains a point
    bool contains(int x) const {
        return lo <= x && x < hi;
    }
};

// ---------------- Segment Tree Node ----------------
struct SegNode {
    int start, end;                 // segment tree interval [start, end)
    vector<Interval> intervals;     // input intervals attached here
    SegNode* left;
    SegNode* right;

    SegNode(int s, int e)
        : start(s), end(e), left(nullptr), right(nullptr) {}
};

// ---------------- Segment Tree Class ----------------
class SegmentTree {
private:
    SegNode* root;

    // ------------------------------------------------
    // Build segment tree from sorted endpoints
    // Time: O(n)
    // ------------------------------------------------
    SegNode* build(const vector<int>& points, int l, int r) {
        if (l + 1 == r) {
            // Leaf node: [points[l], points[r])
            return new SegNode(points[l], points[r]);
        }

        int mid = (l + r) / 2;
        SegNode* node = new SegNode(points[l], points[r]);
        node->left = build(points, l, mid);
        node->right = build(points, mid, r);
        return node;
    }

    // ------------------------------------------------
    // Insert interval using canonical representation
    // Time per interval: O(log n)
    // ------------------------------------------------
    void insertInterval(SegNode* node, const Interval& in) {
        // Case 1: Node interval fully inside input interval
        if (in.lo <= node->start && node->end <= in.hi) {
            node->intervals.push_back(in);
            return;
        }

        // Case 2: Partial overlap → go down
        if (node->left && in.lo < node->left->end)
            insertInterval(node->left, in);

        if (node->right && in.hi > node->right->start)
            insertInterval(node->right, in);
    }

    // ------------------------------------------------
    // Report all overlapping intervals with query
    // Time: O(log n + k)
    // ------------------------------------------------
    void queryInterval(SegNode* node, const Interval& q,
                       vector<Interval>& result) const {
        if (!node) return;

        // Case 1: Disjoint
        if (node->end <= q.lo || node->start >= q.hi)
            return;

        // Case 2: Node interval fully inside query
        if (q.lo <= node->start && node->end <= q.hi) {
            // Report everything under this subtree
            collectAll(node, result);
            return;
        }

        // Case 3: Partial overlap
        for (const auto& in : node->intervals)
            if (in.overlaps(q))
                result.push_back(in);

        queryInterval(node->left, q, result);
        queryInterval(node->right, q, result);
    }

    // ------------------------------------------------
    // Collect all intervals in subtree
    // Time: proportional to output size
    // ------------------------------------------------
    void collectAll(SegNode* node, vector<Interval>& result) const {
        if (!node) return;

        for (const auto& in : node->intervals)
            result.push_back(in);

        collectAll(node->left, result);
        collectAll(node->right, result);
    }

    // ------------------------------------------------
    // Single point query
    // Time: O(log n + k)
    // ------------------------------------------------
    void queryPoint(SegNode* node, int x,
                    vector<Interval>& result) const {
        if (!node) return;

        if (!(node->start <= x && x < node->end))
            return;

        for (const auto& in : node->intervals)
            if (in.contains(x))
                result.push_back(in);

        if (node->left && x < node->left->end)
            queryPoint(node->left, x, result);
        else
            queryPoint(node->right, x, result);
    }

public:
    // ------------------------------------------------
    // Constructor
    // ------------------------------------------------
    SegmentTree(const vector<Interval>& input) {
        // Collect all endpoints
        set<int> endpoints;
        for (auto& in : input) {
            endpoints.insert(in.lo);
            endpoints.insert(in.hi);
        }

        vector<int> points(endpoints.begin(), endpoints.end());

        // Build tree structure
        root = build(points, 0, points.size() - 1);

        // Insert intervals
        for (auto& in : input)
            insertInterval(root, in);
    }

    // ------------------------------------------------
    // Public query: interval
    // ------------------------------------------------
    vector<Interval> queryInterval(int lo, int hi) const {
        vector<Interval> result;
        queryInterval(root, Interval(lo, hi), result);
        return result;
    }

    // ------------------------------------------------
    // Public query: single point
    // ------------------------------------------------
    vector<Interval> queryPoint(int x) const {
        vector<Interval> result;
        queryPoint(root, x, result);
        return result;
    }
};
