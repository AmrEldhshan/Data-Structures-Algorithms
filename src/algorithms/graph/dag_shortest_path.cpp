#include "data_structures/graph/graph.h"

#include <algorithm>
#include <iostream>
#include <limits>
#include <queue>
#include <stdexcept>
#include <vector>

using namespace std;

// ---------------------------------------------------------------------------
// Shortest paths in a DAG
//
// A topological order guarantees that when we reach a vertex, every path into
// it has already been considered. Relax the outgoing edges in that order.
//
// Time:  O(V + E)
// Space: O(V)
// ---------------------------------------------------------------------------
vector<int> dagShortestPaths(const Graph& graph, int source) {
    const int INF = numeric_limits<int>::max() / 4;

    vector<int> inDegree(graph.size(), 0);
    for (const WeightedEdge& edge : graph.edgeList()) ++inDegree[edge.to];

    queue<int> ready;
    for (int vertex = 0; vertex < graph.size(); ++vertex) {
        if (inDegree[vertex] == 0) ready.push(vertex);
    }

    vector<int> order;
    while (!ready.empty()) {
        int current = ready.front();
        ready.pop();
        order.push_back(current);

        for (const Edge& edge : graph.neighbors(current)) {
            if (--inDegree[edge.to] == 0) ready.push(edge.to);
        }
    }

    if (static_cast<int>(order.size()) != graph.size()) {
        throw runtime_error("dagShortestPaths: graph contains a cycle");
    }

    vector<int> distance(graph.size(), INF);
    distance[source] = 0;

    for (int vertex : order) {
        if (distance[vertex] == INF) continue;

        for (const Edge& edge : graph.neighbors(vertex)) {
            distance[edge.to] = min(distance[edge.to],
                                    distance[vertex] + edge.weight);
        }
    }

    return distance;
}

int main() {
    // DAG:
    //   0 -> 1 (5), 0 -> 2 (3)
    //   1 -> 3 (6), 1 -> 2 (2)
    //   2 -> 3 (7), 2 -> 4 (4), 2 -> 5 (2)
    //   3 -> 4 (-1), 3 -> 5 (1)
    //   4 -> 5 (-2)
    Graph graph(6, true);
    graph.addEdge(0, 1, 5);
    graph.addEdge(0, 2, 3);
    graph.addEdge(1, 3, 6);
    graph.addEdge(1, 2, 2);
    graph.addEdge(2, 3, 7);
    graph.addEdge(2, 4, 4);
    graph.addEdge(2, 5, 2);
    graph.addEdge(3, 4, -1);
    graph.addEdge(3, 5, 1);
    graph.addEdge(4, 5, -2);

    vector<int> distance = dagShortestPaths(graph, 0);
    cout << "DAG shortest distances from 0:\n";
    for (int vertex = 0; vertex < graph.size(); ++vertex) {
        cout << "  " << vertex << " : " << distance[vertex] << '\n';
    }

    return 0;
}
