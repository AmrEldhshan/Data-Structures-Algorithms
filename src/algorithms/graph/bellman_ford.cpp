#include "data_structures/graph/graph.h"

#include <iostream>
#include <limits>
#include <vector>

using namespace std;

// ---------------------------------------------------------------------------
// Bellman-Ford
//
// Single-source shortest paths that also works with negative edge weights.
// Relax every edge V - 1 times. If an edge can still be relaxed afterwards,
// a negative cycle is reachable from the source and distances are undefined.
//
// Time:  O(V * E)
// Space: O(V)
// ---------------------------------------------------------------------------
struct BellmanFordResult {
    vector<int> distance;
    vector<int> parent;
    bool hasNegativeCycle = false;
};

BellmanFordResult bellmanFord(const Graph& graph, int source) {
    const int INF = numeric_limits<int>::max() / 4;

    BellmanFordResult result;
    result.distance.assign(graph.size(), INF);
    result.parent.assign(graph.size(), -1);
    result.distance[source] = 0;

    for (int round = 0; round < graph.size() - 1; ++round) {
        bool changed = false;

        for (const WeightedEdge& edge : graph.edgeList()) {
            if (result.distance[edge.from] == INF) continue;

            int candidate = result.distance[edge.from] + edge.weight;
            if (candidate < result.distance[edge.to]) {
                result.distance[edge.to] = candidate;
                result.parent[edge.to] = edge.from;
                changed = true;
            }
        }

        // No relaxation in a full pass means we are already done.
        if (!changed) break;
    }

    for (const WeightedEdge& edge : graph.edgeList()) {
        if (result.distance[edge.from] == INF) continue;
        if (result.distance[edge.from] + edge.weight < result.distance[edge.to]) {
            result.hasNegativeCycle = true;
            break;
        }
    }

    return result;
}

void printPath(const vector<int>& parent, int target) {
    if (target == -1) {
        cout << "(unreachable)";
        return;
    }
    if (parent[target] != -1) {
        printPath(parent, parent[target]);
        cout << " -> ";
    }
    cout << target;
}

int main() {
    // Directed graph with a negative edge, but no negative cycle.
    Graph graph(5, true);
    graph.addEdge(0, 1, 6);
    graph.addEdge(0, 2, 7);
    graph.addEdge(1, 2, 8);
    graph.addEdge(1, 3, 5);
    graph.addEdge(1, 4, -4);
    graph.addEdge(2, 3, -3);
    graph.addEdge(2, 4, 9);
    graph.addEdge(3, 1, -2);
    graph.addEdge(4, 3, 7);

    BellmanFordResult result = bellmanFord(graph, 0);
    cout << "Shortest distances from 0:\n";
    for (int vertex = 0; vertex < graph.size(); ++vertex) {
        cout << "  " << vertex << " : " << result.distance[vertex]
             << "   path: ";
        if (result.distance[vertex] == numeric_limits<int>::max() / 4) {
            cout << "(unreachable)";
        } else {
            printPath(result.parent, vertex);
        }
        cout << '\n';
    }
    cout << "Negative cycle: "
         << (result.hasNegativeCycle ? "yes" : "no") << '\n';

    // Add 3 -> 0 with a large negative weight to create a cycle
    // 0 -> 2 -> 3 -> 0 with total weight 7 - 3 - 10 = -6.
    graph.addEdge(3, 0, -10);
    BellmanFordResult cyclic = bellmanFord(graph, 0);
    cout << "\nAfter adding 3 -> 0 (-10):\n";
    cout << "Negative cycle: "
         << (cyclic.hasNegativeCycle ? "yes" : "no") << '\n';

    return 0;
}
