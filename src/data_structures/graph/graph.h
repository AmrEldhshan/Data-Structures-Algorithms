#ifndef DSA_GRAPH_H
#define DSA_GRAPH_H

#include <stdexcept>
#include <vector>

// ---------------------------------------------------------------------------
// Edge stored in an adjacency list: where the edge goes and what it costs.
// ---------------------------------------------------------------------------
struct Edge {
    int to;
    int weight;
};

// ---------------------------------------------------------------------------
// Edge stored once in a flat list. This is handy for algorithms such as
// Bellman-Ford and Kruskal that want to look at every edge directly.
// ---------------------------------------------------------------------------
struct WeightedEdge {
    int from;
    int to;
    int weight;
};

// ---------------------------------------------------------------------------
// Graph
//
// Adjacency-list representation. Vertices are numbered 0 .. size() - 1.
// The same class supports directed and undirected graphs; for an undirected
// graph addEdge() stores both directions but the flat edge list keeps only
// one copy.
//
// Space: O(V + E)
// ---------------------------------------------------------------------------
class Graph {
public:
    explicit Graph(int vertices, bool directed = false)
        : adjacency_(vertices), directed_(directed) {}

    void addEdge(int from, int to, int weight = 1) {
        checkVertex(from);
        checkVertex(to);

        adjacency_[from].push_back({to, weight});
        edges_.push_back({from, to, weight});

        if (!directed_) {
            adjacency_[to].push_back({from, weight});
        }
    }

    int size() const { return static_cast<int>(adjacency_.size()); }

    bool directed() const { return directed_; }

    const std::vector<Edge>& neighbors(int vertex) const {
        checkVertex(vertex);
        return adjacency_[vertex];
    }

    const std::vector<WeightedEdge>& edgeList() const { return edges_; }

private:
    void checkVertex(int vertex) const {
        if (vertex < 0 || vertex >= size()) {
            throw std::out_of_range("Graph: vertex out of range");
        }
    }

    std::vector<std::vector<Edge>> adjacency_;
    std::vector<WeightedEdge> edges_;
    bool directed_;
};

#endif // DSA_GRAPH_H
