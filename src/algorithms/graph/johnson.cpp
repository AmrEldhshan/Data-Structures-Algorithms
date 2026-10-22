#include "data_structures/graph/graph.h"

#include <functional>
#include <iostream>
#include <limits>
#include <queue>
#include <stdexcept>
#include <utility>
#include <vector>

using namespace std;

// ---------------------------------------------------------------------------
// Johnson's algorithm (all-pairs shortest paths)
//
// Dijkstra needs non-negative weights. Johnson reweights every edge with
// potential values h[v] from one Bellman-Ford run:
//
//   w'(u, v) = w(u, v) + h[u] - h[v]
//
// A virtual source with a 0-weight edge to every vertex computes h so that all
// reweighted edges are non-negative. After running Dijkstra from every vertex,
// convert the distances back:
//
//   dist(u, v) = dist'(u, v) - h[u] + h[v]
//
// Time:  O(V * E + V * (V + E) log V)  (Bellman-Ford + V Dijkstras)
// Space: O(V²)
// ---------------------------------------------------------------------------
const int INF = numeric_limits<int>::max() / 4;

vector<int> bellmanFordPotentials(const Graph& graph) {
    int n = graph.size();
    vector<int> h(n, 0); // virtual source connects to everyone with weight 0

    for (int iteration = 0; iteration < n; ++iteration) {
        bool changed = false;

        for (const WeightedEdge& edge : graph.edgeList()) {
            if (h[edge.from] == INF) continue;
            if (h[edge.from] + edge.weight < h[edge.to]) {
                h[edge.to] = h[edge.from] + edge.weight;
                changed = true;
            }
        }

        if (!changed) break;
        if (iteration == n - 1) {
            throw runtime_error("Johnson: negative cycle detected");
        }
    }

    return h;
}

vector<vector<int>> johnson(const Graph& graph) {
    int n = graph.size();
    vector<int> h = bellmanFordPotentials(graph);
    vector<vector<int>> allPairs(n, vector<int>(n, INF));

    for (int source = 0; source < n; ++source) {
        vector<int> distance(n, INF);
        distance[source] = 0;

        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> open;
        open.push({0, source});

        while (!open.empty()) {
            auto [currentDistance, vertex] = open.top();
            open.pop();

            if (currentDistance != distance[vertex]) continue;

            for (const Edge& edge : graph.neighbors(vertex)) {
                int reweighted = edge.weight + h[vertex] - h[edge.to];
                int candidate = currentDistance + reweighted;

                if (candidate < distance[edge.to]) {
                    distance[edge.to] = candidate;
                    open.push({candidate, edge.to});
                }
            }
        }

        for (int target = 0; target < n; ++target) {
            if (distance[target] == INF) continue;
            allPairs[source][target] =
                distance[target] - h[source] + h[target];
        }
    }

    return allPairs;
}

int main() {
    Graph graph(4, true);
    graph.addEdge(0, 1, 3);
    graph.addEdge(0, 2, 8);
    graph.addEdge(0, 3, -4);
    graph.addEdge(1, 3, 7);
    graph.addEdge(1, 2, 4);
    graph.addEdge(2, 0, 2);
    graph.addEdge(2, 3, -5);
    graph.addEdge(3, 1, 6);

    vector<vector<int>> distance = johnson(graph);

    cout << "Johnson all-pairs shortest paths:\n";
    for (int source = 0; source < graph.size(); ++source) {
        cout << "from " << source << ": ";
        for (int target = 0; target < graph.size(); ++target) {
            if (distance[source][target] == INF) {
                cout << "INF ";
            } else {
                cout << distance[source][target] << ' ';
            }
        }
        cout << '\n';
    }

    return 0;
}
