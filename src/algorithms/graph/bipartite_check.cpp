#include "data_structures/graph/graph.h"

#include <iostream>
#include <queue>
#include <vector>

using namespace std;

// ---------------------------------------------------------------------------
// Bipartite check (2-colouring)
//
// A graph is bipartite when its vertices can be split into two groups so that
// every edge goes between the groups. BFS colours each neighbour with the
// opposite colour. Meeting a neighbour with the same colour is a conflict.
//
// A graph is bipartite exactly when it has no odd-length cycle.
//
// Time:  O(V + E)
// ---------------------------------------------------------------------------
struct BipartiteResult {
    bool bipartite = true;
    vector<int> colour; // -1 = uncoloured, 0 / 1 = the two sides
};

BipartiteResult checkBipartite(const Graph& graph) {
    BipartiteResult result;
    result.colour.assign(graph.size(), -1);

    for (int start = 0; start < graph.size(); ++start) {
        if (result.colour[start] != -1) continue;

        queue<int> pending;
        result.colour[start] = 0;
        pending.push(start);

        while (!pending.empty()) {
            int current = pending.front();
            pending.pop();

            for (const Edge& edge : graph.neighbors(current)) {
                if (result.colour[edge.to] == -1) {
                    result.colour[edge.to] = result.colour[current] ^ 1;
                    pending.push(edge.to);
                } else if (result.colour[edge.to] == result.colour[current]) {
                    result.bipartite = false;
                    return result;
                }
            }
        }
    }

    return result;
}

int main() {
    // A 4-cycle is bipartite: 0--1--2--3--0.
    Graph evenCycle(4, false);
    evenCycle.addEdge(0, 1);
    evenCycle.addEdge(1, 2);
    evenCycle.addEdge(2, 3);
    evenCycle.addEdge(3, 0);

    BipartiteResult first = checkBipartite(evenCycle);
    cout << "4-cycle bipartite: " << (first.bipartite ? "yes" : "no") << '\n';
    cout << "Colours: ";
    for (int colour : first.colour) cout << colour << ' ';
    cout << '\n';

    // A triangle is not bipartite.
    Graph triangle(3, false);
    triangle.addEdge(0, 1);
    triangle.addEdge(1, 2);
    triangle.addEdge(2, 0);

    BipartiteResult second = checkBipartite(triangle);
    cout << "\nTriangle bipartite: " << (second.bipartite ? "yes" : "no")
         << '\n';

    return 0;
}
