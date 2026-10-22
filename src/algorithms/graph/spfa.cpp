#include "data_structures/graph/graph.h"

#include <iostream>
#include <limits>
#include <queue>
#include <vector>

using namespace std;

// ---------------------------------------------------------------------------
// SPFA (Shortest Path Faster Algorithm)
//
// A queue-based version of Bellman-Ford. Only vertices whose distance changed
// are put back in the queue, so it is often much faster than V * E in practice.
// If a vertex is relaxed V times, a negative cycle is reachable.
//
// Worst case: O(V * E) (same as Bellman-Ford)
// Typical:    much faster
// ---------------------------------------------------------------------------
struct SpfaResult {
    vector<int> distance;
    vector<int> parent;
    bool hasNegativeCycle = false;
};

SpfaResult spfa(const Graph& graph, int source) {
    const int INF = numeric_limits<int>::max() / 4;

    SpfaResult result;
    result.distance.assign(graph.size(), INF);
    result.parent.assign(graph.size(), -1);
    result.distance[source] = 0;

    queue<int> pending;
    vector<bool> inQueue(graph.size(), false);
    vector<int> relaxations(graph.size(), 0);

    pending.push(source);
    inQueue[source] = true;

    while (!pending.empty()) {
        int current = pending.front();
        pending.pop();
        inQueue[current] = false;

        for (const Edge& edge : graph.neighbors(current)) {
            if (result.distance[current] == INF) continue;

            int candidate = result.distance[current] + edge.weight;
            if (candidate >= result.distance[edge.to]) continue;

            result.distance[edge.to] = candidate;
            result.parent[edge.to] = current;

            if (++relaxations[edge.to] >= graph.size()) {
                result.hasNegativeCycle = true;
                return result;
            }

            if (!inQueue[edge.to]) {
                pending.push(edge.to);
                inQueue[edge.to] = true;
            }
        }
    }

    return result;
}

int main() {
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

    SpfaResult result = spfa(graph, 0);
    cout << "SPFA distances from 0:\n";
    for (int vertex = 0; vertex < graph.size(); ++vertex) {
        cout << "  " << vertex << " : " << result.distance[vertex] << '\n';
    }

    graph.addEdge(3, 0, -10);
    cout << "\nafter adding a negative cycle: "
         << (spfa(graph, 0).hasNegativeCycle ? "detected" : "not detected")
         << '\n';

    return 0;
}
