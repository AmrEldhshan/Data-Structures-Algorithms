#include "data_structures/graph/graph.h"

#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

// ---------------------------------------------------------------------------
// Topological sort
//
// A topological order lists the vertices of a directed acyclic graph (DAG)
// so that every edge u -> v has u before v. It is used for dependency
// ordering: build systems, course prerequisites, task scheduling, ...
//
// Two classic implementations are shown:
//   1. Kahn's algorithm (repeatedly remove a vertex with in-degree 0)
//   2. DFS post-order (reverse the finishing order)
//
// Time: O(V + E) for both.
// ---------------------------------------------------------------------------
vector<int> topologicalSortKahn(const Graph& graph) {
    vector<int> inDegree(graph.size(), 0);
    for (const WeightedEdge& edge : graph.edgeList()) {
        ++inDegree[edge.to];
    }

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
            if (--inDegree[edge.to] == 0) {
                ready.push(edge.to);
            }
        }
    }

    // A DAG contains all vertices in the order. If some are left over, the
    // graph has a cycle and no topological order exists.
    if (static_cast<int>(order.size()) != graph.size()) return {};
    return order;
}

void topoDfsVisit(const Graph& graph, int vertex, vector<bool>& visited,
                  vector<int>& order) {
    visited[vertex] = true;
    for (const Edge& edge : graph.neighbors(vertex)) {
        if (!visited[edge.to]) topoDfsVisit(graph, edge.to, visited, order);
    }
    order.push_back(vertex);
}

vector<int> topologicalSortDfs(const Graph& graph) {
    vector<bool> visited(graph.size(), false);
    vector<int> order;

    for (int vertex = 0; vertex < graph.size(); ++vertex) {
        if (!visited[vertex]) topoDfsVisit(graph, vertex, visited, order);
    }

    reverse(order.begin(), order.end());
    return order;
}

void printOrder(const string& label, const vector<int>& order) {
    cout << label;
    if (order.empty()) {
        cout << "(cycle detected - no topological order)\n";
        return;
    }
    for (int vertex : order) cout << vertex << ' ';
    cout << '\n';
}

int main() {
    // Course prerequisites: 5 -> 2, 5 -> 0, 4 -> 0, 4 -> 1,
    // 2 -> 3, 3 -> 1.
    Graph graph(6, true);
    graph.addEdge(5, 2);
    graph.addEdge(5, 0);
    graph.addEdge(4, 0);
    graph.addEdge(4, 1);
    graph.addEdge(2, 3);
    graph.addEdge(3, 1);

    printOrder("Kahn:   ", topologicalSortKahn(graph));
    printOrder("DFS:    ", topologicalSortDfs(graph));

    // Add 1 -> 5 to create a cycle. Both algorithms must refuse.
    graph.addEdge(1, 5);
    printOrder("Cyclic: ", topologicalSortKahn(graph));

    return 0;
}
