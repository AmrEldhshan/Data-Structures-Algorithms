#include "data_structures/graph/graph.h"

#include <algorithm>
#include <array>
#include <iostream>
#include <vector>

using namespace std;

// ---------------------------------------------------------------------------
// Tree DP: maximum weight independent set
//
// An independent set contains no two adjacent vertices. On a tree we can
// decide for every node whether it is included:
//
//   dp[v][0] = best answer in v's subtree when v is excluded
//              = sum of max(dp[child][0], dp[child][1])
//   dp[v][1] = best answer when v is included
//              = weight[v] + sum of dp[child][0]
//
// Time:  O(V)
// Space: O(V)
// ---------------------------------------------------------------------------
struct TreeDp {
    vector<array<int, 2>> dp;
    vector<int> chosen;
};

void solve(const Graph& tree, int vertex, int parent,
           const vector<int>& weight, TreeDp& state) {
    state.dp[vertex][0] = 0;
    state.dp[vertex][1] = weight[vertex];

    for (const Edge& edge : tree.neighbors(vertex)) {
        if (edge.to == parent) continue;

        solve(tree, edge.to, vertex, weight, state);
        state.dp[vertex][0] += max(state.dp[edge.to][0], state.dp[edge.to][1]);
        state.dp[vertex][1] += state.dp[edge.to][0];
    }
}

void reconstruct(const Graph& tree, int vertex, int parent, bool canTake,
                 const vector<int>& weight, const TreeDp& state,
                 vector<int>& chosen) {
    bool take = canTake && state.dp[vertex][1] >= state.dp[vertex][0];

    if (take) chosen.push_back(vertex);

    for (const Edge& edge : tree.neighbors(vertex)) {
        if (edge.to == parent) continue;
        reconstruct(tree, edge.to, vertex, !take, weight, state, chosen);
    }
}

int main() {
    /*
        Tree:
                0 (weight 10)
               / \
              1   2   (5, 7)
             / \   \
            3   4   5 (3, 8, 2)
    */
    Graph tree(6, false);
    tree.addEdge(0, 1);
    tree.addEdge(0, 2);
    tree.addEdge(1, 3);
    tree.addEdge(1, 4);
    tree.addEdge(2, 5);

    vector<int> weight = {10, 5, 7, 3, 8, 2};

    TreeDp state;
    state.dp.assign(tree.size(), {0, 0});
    solve(tree, 0, -1, weight, state);

    vector<int> chosen;
    reconstruct(tree, 0, -1, true, weight, state, chosen);

    cout << "maximum independent-set weight: "
         << max(state.dp[0][0], state.dp[0][1]) << '\n';
    cout << "chosen vertices: ";
    for (int vertex : chosen) cout << vertex << ' ';
    cout << '\n';

    return 0;
}
