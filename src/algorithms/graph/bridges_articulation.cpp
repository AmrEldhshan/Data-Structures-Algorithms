#include "data_structures/graph/graph.h"

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

// ---------------------------------------------------------------------------
// Bridges and articulation points (undirected graph)
//
// discovery[v] : time when v was first visited
// low[v]       : earliest discovery time reachable from v's subtree using at
//                most one back edge
//
// For a tree edge (u, v):
//   - low[v] > discovery[u]  =>  (u, v) is a bridge
//   - low[v] >= discovery[u] =>  u is an articulation point
// The DFS root is an articulation point only if it has more than one child.
//
// Time:  O(V + E)
// ---------------------------------------------------------------------------
struct CriticalResult {
    vector<WeightedEdge> bridges;
    vector<int> articulationPoints;
};

struct CriticalState {
    int timer = 0;
    vector<int> discovery;
    vector<int> low;
    vector<int> parent;
    vector<bool> isArticulation;
};

void criticalDfs(const Graph& graph, int vertex, CriticalState& state,
                 CriticalResult& result) {
    state.discovery[vertex] = state.low[vertex] = ++state.timer;
    int children = 0;

    for (const Edge& edge : graph.neighbors(vertex)) {
        if (edge.to == state.parent[vertex]) continue;

        if (state.discovery[edge.to] == 0) {
            ++children;
            state.parent[edge.to] = vertex;
            criticalDfs(graph, edge.to, state, result);

            state.low[vertex] = min(state.low[vertex], state.low[edge.to]);

            if (state.low[edge.to] > state.discovery[vertex]) {
                result.bridges.push_back({vertex, edge.to, 1});
            }

            if (state.parent[vertex] != -1 &&
                state.low[edge.to] >= state.discovery[vertex]) {
                state.isArticulation[vertex] = true;
            }
        } else {
            // Back edge: use the neighbour's discovery time.
            state.low[vertex] = min(state.low[vertex], state.discovery[edge.to]);
        }
    }

    if (state.parent[vertex] == -1 && children > 1) {
        state.isArticulation[vertex] = true;
    }
}

CriticalResult findCriticalParts(const Graph& graph) {
    CriticalState state;
    state.discovery.assign(graph.size(), 0);
    state.low.assign(graph.size(), 0);
    state.parent.assign(graph.size(), -1);
    state.isArticulation.assign(graph.size(), false);

    CriticalResult result;

    for (int vertex = 0; vertex < graph.size(); ++vertex) {
        if (state.discovery[vertex] == 0) criticalDfs(graph, vertex, state, result);
    }

    for (int vertex = 0; vertex < graph.size(); ++vertex) {
        if (state.isArticulation[vertex]) result.articulationPoints.push_back(vertex);
    }

    return result;
}

int main() {
    // Classic example:
    //
    //   0 -- 1 -- 2 -- 3
    //        |         |
    //        +----4----+
    //             |
    //             5
    //
    // 1 and 4 are articulation points; 0--1 and 4--5 are bridges.
    Graph graph(6, false);
    graph.addEdge(0, 1);
    graph.addEdge(1, 2);
    graph.addEdge(2, 3);
    graph.addEdge(1, 4);
    graph.addEdge(4, 3);
    graph.addEdge(4, 5);

    CriticalResult result = findCriticalParts(graph);

    cout << "Bridges: ";
    for (const WeightedEdge& edge : result.bridges) {
        cout << edge.from << "--" << edge.to << ' ';
    }
    cout << "\nArticulation points: ";
    for (int vertex : result.articulationPoints) cout << vertex << ' ';
    cout << '\n';

    return 0;
}
