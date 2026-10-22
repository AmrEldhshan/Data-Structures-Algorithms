#include "data_structures/graph/graph.h"

#include <functional>
#include <iostream>
#include <limits>
#include <queue>
#include <utility>
#include <vector>

using namespace std;

// ---------------------------------------------------------------------------
// Prim's minimum spanning tree
//
// Grow one tree from an arbitrary start vertex. At every step add the
// cheapest edge that connects a vertex inside the tree to one outside it.
// A min-priority queue stores candidate edges, so the next edge is O(log E).
//
// Time:  O(E log V)
// Space: O(V + E)
// ---------------------------------------------------------------------------
struct PrimResult {
    int totalWeight = 0;
    vector<WeightedEdge> edges;
    bool connected = true;
};

PrimResult primMst(const Graph& graph, int start = 0) {
    const int INF = numeric_limits<int>::max();

    PrimResult result;
    vector<bool> inTree(graph.size(), false);
    vector<int> bestWeight(graph.size(), INF);
    vector<int> bestParent(graph.size(), -1);

    // (weight, vertex) pairs; greater<> makes this a min-heap.
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pending;

    bestWeight[start] = 0;
    pending.push({0, start});

    while (!pending.empty()) {
        auto [weight, vertex] = pending.top();
        pending.pop();

        if (inTree[vertex] || weight != bestWeight[vertex]) continue;

        inTree[vertex] = true;
        if (bestParent[vertex] != -1) {
            result.totalWeight += weight;
            result.edges.push_back({bestParent[vertex], vertex, weight});
        }

        for (const Edge& edge : graph.neighbors(vertex)) {
            if (!inTree[edge.to] && edge.weight < bestWeight[edge.to]) {
                bestWeight[edge.to] = edge.weight;
                bestParent[edge.to] = vertex;
                pending.push({edge.weight, edge.to});
            }
        }
    }

    for (bool visited : inTree) {
        if (!visited) result.connected = false;
    }

    return result;
}

int main() {
    // Same graph as kruskal_mst.cpp, so the total weight must match (16).
    Graph graph(6, false);
    graph.addEdge(0, 1, 4);
    graph.addEdge(0, 2, 4);
    graph.addEdge(1, 2, 2);
    graph.addEdge(1, 3, 5);
    graph.addEdge(2, 3, 8);
    graph.addEdge(2, 4, 10);
    graph.addEdge(3, 4, 2);
    graph.addEdge(3, 5, 6);
    graph.addEdge(4, 5, 3);

    PrimResult result = primMst(graph, 0);
    cout << "Prim MST edges:\n";
    for (const WeightedEdge& edge : result.edges) {
        cout << "  " << edge.from << " -- " << edge.to
             << " == " << edge.weight << '\n';
    }
    cout << "Total weight: " << result.totalWeight << '\n';
    cout << "Graph connected: " << (result.connected ? "yes" : "no") << '\n';

    return 0;
}
