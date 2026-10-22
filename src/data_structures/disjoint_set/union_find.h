#ifndef DSA_UNION_FIND_H
#define DSA_UNION_FIND_H

#include <stdexcept>
#include <utility>
#include <vector>

// ---------------------------------------------------------------------------
// Union-find (disjoint set union) with path compression and union by rank
//
// parent[x] points to x's parent; a root points to itself.
//
// find(x): follow parent pointers to the root and compress the path so future
//          queries are faster.
// unite(a, b): attach the shorter tree under the taller one (rank heuristic).
//
// Amortised time per operation: O(alpha(n)), effectively constant.
// Space: O(n).
// ---------------------------------------------------------------------------
class UnionFind {
public:
    explicit UnionFind(int size)
        : parent_(size), rank_(size, 0), componentSize_(size, 1) {
        if (size < 0) throw std::invalid_argument("UnionFind: negative size");
        for (int i = 0; i < size; ++i) parent_[i] = i;
    }

    int size() const { return static_cast<int>(parent_.size()); }

    int find(int vertex) {
        checkVertex(vertex);

        int root = vertex;
        while (parent_[root] != root) root = parent_[root];

        // Path compression: point every visited node directly at the root.
        while (parent_[vertex] != vertex) {
            int next = parent_[vertex];
            parent_[vertex] = root;
            vertex = next;
        }

        return root;
    }

    bool connected(int a, int b) { return find(a) == find(b); }

    // Returns true when the two components were actually merged.
    bool unite(int a, int b) {
        int rootA = find(a);
        int rootB = find(b);
        if (rootA == rootB) return false;

        if (rank_[rootA] < rank_[rootB]) std::swap(rootA, rootB);

        parent_[rootB] = rootA;
        componentSize_[rootA] += componentSize_[rootB];

        if (rank_[rootA] == rank_[rootB]) ++rank_[rootA];
        --components_;
        return true;
    }

    int componentSize(int vertex) { return componentSize_[find(vertex)]; }

    int components() const { return components_; }

private:
    void checkVertex(int vertex) const {
        if (vertex < 0 || vertex >= size()) {
            throw std::out_of_range("UnionFind: vertex out of range");
        }
    }

    std::vector<int> parent_;
    std::vector<int> rank_;
    std::vector<int> componentSize_;
    int components_ = static_cast<int>(parent_.size());
};

#endif // DSA_UNION_FIND_H
