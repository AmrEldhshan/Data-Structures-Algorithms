#include "data_structures/graph/graph.h"

#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

// ---------------------------------------------------------------------------
// Connected components (undirected graph)
//
// Two vertices are in the same component when a path connects them. A simple
// BFS/DFS from every unvisited vertex labels one whole component per start.
//
// Time:  O(V + E)
// Space: O(V)
// ---------------------------------------------------------------------------
vector<int> connectedComponents(const Graph& graph) {
    vector<int> component(graph.size(), -1);
    int nextId = 0;

    for (int start = 0; start < graph.size(); ++start) {
        if (component[start] != -1) continue;

        queue<int> pending;
        component[start] = nextId;
        pending.push(start);

        while (!pending.empty()) {
            int current = pending.front();
            pending.pop();

            for (const Edge& edge : graph.neighbors(current)) {
                if (component[edge.to] == -1) {
                    component[edge.to] = nextId;
                    pending.push(edge.to);
                }
            }
        }

        ++nextId;
    }

    return component;
}

int main() {
    // Three separate pieces:
    //   {0, 1, 2}   {3, 4}   {5, 6, 7}
    Graph graph(8, false);
    graph.addEdge(0, 1);
    graph.addEdge(1, 2);
    graph.addEdge(0, 2);
    graph.addEdge(3, 4);
    graph.addEdge(5, 6);
    graph.addEdge(6, 7);

    vector<int> component = connectedComponents(graph);
    int count = 0;
    for (int id : component) count = max(count, id + 1);

    cout << "Number of components: " << count << "\n\n";
    for (int id = 0; id < count; ++id) {
        cout << "Component " << id << ": ";
        for (int vertex = 0; vertex < graph.size(); ++vertex) {
            if (component[vertex] == id) cout << vertex << ' ';
        }
        cout << '\n';
    }

    return 0;
}
