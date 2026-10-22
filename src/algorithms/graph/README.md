# Graph algorithms

A graph is a set of vertices connected by edges. This folder builds up the
standard graph toolbox: traversal, ordering, connectivity, shortest paths,
minimum spanning trees, and a few classic structural queries.

All examples use the shared adjacency-list class in
[`src/data_structures/graph/graph.h`](../../data_structures/graph/graph.h).
Vertices are numbered `0 .. V-1`.

## Files

| File | Algorithm | Graph type | Finds |
| --- | --- | --- | --- |
| `bfs.cpp` | Breadth-first search | Any | Shortest path in edge count, components |
| `dfs.cpp` | Depth-first search | Any | Traversal order, discovery/finish times |
| `topological_sort.cpp` | Kahn and DFS topological sort | Directed | A valid dependency order |
| `cycle_detection.cpp` | DFS colouring | Directed / undirected | Whether a cycle exists |
| `connected_components.cpp` | BFS labelling | Undirected | Components and their size |
| `scc_tarjan.cpp` | Tarjan | Directed | Strongly connected components |
| `dijkstra.cpp` | Dijkstra | Weighted, non-negative | Shortest paths from one source |
| `bellman_ford.cpp` | Bellman-Ford | Weighted, negative allowed | Shortest paths + negative cycles |
| `floyd_warshall.cpp` | Floyd-Warshall | Weighted, negative allowed | All-pairs shortest paths |
| `kruskal_mst.cpp` | Kruskal | Weighted undirected | Minimum spanning tree |
| `prim_mst.cpp` | Prim | Weighted undirected | Minimum spanning tree |
| `bipartite_check.cpp` | BFS 2-colouring | Undirected | Whether the graph is bipartite |
| `bridges_articulation.cpp` | Tarjan low-link | Undirected | Bridges and cut vertices |
| `lca_binary_lifting.cpp` | Binary lifting | Tree | Lowest common ancestor, distance |
| `spfa.cpp` | SPFA | Weighted, negative allowed | Queue-based shortest paths + negative cycles |
| `dag_shortest_path.cpp` | DAG relaxation | Directed acyclic, negative allowed | Shortest paths in O(V + E) |
| `a_star.cpp` | A* | Weighted grid, non-negative | Goal-directed shortest path with a heuristic |
| `johnson.cpp` | Johnson | Weighted, negative allowed | All-pairs shortest paths with reweighting |

## Representation

```cpp
Graph graph(V, /*directed=*/false);
graph.addEdge(u, v, weight);   // weight defaults to 1
for (const Edge& e : graph.neighbors(u)) { ... }
for (const WeightedEdge& e : graph.edgeList()) { ... }
```

The adjacency list costs `O(V + E)` space and lets us iterate a vertex's
neighbours in `O(degree)`. The flat edge list is kept for algorithms that want
to scan every edge.

## Traversal

**BFS** explores in rings around the source. Because it visits vertices in
non-decreasing distance, it finds shortest paths when every edge has the same
cost. It also labels connected components.

**DFS** follows one branch to the end before backtracking. Discovery and finish
times turn the DFS tree into a powerful tool: they drive cycle detection,
topological sorting, SCCs, bridges, and articulation points.

| Algorithm | Time | Space |
| --- | --- | --- |
| BFS | O(V + E) | O(V) |
| DFS | O(V + E) | O(V) |

## Ordering and connectivity

- **Topological sort** only exists for a DAG. Kahn repeatedly removes a vertex
  with in-degree 0; the DFS version reverses finishing order. If a vertex is
  never removed, a cycle exists.
- **Strongly connected components**: `u` and `v` are in the same SCC when each
  can reach the other. Tarjan finds all SCCs in one DFS pass using
  `discovery`/`low` values and a stack.
- **Bridges** are edges whose removal disconnects the graph. **Articulation
  points** are vertices whose removal disconnects the graph. Both come from the
  same low-link calculation.

## Shortest paths

| Algorithm | Weights | Time | Use when |
| --- | --- | --- | --- |
| BFS | Unweighted | O(V + E) | Every edge costs the same |
| Dijkstra | Non-negative | O((V + E) log V) | One source, non-negative weights |
| Bellman-Ford | Negative allowed | O(V · E) | One source, negative edges, cycle detection |
| Floyd-Warshall | Negative allowed | O(V³) | All pairs, small graph |
| SPFA | Negative allowed | O(V · E) worst | One source, negative edges, often faster than Bellman-Ford |
| DAG relaxation | Negative allowed | O(V + E) | One source in a DAG |
| A* | Non-negative | O(E log V) worst | One source/goal with a useful heuristic |
| Johnson | Negative allowed, no negative cycle | O(VE + V(V + E) log V) | All pairs, sparse graph |

Dijkstra is greedy: once a vertex is popped from the min-heap, its distance is
final. A negative edge breaks that guarantee, which is why Bellman-Ford relaxes
every edge `V - 1` times instead.

**SPFA** is Bellman-Ford with a queue: only vertices whose distance changed are
relaxed again. It detects a negative cycle when a vertex is relaxed `V` times.

**DAG shortest paths** first topologically sorts the graph, then relaxes edges
in that order. Every incoming path is settled before a vertex is processed, so
one pass is enough. A negative edge is fine as long as there is no cycle.

**A\*** orders the priority queue by `f = g + h`. `g` is the cost so far and `h`
is an estimate of the remaining cost. With an admissible (never overestimating)
and consistent heuristic, the first goal popped is optimal. On a 4-direction
grid, Manhattan distance is the natural heuristic.

**Johnson's algorithm** handles negative edges for all-pairs shortest paths.
One Bellman-Ford run from a virtual source computes potentials `h`; reweighting
with `w'(u,v) = w(u,v) + h[u] - h[v]` makes every edge non-negative. Running
Dijkstra from every vertex is then valid, and `dist'(u,v) - h[u] + h[v]` gives
the original distance.

## Minimum spanning trees

A spanning tree connects every vertex with no cycles. A **minimum** spanning
tree has the smallest possible total edge weight.

- **Kruskal**: sort edges by weight and add an edge when its endpoints are in
  different components (union-find). `O(E log E)`.
- **Prim**: grow one tree, always adding the cheapest edge leaving it.
  `O(E log V)` with a binary heap.

Both produce the same total weight (though the chosen edges may differ when
weights tie). The two demos use the same graph and both print `16`.

## Bipartite graphs

A graph is bipartite when its vertices can be split into two sides with every
edge crossing between them. BFS colours neighbours with the opposite colour; a
same-colour neighbour means an odd cycle and a failed check.

## Lowest common ancestor

For a rooted tree, `LCA(u, v)` is the deepest vertex that is an ancestor of
both. Binary lifting stores the `2^k`-th ancestor of every vertex, which answers
each query in `O(log V)` after an `O(V log V)` build. The distance between two
vertices is `depth[u] + depth[v] - 2 * depth[LCA(u, v)]`.

## Run

```bash
./build/bin/algo_bfs
./build/bin/algo_dfs
./build/bin/algo_topological_sort
./build/bin/algo_cycle_detection
./build/bin/algo_connected_components
./build/bin/algo_scc_tarjan
./build/bin/algo_dijkstra
./build/bin/algo_bellman_ford
./build/bin/algo_floyd_warshall
./build/bin/algo_kruskal
./build/bin/algo_prim
./build/bin/algo_bipartite_check
./build/bin/algo_bridges_articulation
./build/bin/algo_lca
./build/bin/algo_spfa
./build/bin/algo_dag_shortest_path
./build/bin/algo_a_star
./build/bin/algo_johnson
```

## Exercises

1. Run BFS from a vertex in a disconnected graph. Which distances stay `-1`?
2. Add an edge to the DAG in `topological_sort.cpp` that creates a cycle. Why
   does Kahn's queue eventually become empty with vertices left over?
3. In `bellman_ford.cpp`, remove the `changed` early exit. Does the result
   change? What does the extra pass cost?
4. Floyd-Warshall is `O(V³)`. How many operations does that mean for `V = 1000`?
   When would you use repeated Dijkstra instead?
5. Run Prim and Kruskal on a graph with equal edge weights. Do they choose the
   same tree? Why is the total weight still the same?
6. A tree has no cycles. What are its bridges and articulation points?
7. Why must the LCA table store `-1` for ancestors above the root?
