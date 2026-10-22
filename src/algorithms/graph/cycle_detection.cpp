#include "data_structures/graph/graph.h"

#include <iostream>
#include <vector>

using namespace std;

// ---------------------------------------------------------------------------
// Cycle detection
//
// Directed graph: three colours
//   0 = unvisited, 1 = on the current DFS path, 2 = completely processed
// An edge to a vertex that is still "on the path" closes a directed cycle.
//
// Undirected graph: run DFS and ignore the edge back to the parent. Any other
// edge to an already visited vertex closes a cycle.
//
// Time: O(V + E)
// ---------------------------------------------------------------------------
bool directedCycleVisit(const Graph& graph, int vertex, vector<int>& colour) {
    colour[vertex] = 1;

    for (const Edge& edge : graph.neighbors(vertex)) {
        if (colour[edge.to] == 1) return true;
        if (colour[edge.to] == 0 && directedCycleVisit(graph, edge.to, colour)) {
            return true;
        }
    }

    colour[vertex] = 2;
    return false;
}

bool hasDirectedCycle(const Graph& graph) {
    vector<int> colour(graph.size(), 0);
    for (int vertex = 0; vertex < graph.size(); ++vertex) {
        if (colour[vertex] == 0 && directedCycleVisit(graph, vertex, colour)) {
            return true;
        }
    }
    return false;
}

bool undirectedCycleVisit(const Graph& graph, int vertex, int parent,
                          vector<bool>& visited) {
    visited[vertex] = true;

    for (const Edge& edge : graph.neighbors(vertex)) {
        if (edge.to == parent) continue;
        if (visited[edge.to]) return true;
        if (undirectedCycleVisit(graph, edge.to, vertex, visited)) return true;
    }

    return false;
}

bool hasUndirectedCycle(const Graph& graph) {
    vector<bool> visited(graph.size(), false);
    for (int vertex = 0; vertex < graph.size(); ++vertex) {
        if (!visited[vertex] && undirectedCycleVisit(graph, vertex, -1, visited)) {
            return true;
        }
    }
    return false;
}

int main() {
    Graph directed(4, true);
    directed.addEdge(0, 1);
    directed.addEdge(1, 2);
    directed.addEdge(2, 3);
    cout << "Directed DAG has cycle:      "
         << (hasDirectedCycle(directed) ? "yes" : "no") << '\n';

    directed.addEdge(3, 1);
    cout << "After adding 3 -> 1:         "
         << (hasDirectedCycle(directed) ? "yes" : "no") << '\n';

    Graph undirected(4, false);
    undirected.addEdge(0, 1);
    undirected.addEdge(1, 2);
    undirected.addEdge(2, 3);
    cout << "\nUndirected tree has cycle:   "
         << (hasUndirectedCycle(undirected) ? "yes" : "no") << '\n';

    undirected.addEdge(3, 0);
    cout << "After adding 3 -- 0:         "
         << (hasUndirectedCycle(undirected) ? "yes" : "no") << '\n';

    return 0;
}
