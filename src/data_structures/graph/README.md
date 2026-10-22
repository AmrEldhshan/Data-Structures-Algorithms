# Graph representation

A graph is a collection of vertices and edges. The same graph can be stored in
several ways; this folder uses the **adjacency list**, which is the usual choice
for sparse graphs and for every algorithm in
[`src/algorithms/graph/`](../../algorithms/graph/README.md).

## Files

| File | Contents |
| --- | --- |
| `graph.h` | `Graph`, `Edge`, `WeightedEdge` |

## Interface

```cpp
#include "data_structures/graph/graph.h"

Graph graph(5, /*directed=*/false);
graph.addEdge(0, 1, 4);          // 0 -- 1 with weight 4
graph.addEdge(1, 2);             // weight defaults to 1

for (const Edge& e : graph.neighbors(0)) {
    // e.to, e.weight
}

for (const WeightedEdge& e : graph.edgeList()) {
    // e.from, e.to, e.weight
}
```

Vertices are numbered `0 .. size() - 1`; an out-of-range vertex throws
`std::out_of_range`.

## Representation

```text
adjacency_[0] -> (1, 4)
adjacency_[1] -> (0, 4) -> (2, 1)
adjacency_[2] -> (1, 1)
```

For an undirected graph, `addEdge(u, v, w)` stores `v` in `u`'s list **and**
`u` in `v`'s list. The flat `edgeList()` keeps only one copy of each edge, which
is what Kruskal and Bellman-Ford want.

## Complexity

| Operation | Time |
| --- | --- |
| Add edge | O(1) |
| Iterate neighbours of `u` | O(degree(u)) |
| Iterate all edges | O(E) |
| Check whether `u -- v` exists | O(degree(u)) |
| Space | O(V + E) |

## Adjacency list vs adjacency matrix

| | Adjacency list | Adjacency matrix |
| --- | --- | --- |
| Space | O(V + E) | O(V²) |
| Add edge | O(1) | O(1) |
| Check edge | O(degree) | O(1) |
| Iterate neighbours | O(degree) | O(V) |
| Best for | Sparse graphs | Dense graphs |

## Exercises

1. Add a `removeEdge(u, v)` method. What is its time complexity?
2. Build the same graph as an `vector<vector<int>>` matrix and compare the
   memory used for `V = 10_000, E = 20_000`.
3. Why does the flat edge list store an undirected edge only once?
4. What happens if you call `addEdge(0, 0)`? Is a self-loop useful?
