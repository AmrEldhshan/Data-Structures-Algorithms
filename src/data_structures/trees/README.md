# Trees

A tree is a set of nodes connected by edges with no cycles. Trees are the
backbone of databases, file systems, compilers, and spatial indexes. The files
here build several kinds of tree from scratch.

## The trees in this folder

| File | Structure | Best for | Search / update |
| --- | --- | --- | --- |
| `bst.h` | Binary search tree | Learning the basic ordering rule | O(h), worst O(n) |
| `avl.h` | AVL tree | Strictly balanced search | O(log n) |
| `red_black_tree.h` | Red-black tree | Balanced search with fewer rotations | O(log n) |
| `two_three_tree.h` | 2-3 tree | Understanding multi-way search trees | O(log n) |
| `interval_tree.h` | Interval tree (template) | Overlap queries | O(log n + k) |
| `interval_tree_augmented.cpp` | Augmented BST interval tree | Seeing the `max` augmentation | O(h + k) |
| `red_black_interval_tree.cpp` | Red-black interval tree | Guaranteed O(log n) overlap queries | O(log n + k) |
| `segment_tree.cpp` | Segment tree | Static interval overlap queries | O(log n + k) |
| `kd_tree.cpp` | KD-tree (d dimensions) | Orthogonal range queries in space | O(n^(1-1/d) + k) |
| `range_tree_2d.cpp` | 2D range tree | Orthogonal range queries | O(log² n + k) |
| `range_tree_d_dim.cpp` | d-dimensional range tree | Higher-dimensional queries | O(log^d n + k) |
| `trie.h` | Trie (prefix tree) | Prefix lookup and autocomplete | O(L) |
| `fenwick_tree.h` | Fenwick tree (BIT) | Prefix sums with point updates | O(log n) |
| `sparse_table.h` | Sparse table | Static range-minimum queries | O(1) query |
| `splay_tree.h` | Splay tree | Self-adjusting search + order statistics | Amortised O(log n) |
| `lazy_segment_tree.h` | Lazy segment tree | Range add + range sum | O(log n) |
| `merge_sort_tree.h` | Merge-sort tree | Count/k-th in a range | O(log² n) |
| `persistent_segment_tree.h` | Persistent segment tree | Historical range sums | O(log n) per update |
| `wavelet_tree.h` | Wavelet tree | Rank and k-th in a range | O(log σ) |
| `disjoint_sparse_table.h` | Disjoint sparse table | Static idempotent RMQ | O(1) query |
| `radix_tree.h` | Radix tree (compressed trie) | Prefix lookup with compressed edges | O(key length) |
| `suffix_tree.h` | Suffix tree (naive radix construction) | Substring search and occurrence counts | O(m) search |
| `b_tree.h` | B-tree | Multi-way balanced search tree | O(log n) |
| `b_plus_tree.h` | B+ tree | Internal separators, all keys in leaves | O(log n) |

`k` is the number of results reported. Files ending in `.cpp` contain a runnable
`main()` and are built as CMake targets named `ds_*`.

## Binary search tree (BST)

Rule: for every node, all values in the left subtree are smaller and all values
in the right subtree are larger.

```text
        50
       /  \
     30    70
    / \   / \
   20 40 60 80
```

- **Inorder traversal** visits values in sorted order.
- **Search** compares once per level: O(h).
- **Problem:** inserting sorted data creates a chain, so `h` becomes n.

`bst.h` also includes breadth-first traversal, predecessor/successor, and all
three depth-first traversals.

## AVL tree

An AVL tree keeps `height(left) - height(right)` in `{-1, 0, 1}` for every node.
After an insertion or deletion, it rotates the first unbalanced node:

| Case | Rotation |
| --- | --- |
| Left-left | Right rotation |
| Right-right | Left rotation |
| Left-right | Left then right |
| Right-left | Right then left |

Because the height is O(log n), every search is O(log n). The implementation
stores the height in each node and updates it after each rotation.

## Red-black tree

A red-black tree is a BST with colour rules. It allows slightly less balance
than an AVL tree but needs fewer rotations. The file implements the standard
fix-up after insertion, including recolouring and rotations.

## 2-3 tree

Every node has either two or three children, and all leaves are at the same
depth. Nodes with three children hold two keys. This shows how a multi-way tree
stays perfectly balanced without rotations.

## Interval and segment trees

These answer questions about ranges:

- **Interval tree:** store intervals; report all intervals overlapping a query.
- **Segment tree:** split the coordinate range into canonical segments; store
  the intervals attached to each segment.

The interval tree augments each node with `max`, the largest `high` endpoint in
its subtree. This lets the search skip a subtree when no interval there can
overlap the query.

## Splay tree

A splay tree moves every accessed node to the root with zig, zig-zig, and
zig-zag rotations. It needs no balance metadata, and recently used keys become
cheap. Subtree sizes add `kth` and `rank` queries. Individual operations can be
O(n), but the amortised cost is O(log n).

## Lazy segment tree

A lazy segment tree stores pending range additions in a `lazy` array. An update
that fully covers a node changes the node's sum and lazy value immediately;
children are updated only when a later operation descends into them. This keeps
range add and range sum at O(log n).

## Range-query trees

- **Merge-sort tree:** each segment-tree node stores its range sorted. Counts
  use binary search; k-th uses a value binary search over those counts.
- **Persistent segment tree:** each update copies O(log n) nodes, so old versions
  remain queryable. This is the basis for persistent arrays and versioned data.
- **Wavelet tree:** recursively partitions values by the median and stores
  prefix counts. Rank and k-th descend one level per step.
- **Disjoint sparse table:** a static RMQ structure whose two table lookups cover
  the query with disjoint power-of-two blocks.

## KD-tree and range trees

A KD-tree splits space alternately by dimension (`x`, then `y`, then `x`, ...).
It is excellent for nearest-neighbour and orthogonal range queries. A range tree
builds a balanced tree on one dimension and stores a secondary tree at each node
for the next dimension. Both files include comments explaining why a KD-tree
query is not O(log n).

## Trie

A trie stores strings character by character. Each node is a prefix; a flag marks
where a complete word ends.

```text
insert: cat, car, card

        root
         |
         c
         |
         a
        / \
      (t)  r
      cat  |
          (r) -- d
          car  (card)
```

Looking up a word of length `L` costs `O(L)`, no matter how many words are
stored. The trade-off is memory: each node may hold 26 child pointers.

## Fenwick tree (BIT)

A Fenwick tree stores prefix sums in a clever array. Index `i` covers a block
whose length is the lowest set bit of `i`:

```text
i:      1   2   3   4   5   6   7   8
covers: 1   2   1   4   1   2   1   8   elements
```

`prefixSum(i)` walks `i -= i & -i`; `add(i, delta)` walks
`i += i & -i`. Both touch only `O(log n)` entries, and the tree uses `O(n)`
space — much less than a segment tree for this specific job.

## Sparse table

A sparse table precomputes the minimum of every power-of-two block:
`table[k][i]` is the minimum of `2^k` elements starting at `i`. A query takes two
overlapping blocks of the largest fitting power of two and combines them. The
build is `O(n log n)`, a query is `O(1)`, and the array is static (no updates).

## Run the tree demos

```bash
./build/bin/ds_kd_tree
./build/bin/ds_range_tree_2d
./build/bin/ds_range_tree_d_dim
./build/bin/ds_segment_tree
./build/bin/ds_interval_tree_augmented
./build/bin/ds_red_black_interval_tree
./build/bin/demo_trie
./build/bin/demo_fenwick
./build/bin/demo_sparse_table
```

## Exercises

1. Insert `1, 2, 3, 4, 5` into `bst.h`; print the tree. Insert the same values
   into `avl.h`; compare the heights.
2. Why does the interval tree store `max` instead of `min`?
3. Build a KD-tree with points `(2,3)`, `(5,4)`, `(9,6)`, and query the
   rectangle `[3,7] x [2,5]`. Which points are returned?
4. In the segment tree, why does an interval get attached to O(log n) nodes?
5. Insert `do`, `dog`, and `door` into a trie. How many nodes does the shared
   prefix save compared with three separate character arrays?
6. Why can a Fenwick tree compute prefix sums but not range minima?
7. A sparse table query uses two overlapping blocks. Why is that still correct
   for `min` but not for `sum`?
