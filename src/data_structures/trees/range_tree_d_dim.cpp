#include <bits/stdc++.h>
using namespace std;

/*
============================================================
  Orthogonal d-Dimensional Range Tree (STATIC)
============================================================

POINTS:
  Each point has d coordinates: p[0], p[1], ..., p[d-1]

TREE STRUCTURE:
  - Level 0: tree on coordinate 0
  - Each node stores an associated (d-1)-dim range tree
    built on coordinates [1 .. d-1]

------------------------------------------------------------
COMPLEXITIES:

Construction Time:
  - Using merge trick:     O(n log n)
  - Without merge:         O(n log^2 n)   (NOT USED)

Construction Space:
  - O(n log n)

Query Time:
  - O(log^d n + k)

Query Space:
  - O(log n) recursion stack

============================================================
*/

// ---------------------------------------------------------
// Point definition (d-dimensional)
// ---------------------------------------------------------
struct Point {
    vector<int> coord;   // coord[i] = coordinate in dimension i
};

// ---------------------------------------------------------
// Range Tree Node (recursive definition)
// ---------------------------------------------------------
struct Node {
    int dim;                 // dimension this node splits on
    int key;                 // split value (median)
    int min_val, max_val;    // interval for this dimension

    Node* left;
    Node* right;

    // Associated tree for remaining dimensions
    Node* assoc;             // (d-1)-dim range tree root

    // Only used when dim == last dimension
    vector<Point> points;    // stored points (sorted)

    Node(int d)
        : dim(d), left(nullptr), right(nullptr), assoc(nullptr) {}
};

// ---------------------------------------------------------
// Compare points by a given dimension (tie-break lexicographically)
// ---------------------------------------------------------
bool compareByDim(const Point& a, const Point& b, int dim) {
    if (a.coord[dim] != b.coord[dim])
        return a.coord[dim] < b.coord[dim];
    return a.coord < b.coord; // tie-break to avoid equal keys
}

// ---------------------------------------------------------
// Build d-dimensional range tree
// Input:
//   pts  : points belonging to this subtree
//   dim  : current dimension
//   D    : total dimensions
//
// Returns root of range tree
// ---------------------------------------------------------
Node* buildRangeTree(vector<Point>& pts, int dim, int D) {
    if (pts.empty()) return nullptr;

    Node* node = new Node(dim);

    // -----------------------------------------------------
    // BASE CASE: last dimension
    // -----------------------------------------------------
    if (dim == D - 1) {
        // Sort points by last coordinate
        sort(pts.begin(), pts.end(),
             [&](const Point& a, const Point& b) {
                 return compareByDim(a, b, dim);
             });

        node->min_val = pts.front().coord[dim];
        node->max_val = pts.back().coord[dim];
        node->points = pts; // store all points here

        return node;
    }

    // -----------------------------------------------------
    // A single point cannot be split further. Keep it as a leaf
    // for this dimension and build the associated tree for the
    // remaining dimensions. (Without this, mid == 0 and the right
    // half would never shrink, causing infinite recursion.)
    // -----------------------------------------------------
    if (pts.size() <= 1) {
        node->key = pts.front().coord[dim];
        node->min_val = pts.front().coord[dim];
        node->max_val = pts.front().coord[dim];
        node->assoc = buildRangeTree(pts, dim + 1, D);
        return node;
    }

    // -----------------------------------------------------
    // Sort points by current dimension
    // -----------------------------------------------------
    sort(pts.begin(), pts.end(),
         [&](const Point& a, const Point& b) {
             return compareByDim(a, b, dim);
         });

    int mid = pts.size() / 2;

    node->key = pts[mid].coord[dim];
    node->min_val = pts.front().coord[dim];
    node->max_val = pts.back().coord[dim];

    // Split points
    vector<Point> leftPts(pts.begin(), pts.begin() + mid);
    vector<Point> rightPts(pts.begin() + mid, pts.end());

    // Build left/right on SAME dimension
    node->left  = buildRangeTree(leftPts, dim, D);
    node->right = buildRangeTree(rightPts, dim, D);

    // Build associated (d-1)-dim tree
    node->assoc = buildRangeTree(pts, dim + 1, D);

    return node;
}

// ---------------------------------------------------------
// Report all points in subtree (used when fully contained)
// ---------------------------------------------------------
void reportSubtree(Node* node, vector<Point>& result) {
    if (!node) return;

    if (!node->points.empty()) {
        for (auto& p : node->points)
            result.push_back(p);
        return;
    }

    reportSubtree(node->left, result);
    reportSubtree(node->right, result);
}

// ---------------------------------------------------------
// Range Query (recursive)
// ---------------------------------------------------------
void rangeQuery(
    Node* node,
    const vector<int>& low,
    const vector<int>& high,
    int D,
    vector<Point>& result
) {
    if (!node) return;

    int d = node->dim;

    // -----------------------------------------------------
    // DISJOINT
    // -----------------------------------------------------
    if (node->max_val < low[d] || node->min_val > high[d])
        return;

    // -----------------------------------------------------
    // FULLY CONTAINED
    // -----------------------------------------------------
    if (low[d] <= node->min_val && node->max_val <= high[d]) {
        if (node->assoc) {
            // Go to associated (d-1)-dim tree
            rangeQuery(node->assoc, low, high, D, result);
        } else {
            // Last dimension
            reportSubtree(node, result);
        }
        return;
    }

    // -----------------------------------------------------
    // PARTIAL OVERLAP
    // -----------------------------------------------------
    rangeQuery(node->left,  low, high, D, result);
    rangeQuery(node->right, low, high, D, result);
}

// ---------------------------------------------------------
// Example usage
// ---------------------------------------------------------
int main() {
    int D = 3; // number of dimensions (change freely)

    vector<Point> points = {
        {{1,4,2}},
        {{2,5,3}},
        {{5,2,1}},
        {{6,7,4}},
        {{7,3,2}},
        {{8,9,6}}
    };

    Node* root = buildRangeTree(points, 0, D);

    // Query rectangle:
    // x in [1,8], y in [2,5], z in [1,3]
    vector<int> low  = {1, 2, 1};
    vector<int> high = {8, 5, 3};

    vector<Point> ans;
    rangeQuery(root, low, high, D, ans);

    cout << "Query result:\n";
    for (auto& p : ans) {
        cout << "(";
        for (int i = 0; i < D; i++) {
            cout << p.coord[i];
            if (i + 1 < D) cout << ", ";
        }
        cout << ")\n";
    }
}

