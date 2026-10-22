#include "data_structures/graph/graph.h"

#include <iostream>
#include <vector>

using namespace std;

// ---------------------------------------------------------------------------
// Lowest common ancestor (binary lifting)
//
// Precompute up[k][v] = the 2^k-th ancestor of v, and depth[v]. Then:
//   1. Lift the deeper vertex until both are at the same depth.
//   2. Lift both together from the largest power of two downwards.
//
// Time:  O(V log V) build, O(log V) per query
// Space: O(V log V)
// ---------------------------------------------------------------------------
class LowestCommonAncestor {
public:
    explicit LowestCommonAncestor(const Graph& tree, int root = 0)
        : depth_(tree.size(), 0), up_(maxLog(tree.size()), vector<int>(tree.size(), -1)) {
        dfs(tree, root, -1, 0);
    }

    int query(int a, int b) const {
        if (depth_[a] < depth_[b]) swap(a, b);

        int difference = depth_[a] - depth_[b];
        for (int bit = 0; difference != 0; ++bit, difference >>= 1) {
            if (difference & 1) a = up_[bit][a];
        }

        if (a == b) return a;

        for (int bit = static_cast<int>(up_.size()) - 1; bit >= 0; --bit) {
            if (up_[bit][a] != up_[bit][b]) {
                a = up_[bit][a];
                b = up_[bit][b];
            }
        }

        return up_[0][a];
    }

    int distance(int a, int b) const {
        int ancestor = query(a, b);
        return depth_[a] + depth_[b] - 2 * depth_[ancestor];
    }

private:
    static int maxLog(int n) {
        int levels = 1;
        while ((1 << levels) <= n) ++levels;
        return levels;
    }

    void dfs(const Graph& tree, int vertex, int parent, int depth) {
        depth_[vertex] = depth;
        up_[0][vertex] = parent;

        for (size_t bit = 1; bit < up_.size(); ++bit) {
            int middle = up_[bit - 1][vertex];
            up_[bit][vertex] = (middle == -1) ? -1 : up_[bit - 1][middle];
        }

        for (const Edge& edge : tree.neighbors(vertex)) {
            if (edge.to != parent) dfs(tree, edge.to, vertex, depth + 1);
        }
    }

    vector<int> depth_;
    vector<vector<int>> up_;
};

int main() {
    /* Tree:
     *
     *          0
     *        /   \
     *       1     2
     *      / \     \
     *     3   4     5
     *    /
     *   6
     */
    Graph tree(7, false);
    tree.addEdge(0, 1);
    tree.addEdge(0, 2);
    tree.addEdge(1, 3);
    tree.addEdge(1, 4);
    tree.addEdge(2, 5);
    tree.addEdge(3, 6);

    LowestCommonAncestor lca(tree, 0);

    cout << "LCA(6, 4) = " << lca.query(6, 4) << '\n';
    cout << "LCA(6, 5) = " << lca.query(6, 5) << '\n';
    cout << "LCA(3, 4) = " << lca.query(3, 4) << '\n';
    cout << "Distance(6, 5) = " << lca.distance(6, 5) << '\n';

    return 0;
}
