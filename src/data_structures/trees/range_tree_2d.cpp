#include <bits/stdc++.h>
using namespace std;

/*
==========================================================
 Orthogonal 2D Range Tree (Static)
----------------------------------------------------------
 Construction Time:
   - With merge:        O(n log n)
   - Without merge:     O(n log^2 n)  (NOT USED HERE)

 Construction Space:
   - O(n log n)

 Query Time:
   - O(log^2 n + k)

 Query Space:
   - O(log n) recursion stack

==========================================================
*/

// ----------------------------
// Point definition
// ----------------------------
struct Point {
    int x, y;
};

// ----------------------------
// Node of Range Tree
// ----------------------------
struct Node {
    // key used for X-tree navigation
    int key_x;

    // interval of x covered by this node
    int x_min, x_max;

    // children in X-tree
    Node* left;
    Node* right;

    // associated tree:
    // points in this subtree sorted by y
    vector<Point> assoc_y;

    Node() : left(nullptr), right(nullptr) {}
};

// --------------------------------------------------
// Utility: merge two arrays sorted by y (then x)
// Time: O(n)
// --------------------------------------------------
vector<Point> mergeByY(const vector<Point>& a,
                       const vector<Point>& b) {
    vector<Point> res;
    int i = 0, j = 0;

    while (i < (int)a.size() && j < (int)b.size()) {
        if (a[i].y < b[j].y ||
           (a[i].y == b[j].y && a[i].x < b[j].x)) {
            res.push_back(a[i++]);
        } else {
            res.push_back(b[j++]);
        }
    }
    while (i < (int)a.size()) res.push_back(a[i++]);
    while (j < (int)b.size()) res.push_back(b[j++]);

    return res;
}

// --------------------------------------------------
// Build 2D Range Tree
// Input:
//   points sorted by x (then y)
// Output:
//   root of range tree
//
// Returns also points sorted by y (for merge trick)
// --------------------------------------------------
Node* buildRangeTree(
    const vector<Point>& pts,
    int l, int r,
    vector<Point>& sortedByY
) {
    // Base case: a single point becomes a leaf.
    // (Using l >= r here would make [l, r) with one element recurse forever
    //  because mid == l and the right half would never shrink.)
    if (r - l <= 1) {
        Node* leaf = new Node();
        leaf->key_x = pts[l].x;
        leaf->x_min = pts[l].x;
        leaf->x_max = pts[l].x;
        sortedByY = { pts[l] };
        leaf->assoc_y = sortedByY;
        return leaf;
    }

    int mid = (l + r) / 2;

    Node* node = new Node();

    // key is x of median point
    node->key_x = pts[mid].x;

    // interval on x
    node->x_min = pts[l].x;
    node->x_max = pts[r - 1].x;

    // Build left and right subtrees
    vector<Point> leftY, rightY;
    node->left  = buildRangeTree(pts, l, mid, leftY);
    node->right = buildRangeTree(pts, mid, r, rightY);

    // Merge Y-sorted arrays (O(n))
    sortedByY = mergeByY(leftY, rightY);

    // Associated tree is simply sorted array by y
    node->assoc_y = sortedByY;

    return node;
}

// --------------------------------------------------
// Report points from assoc_y with y in [y1, y2]
// Time: O(log n + k)
// --------------------------------------------------
void reportY(
    const vector<Point>& arr,
    int y1, int y2,
    vector<Point>& result
) {
    // lower_bound on y
    auto it1 = lower_bound(
        arr.begin(), arr.end(), y1,
        [](const Point& p, int val) {
            return p.y < val;
        }
    );

    // iterate until y > y2
    for (auto it = it1; it != arr.end() && it->y <= y2; ++it) {
        result.push_back(*it);
    }
}

// --------------------------------------------------
// Range Query on X-tree
// --------------------------------------------------
void rangeQueryX(
    Node* node,
    int x1, int x2,
    int y1, int y2,
    vector<Point>& result
) {
    if (!node) return;

    // Case 1: disjoint
    if (node->x_max < x1 || node->x_min > x2)
        return;

    // Case 2: fully contained
    if (x1 <= node->x_min && node->x_max <= x2) {
        // Directly query associated Y-tree
        reportY(node->assoc_y, y1, y2, result);
        return;
    }

    // Case 3: partial overlap
    rangeQueryX(node->left,  x1, x2, y1, y2, result);
    rangeQueryX(node->right, x1, x2, y1, y2, result);
}

// --------------------------------------------------
// Public query function
// --------------------------------------------------
vector<Point> rangeQuery(
    Node* root,
    int x1, int x2,
    int y1, int y2
) {
    vector<Point> result;
    rangeQueryX(root, x1, x2, y1, y2, result);
    return result;
}

// --------------------------------------------------
// Example usage
// --------------------------------------------------
int main() {
    vector<Point> points = {
        {1,4}, {2,5}, {5,2}, {6,7}, {7,3}, {8,9}
    };

    // Sort points by x (then y)
    sort(points.begin(), points.end(), [](auto& a, auto& b) {
        if (a.x != b.x) return a.x < b.x;
        return a.y < b.y;
    });

    vector<Point> dummy;
    Node* root = buildRangeTree(points, 0, points.size(), dummy);

    // Query rectangle
    int x1 = 1, x2 = 8;
    int y1 = 2, y2 = 5;

    vector<Point> ans = rangeQuery(root, x1, x2, y1, y2);

    cout << "Query result:\n";
    for (auto& p : ans) {
        cout << "(" << p.x << ", " << p.y << ")\n";
    }
}
