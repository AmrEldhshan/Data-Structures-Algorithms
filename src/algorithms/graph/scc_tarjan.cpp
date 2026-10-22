#include "data_structures/graph/graph.h"

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

// ---------------------------------------------------------------------------
// Strongly connected components (Tarjan's algorithm)
//
// In a directed graph, u and v are strongly connected when u can reach v and
// v can reach u. Tarjan finds every maximal such group in one DFS pass.
//
// Key arrays:
//   discovery[v] : DFS discovery time
//   low[v]       : smallest discovery time reachable from v's DFS subtree
//   onStack[v]   : v is currently on the Tarjan stack
//
// When low[v] == discovery[v], v is the root of an SCC. Pop the stack until v.
//
// Time:  O(V + E)
// Space: O(V)
// ---------------------------------------------------------------------------
struct TarjanState {
    int timer = 0;
    vector<int> discovery;
    vector<int> low;
    vector<bool> onStack;
    vector<int> stack;
    vector<vector<int>> components;
};

void tarjanDfs(const Graph& graph, int vertex, TarjanState& state) {
    state.discovery[vertex] = state.low[vertex] = ++state.timer;
    state.stack.push_back(vertex);
    state.onStack[vertex] = true;

    for (const Edge& edge : graph.neighbors(vertex)) {
        if (state.discovery[edge.to] == 0) {
            tarjanDfs(graph, edge.to, state);
            state.low[vertex] = min(state.low[vertex], state.low[edge.to]);
        } else if (state.onStack[edge.to]) {
            state.low[vertex] = min(state.low[vertex], state.discovery[edge.to]);
        }
    }

    if (state.low[vertex] == state.discovery[vertex]) {
        vector<int> component;
        while (true) {
            int top = state.stack.back();
            state.stack.pop_back();
            state.onStack[top] = false;
            component.push_back(top);
            if (top == vertex) break;
        }
        sort(component.begin(), component.end());
        state.components.push_back(component);
    }
}

vector<vector<int>> stronglyConnectedComponents(const Graph& graph) {
    TarjanState state;
    state.discovery.assign(graph.size(), 0);
    state.low.assign(graph.size(), 0);
    state.onStack.assign(graph.size(), false);

    for (int vertex = 0; vertex < graph.size(); ++vertex) {
        if (state.discovery[vertex] == 0) tarjanDfs(graph, vertex, state);
    }

    return state.components;
}

int main() {
    // 0 -> 1 -> 2 -> 0 is one SCC.
    // 3 -> 4 -> 3 is another.
    // 2 -> 3 links them without merging them.
    Graph graph(5, true);
    graph.addEdge(0, 1);
    graph.addEdge(1, 2);
    graph.addEdge(2, 0);
    graph.addEdge(2, 3);
    graph.addEdge(3, 4);
    graph.addEdge(4, 3);

    vector<vector<int>> components = stronglyConnectedComponents(graph);
    cout << "Strongly connected components:\n";
    for (const vector<int>& component : components) {
        cout << "  { ";
        for (int vertex : component) cout << vertex << ' ';
        cout << "}\n";
    }

    return 0;
}
