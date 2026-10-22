#include "data_structures/graph/graph.h"

#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

// ---------------------------------------------------------------------------
// Breadth-First Search (BFS)
//
// Explore the graph level by level starting at `source`. BFS is the natural
// choice when every edge has the same cost (or no cost), because the first
// time a vertex is reached it is reached by a shortest path in edge count.
//
// Time:  O(V + E)
// Space: O(V)
// ---------------------------------------------------------------------------
vector<int> bfsDistances(const Graph& graph, int source) {
    vector<int> distance(graph.size(), -1);
    queue<int> pending;

    distance[source] = 0;
    pending.push(source);

    while (!pending.empty()) {
        int current = pending.front();
        pending.pop();

        for (const Edge& edge : graph.neighbors(current)) {
            if (distance[edge.to] == -1) {
                distance[edge.to] = distance[current] + 1;
                pending.push(edge.to);
            }
        }
    }

    return distance;
}

// Reconstruct one shortest path from `source` to `target`.
// Returns an empty vector when `target` is unreachable.
vector<int> bfsPath(const Graph& graph, int source, int target) {
    vector<int> parent(graph.size(), -1);
    vector<bool> visited(graph.size(), false);
    queue<int> pending;

    visited[source] = true;
    pending.push(source);

    while (!pending.empty()) {
        int current = pending.front();
        pending.pop();

        if (current == target) break;

        for (const Edge& edge : graph.neighbors(current)) {
            if (!visited[edge.to]) {
                visited[edge.to] = true;
                parent[edge.to] = current;
                pending.push(edge.to);
            }
        }
    }

    if (!visited[target]) return {};

    vector<int> path;
    for (int vertex = target; vertex != -1; vertex = parent[vertex]) {
        path.push_back(vertex);
    }
    reverse(path.begin(), path.end());
    return path;
}

int main() {
    /* Undirected graph:
     *
     *        0
     *       / \
     *      1   2
     *     / \   \
     *    3   4   5
     *    |
     *    6
     */
    Graph graph(7, false);
    graph.addEdge(0, 1);
    graph.addEdge(0, 2);
    graph.addEdge(1, 3);
    graph.addEdge(1, 4);
    graph.addEdge(2, 5);
    graph.addEdge(3, 6);

    vector<int> distance = bfsDistances(graph, 0);
    cout << "BFS distances from vertex 0:\n";
    for (int vertex = 0; vertex < graph.size(); ++vertex) {
        cout << "  " << vertex << " : " << distance[vertex] << '\n';
    }

    vector<int> path = bfsPath(graph, 0, 6);
    cout << "\nShortest path 0 -> 6: ";
    for (size_t i = 0; i < path.size(); ++i) {
        if (i != 0) cout << " -> ";
        cout << path[i];
    }
    cout << '\n';

    // BFS also finds connected components in an undirected graph. Every
    // unvisited vertex starts a new component.
    vector<bool> visited(graph.size(), false);
    int components = 0;
    for (int start = 0; start < graph.size(); ++start) {
        if (visited[start]) continue;
        ++components;

        queue<int> pending;
        visited[start] = true;
        pending.push(start);
        while (!pending.empty()) {
            int current = pending.front();
            pending.pop();
            for (const Edge& edge : graph.neighbors(current)) {
                if (!visited[edge.to]) {
                    visited[edge.to] = true;
                    pending.push(edge.to);
                }
            }
        }
    }
    cout << "Connected components: " << components << '\n';

    return 0;
}
