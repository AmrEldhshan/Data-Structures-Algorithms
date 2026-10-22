#include "data_structures/graph/graph.h"

#include <iomanip>
#include <iostream>
#include <limits>
#include <vector>

using namespace std;

// ---------------------------------------------------------------------------
// Floyd-Warshall
//
// All-pairs shortest paths. For every possible intermediate vertex k, relax
// every pair (i, j): if i -> k -> j is cheaper than i -> j, use it.
//
// Works with negative edges. A negative value on the diagonal means a
// negative cycle exists.
//
// Time:  O(V^3)
// Space: O(V^2)
// ---------------------------------------------------------------------------
vector<vector<int>> floydWarshall(const Graph& graph) {
    const int INF = numeric_limits<int>::max() / 4;

    vector<vector<int>> distance(graph.size(), vector<int>(graph.size(), INF));
    for (int vertex = 0; vertex < graph.size(); ++vertex) {
        distance[vertex][vertex] = 0;
    }

    for (const WeightedEdge& edge : graph.edgeList()) {
        // Keep the cheapest edge when the input contains parallel edges.
        distance[edge.from][edge.to] =
            min(distance[edge.from][edge.to], edge.weight);
    }

    for (int k = 0; k < graph.size(); ++k) {
        for (int i = 0; i < graph.size(); ++i) {
            if (distance[i][k] == INF) continue;
            for (int j = 0; j < graph.size(); ++j) {
                if (distance[k][j] == INF) continue;
                int candidate = distance[i][k] + distance[k][j];
                if (candidate < distance[i][j]) {
                    distance[i][j] = candidate;
                }
            }
        }
    }

    return distance;
}

int main() {
    Graph graph(4, true);
    graph.addEdge(0, 1, 3);
    graph.addEdge(0, 3, 7);
    graph.addEdge(1, 0, 8);
    graph.addEdge(1, 2, 2);
    graph.addEdge(2, 0, 5);
    graph.addEdge(2, 3, 1);
    graph.addEdge(3, 0, 2);

    vector<vector<int>> distance = floydWarshall(graph);
    const int INF = numeric_limits<int>::max() / 4;

    cout << "All-pairs shortest distances (INF = unreachable):\n";
    cout << "      ";
    for (int j = 0; j < graph.size(); ++j) cout << setw(5) << j;
    cout << '\n';

    for (int i = 0; i < graph.size(); ++i) {
        cout << "  " << i << " : ";
        for (int j = 0; j < graph.size(); ++j) {
            if (distance[i][j] == INF) {
                cout << setw(5) << "INF";
            } else {
                cout << setw(5) << distance[i][j];
            }
        }
        cout << '\n';
    }

    return 0;
}
