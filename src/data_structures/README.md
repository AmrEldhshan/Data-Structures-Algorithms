# Data structures

Each folder here answers one question: **how is this structure built from
scratch?**

| Folder | What you will learn |
| --- | --- |
| [`linked_lists/`](linked_lists/README.md) | Pointers, nodes, list variants, skip lists |
| [`stacks/`](stacks/README.md) | LIFO, expression parsing, postfix evaluation |
| [`queues/`](queues/README.md) | FIFO, circular buffers, priority queues |
| [`heaps/`](heaps/README.md) | Complete trees stored in arrays, heapify, min-heap |
| [`hashing/`](hashing/README.md) | Hash functions and collision resolution |
| [`trees/`](trees/README.md) | BST, balanced trees, spatial, interval, and range-query trees |
| [`graph/`](graph/README.md) | Adjacency-list graph representation |
| [`cache/`](cache/README.md) | LRU cache: hash map + linked list |
| [`disjoint_set/`](disjoint_set/README.md) | Union-find, weight rule, path compression |
| [`matrix/`](matrix/README.md) | Dense row-major matrix and arithmetic |
| [`bitset/`](bitset/README.md) | Fixed-size bits packed into 64-bit words |
| [`dynamic_array/`](dynamic_array/README.md) | Growable contiguous array with amortised O(1) append |
| [`big_integer/`](big_integer/README.md) | Arbitrary-precision signed integer |
| [`ordered/`](ordered/README.md) | Treap, ordered set, ordered map, order statistics |
| [`bloom_filter/`](bloom_filter/README.md) | Probabilistic membership |
| [`strings/`](strings/README.md) | Suffix arrays and suffix automata |
| [`sqrt_decomposition/`](sqrt_decomposition/README.md) | Block decomposition for range queries |
| [`probabilistic/`](probabilistic/README.md) | Count-min sketch, HyperLogLog, cuckoo filter |
| [`sets/`](sets/README.md) | Van Emde Boas set with predecessor/successor |

## How to use a header

All header-only structures are included relative to `src/`:

```cpp
#include "data_structures/stacks/stack.h"

int main() {
    Stack<int> stack;
    stack.push(10);
    stack.push(20);
    return stack.pop(); // 20
}
```

Compile with the include path:

```bash
g++ -std=c++20 -Isrc your_file.cpp -o your_program
```

Some structures are provided as `.cpp` files because they include a runnable
`main()`. Those are built automatically by CMake as `ds_*` targets.

## The pattern used in this repository

Most structures follow the same layout:

1. A short comment block: what the structure is and its complexity.
2. A `Node` (or array) representation.
3. Public operations: insert, delete, search, print.
4. Private helpers that keep the invariant (for example `heapifyDown`).

Read the comment block, then trace one operation by hand. That is usually enough
to understand the whole file.

## Suggested order

Linked lists → stacks → queues → heaps → hashing → trees → graph →
cache → disjoint set → advanced trees → bloom filter and suffix array.
