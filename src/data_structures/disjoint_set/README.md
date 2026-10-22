# Disjoint set (union-find)

A disjoint-set structure tracks a collection of non-overlapping sets. It answers
two questions quickly:

- **Find(x):** which set contains `x`?
- **Union(a, b):** merge the sets containing `a` and `b`.

It is the engine behind Kruskal's minimum spanning tree and many connectivity
problems.

## Files

| File | Representation | Union rule |
| --- | --- | --- |
| `disjoint_set_array.cpp` | `parent[]` and `size[]` arrays | Attach the smaller set under the larger one |
| `disjoint_set_tree.cpp` | Explicit node objects with parent pointers | Attach the smaller tree under the larger one |
| `union_find.h` | Array-based template with path compression and union by size | Both optimisations |

The two original programs contain a runnable `main()` and are built as
`ds_disjoint_set_array` and `ds_disjoint_set_tree`. The header-only
`union_find.h` is exercised by `demo_union_find` and the test suite.

## How it works

Each set is a tree. The root is the representative element. `find(x)` follows
parent pointers until it reaches a root. `union(a, b)` finds both roots and
attaches the smaller tree to the larger one. This is called the **weight rule**
(union by size).

```text
union(1, 2)        union(3, 4)         union(2, 4)
    1                  3                   1
   /                  /                  /   \
  2                  4                  2     3
                                             /
                                            4
```

## Why union by size helps

Without a rule, a sequence of unions can create a long chain, and `find` becomes
O(n). Always attaching the smaller tree to the larger one keeps the height
O(log n).

## Path compression

A second optimisation makes each node point directly at the root during `find`.
Combined with union by size, the amortised cost is almost constant: O(α(n)),
where α is the inverse Ackermann function.

`union_find.h` implements both. `find` compresses the path on the way back up;
`unite` attaches the smaller component under the larger one.

## Complexity

| Operation | This implementation | With path compression |
| --- | --- | --- |
| find | O(log n) | O(α(n)) ≈ O(1) |
| union | O(log n) | O(α(n)) ≈ O(1) |
| space | O(n) | O(n) |

## Run the demos

```bash
./build/bin/ds_disjoint_set_array
./build/bin/ds_disjoint_set_tree
./build/bin/demo_union_find
```

## Exercise

Build five singleton sets, then run these unions: `(0,1)`, `(2,3)`, `(1,3)`,
`(4,0)`. Draw the forest after each step. What is the final root of `2`?
