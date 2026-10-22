#include <iostream>     // For input/output (cout, endl)
#include <vector>       // For dynamic arrays (adjacency list)
#include <queue>        // For priority_queue used in Dijkstra
#include <climits>      // For INT_MAX (represents infinity)

using namespace std;

/*
    Graph class represents a weighted directed graph
    and provides an implementation of Dijkstra’s algorithm.
*/
class Graph {
private:
    int V;
    // Number of vertices (nodes) in the graph.
    // Vertices are assumed to be labeled from 0 to V-1.

    /*
        Adjacency list representation of the graph.
        adj[u] is a list of pairs (v, weight) meaning:
        - there is an edge from vertex u to vertex v
        - the edge has a cost (weight)
    */
    vector<vector<pair<int, int>>> adj;

public:
    /*
        Constructor:
        Initializes a graph with a given number of vertices.
        - vertices: total number of nodes in the graph
    */
    Graph(int vertices) {
        V = vertices;        // Store number of vertices
        adj.resize(V);       // Create V empty adjacency lists
    }

    /*
        Adds a directed edge to the graph.
        u -> v with weight w

        Parameters:
        - u: source vertex
        - v: destination vertex
        - w: weight (cost) of the edge
    */
    void addEdge(int u, int v, int w) {
        adj[u].push_back({v, w});
        // Store the edge as a (vertex, weight) pair
    }

    /*
        Dijkstra’s Algorithm:
        Computes the shortest path from source vertex s
        to all other vertices in the graph.

        Assumption:
        - All edge weights are non-negative.
    */
    void dijkstra(int s) {

        /*
            d[v] represents the shortest known distance
            from source vertex s to vertex v.

            Initially:
            - All distances are set to "infinity"
            - Except the source vertex which has distance 0
        */
        vector<int> d(V, INT_MAX);

        /*
            visited[v] is true if vertex v has been finalized,
            meaning the shortest distance to v is confirmed.
            This corresponds to set S in the algorithm.
        */
        vector<bool> visited(V, false);

        // Distance from source to itself is always 0
        d[s] = 0;

        /*
            Priority queue (min-heap) used to always extract
            the vertex with the smallest tentative distance.

            Each element is:
            (distance from source, vertex index)
        */
        priority_queue<
            pair<int, int>,              // (distance, vertex)
            vector<pair<int, int>>,      // container
            greater<pair<int, int>>      // min-heap comparator
        > Q;

        // Insert the source vertex into the priority queue
        Q.push({0, s});

        /*
            Main loop of Dijkstra’s algorithm:
            Continue until there are no vertices left to process.
        */
        while (!Q.empty()) {

            /*
                Extract the vertex u with the minimum distance
                from the priority queue.
            */
            int u = Q.top().second;
            Q.pop();

            /*
                If u has already been processed (finalized),
                skip it. This avoids reprocessing outdated entries
                from the priority queue.
            */
            if (visited[u])
                continue;

            /*
                Mark vertex u as visited.
                This means the shortest distance to u is finalized.
            */
            visited[u] = true;

            /*
                Relaxation step:
                Check all neighbors v of u.
                Try to improve the shortest distance to v
                by going through u.
            */
            for (auto edge : adj[u]) {
                int v = edge.first;   // Neighbor vertex
                int w = edge.second;  // Weight of edge u -> v

                /*
                    Relaxation condition:
                    If going from s -> u -> v is shorter than
                    the current known distance to v, update it.
                */
                if (!visited[v] && d[v] > d[u] + w) {
                    d[v] = d[u] + w;

                    /*
                        Push updated distance into the priority queue.
                        This acts as an implicit DECREASE-KEY operation.
                    */
                    Q.push({d[v], v});
                }
            }
        }

        /*
            Output the final shortest distances from source s
            to every vertex in the graph.
        */
        cout << "Vertex\tDistance from source\n";
        for (int i = 0; i < V; i++) {
            cout << i << "\t";
            if (d[i] == INT_MAX)
                cout << "INF\n";  // Vertex is unreachable
            else
                cout << d[i] << "\n";
        }
    }
};

int main() {

    /*
        Create a graph with 5 vertices:
        Vertices are labeled 0, 1, 2, 3, 4
    */
    Graph g(5);

    /*
        Add directed weighted edges to the graph.
        Each call represents: u -> v with weight w
    */
    g.addEdge(0, 1, 10);
    g.addEdge(0, 4, 5);
    g.addEdge(1, 2, 1);
    g.addEdge(1, 4, 2);
    g.addEdge(2, 3, 4);
    g.addEdge(3, 0, 7);
    g.addEdge(3, 2, 6);
    g.addEdge(4, 1, 3);
    g.addEdge(4, 2, 9);
    g.addEdge(4, 3, 2);

    /*
        Run Dijkstra’s algorithm starting from vertex 0.
        This computes the shortest path from 0 to all other vertices.
    */
    g.dijkstra(0);

    return 0;  // End of program
}
