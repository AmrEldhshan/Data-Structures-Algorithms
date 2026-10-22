#include "data_structures/graph/graph.h"

#include <iostream>
#include <stack>
#include <vector>

using namespace std;

// ---------------------------------------------------------------------------
// Depth-First Search (DFS)
//
// DFS follows one branch as far as possible before backing up. The recursive
// version is the easiest to read; the iterative version shows what the call
// stack is doing explicitly.
//
// Time:  O(V + E)
// Space: O(V)
// ---------------------------------------------------------------------------
void dfsVisit(const Graph& graph, int vertex, vector<bool>& visited,
              vector<int>& order) {
    visited[vertex] = true;
    order.push_back(vertex);

    for (const Edge& edge : graph.neighbors(vertex)) {
        if (!visited[edge.to]) {
            dfsVisit(graph, edge.to, visited, order);
        }
    }
}

vector<int> dfsRecursive(const Graph& graph, int start) {
    vector<bool> visited(graph.size(), false);
    vector<int> order;
    dfsVisit(graph, start, visited, order);
    return order;
}

vector<int> dfsIterative(const Graph& graph, int start) {
    vector<bool> visited(graph.size(), false);
    vector<int> order;
    stack<int> pending;

    pending.push(start);

    while (!pending.empty()) {
        int current = pending.top();
        pending.pop();

        if (visited[current]) continue;
        visited[current] = true;
        order.push_back(current);

        // Push neighbours in reverse so the smallest one is explored first
        // (the stack is LIFO).
        const vector<Edge>& neighbours = graph.neighbors(current);
        for (auto it = neighbours.rbegin(); it != neighbours.rend(); ++it) {
            if (!visited[it->to]) pending.push(it->to);
        }
    }

    return order;
}

// Discovery and finish times are useful for cycle detection, topological
// sorting, and strongly connected components.
struct DfsTimes {
    vector<int> discovery;
    vector<int> finish;
};

void timeVisit(const Graph& graph, int vertex, int& timer,
               vector<bool>& visited, DfsTimes& times) {
    visited[vertex] = true;
    times.discovery[vertex] = ++timer;

    for (const Edge& edge : graph.neighbors(vertex)) {
        if (!visited[edge.to]) {
            timeVisit(graph, edge.to, timer, visited, times);
        }
    }

    times.finish[vertex] = ++timer;
}

DfsTimes dfsTimes(const Graph& graph, int start) {
    DfsTimes times;
    times.discovery.assign(graph.size(), 0);
    times.finish.assign(graph.size(), 0);

    vector<bool> visited(graph.size(), false);
    int timer = 0;
    timeVisit(graph, start, timer, visited, times);
    return times;
}

int main() {
    // Undirected graph with two branches.
    Graph graph(6, false);
    graph.addEdge(0, 1);
    graph.addEdge(0, 2);
    graph.addEdge(1, 3);
    graph.addEdge(1, 4);
    graph.addEdge(2, 5);

    cout << "Recursive DFS from 0: ";
    for (int vertex : dfsRecursive(graph, 0)) cout << vertex << ' ';
    cout << '\n';

    cout << "Iterative DFS from 0: ";
    for (int vertex : dfsIterative(graph, 0)) cout << vertex << ' ';
    cout << '\n';

    DfsTimes times = dfsTimes(graph, 0);
    cout << "\nvertex  discovery  finish\n";
    for (int vertex = 0; vertex < graph.size(); ++vertex) {
        cout << "  " << vertex << "        " << times.discovery[vertex]
             << "        " << times.finish[vertex] << '\n';
    }

    // An edge to an already visited vertex that is not the parent means the
    // undirected graph contains a cycle. This is the same idea used in
    // cycle_detection.cpp.
    cout << "\nNote: discovery/finish times make the DFS tree visible.\n";

    return 0;
}
