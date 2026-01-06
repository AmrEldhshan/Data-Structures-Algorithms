#include <bits/stdc++.h>
using namespace std;

/*
===========================================================
KD-TREE IMPLEMENTATION (d-DIMENSIONS)
===========================================================

- Static data structure (build once, query many times)
- Supports orthogonal range queries
- Points stored ONLY in leaves
- Internal nodes store splitting information only

-----------------------------------------------------------
TIME COMPLEXITIES:
-----------------------------------------------------------
Build Time      : O(n log n)
Space Complexity: O(n)
Query Time      : O(n^(1 - 1/d) + k)
  - For 2D: O(sqrt(n) + k)

-----------------------------------------------------------
WHY QUERY IS NOT LOG n?
-----------------------------------------------------------
Because the query rectangle may INTERSECT splitting lines,
forcing us to explore BOTH subtrees at some levels.
===========================================================
*/

// -----------------------------
// Point in d dimensions
// -----------------------------
struct Point {
    vector<double> coord;  // coordinates in d dimensions

    Point(int d = 0) {
        coord.resize(d);
    }
};

// -----------------------------
// KD-Tree Node
// -----------------------------
struct KDNode {
    int splitDim;          // which dimension we split on
    double splitValue;     // median value for splitting
    KDNode* left;
    KDNode* right;
    Point* point;          // non-null ONLY for leaf nodes

    KDNode() {
        left = right = nullptr;
        point = nullptr;
    }
};

// -----------------------------
// KD-Tree Class
// -----------------------------
class KDTree {
private:
    KDNode* root;
    int d;   // number of dimensions

    /*
    ===========================================================
    BUILD FUNCTION
    ===========================================================
    Recursively builds KD-tree by:
    1) Selecting split dimension (cycling)
    2) Finding median
    3) Dividing points
    ===========================================================
    */

    KDNode* build(vector<Point*>& pts, int depth) {
        if (pts.empty()) return nullptr;

        KDNode* node = new KDNode();

        // Leaf node: only one point
        if (pts.size() == 1) {
            node->point = pts[0];
            return node;
        }

        // Select splitting dimension (cycle)
        int axis = depth % d;
        node->splitDim = axis;

        // Sort points by this dimension
        nth_element(
            pts.begin(),
            pts.begin() + pts.size() / 2,
            pts.end(),
            [axis](Point* a, Point* b) {
                return a->coord[axis] < b->coord[axis];
            }
        );

        int mid = pts.size() / 2;
        node->splitValue = pts[mid]->coord[axis];

        // Divide points
        vector<Point*> leftPts(pts.begin(), pts.begin() + mid);
        vector<Point*> rightPts(pts.begin() + mid, pts.end());

        node->left  = build(leftPts, depth + 1);
        node->right = build(rightPts, depth + 1);

        return node;
    }

    /*
    ===========================================================
    RANGE QUERY FUNCTION
    ===========================================================
    Uses the rule:
    - If query rectangle is FULLY CONTAINED in one side
      -> visit ONE subtree
    - If query rectangle INTERSECTS splitting line
      -> visit BOTH subtrees
    ===========================================================
    */

    void rangeQuery(
        KDNode* node,
        const vector<double>& lo,
        const vector<double>& hi,
        vector<Point*>& result
    ) {
        if (!node) return;

        // Leaf node: check the single stored point
        if (node->point) {
            bool inside = true;
            for (int i = 0; i < d; i++) {
                if (node->point->coord[i] < lo[i] ||
                    node->point->coord[i] > hi[i]) {
                    inside = false;
                    break;
                }
            }
            if (inside) result.push_back(node->point);
            return;
        }

        int axis = node->splitDim;
        double split = node->splitValue;

        // -----------------------------
        // FULLY CONTAINED CASES
        // -----------------------------

        // Query is completely on the LEFT
        if (hi[axis] < split) {
            rangeQuery(node->left, lo, hi, result);
        }
        // Query is completely on the RIGHT
        else if (lo[axis] >= split) {
            rangeQuery(node->right, lo, hi, result);
        }
        // -----------------------------
        // INTERSECTS SPLITTING LINE
        // -----------------------------
        else {
            rangeQuery(node->left, lo, hi, result);
            rangeQuery(node->right, lo, hi, result);
        }
    }

public:
    // Constructor
    KDTree(int dimensions) {
        d = dimensions;
        root = nullptr;
    }

    /*
    ===========================================================
    BUILD TREE (PUBLIC)
    ===========================================================
    Time Complexity: O(n log n)
    Space Complexity: O(n)
    ===========================================================
    */
    void buildTree(vector<Point>& points) {
        vector<Point*> pts;
        for (auto& p : points)
            pts.push_back(&p);

        root = build(pts, 0);
    }

    /*
    ===========================================================
    RANGE QUERY (PUBLIC)
    ===========================================================
    Time Complexity:
      O(n^(1 - 1/d) + k)
    ===========================================================
    */
    vector<Point*> query(
        const vector<double>& lo,
        const vector<double>& hi
    ) {
        vector<Point*> result;
        rangeQuery(root, lo, hi, result);
        return result;
    }
};

// -----------------------------
// EXAMPLE USAGE
// -----------------------------
int main() {
    int d = 2;  // 2D KD-Tree
    KDTree tree(d);

    vector<Point> points;
    points.push_back({{2, 3}});
    points.push_back({{5, 4}});
    points.push_back({{9, 6}});
    points.push_back({{4, 7}});
    points.push_back({{8, 1}});
    points.push_back({{7, 2}});

    tree.buildTree(points);

    // Query rectangle
    vector<double> lo = {3, 1};
    vector<double> hi = {9, 5};

    vector<Point*> result = tree.query(lo, hi);

    cout << "Points inside query rectangle:\n";
    for (auto* p : result) {
        cout << "(";
        for (int i = 0; i < d; i++) {
            cout << p->coord[i];
            if (i + 1 < d) cout << ", ";
        }
        cout << ")\n";
    }

    return 0;
}
