# Ordered set and ordered map

Sorted associative containers built on a **treap** (a randomized balanced binary
search tree). Unlike a hash table, iteration is in key order, and the subtree
sizes support order statistics.

## Files

| File | Contents |
| --- | --- |
| `treap.h` | `Treap<Key, Value, Compare>`: insertion, erase, lookup, kth, rank, bounds, in-order traversal |
| `ordered_set.h` | `OrderedSet<T>`: unique sorted values |
| `ordered_map.h` | `OrderedMap<K, V>`: unique sorted keys with values |

## Why a treap?

Each node stores a random priority. The tree is a BST on the key and a min-heap
on the priority. Random priorities keep the expected height O(log n), and
rotations restore the heap property after insertion or deletion.

```text
key:      50 (priority 2)
         /              \
       30 (7)          70 (4)
      /     \             \
    20 (9)  40 (8)        80 (11)
```

The priorities are random, so the shape is not deterministic, but the expected
costs are.

## Operations

| Operation | Expected time |
| --- | --- |
| insert / erase | O(log n) |
| contains / find | O(log n) |
| minimum / maximum | O(log n) |
| kth smallest (0-based) | O(log n) |
| rank (number of keys smaller) | O(log n) |
| lowerBound / upperBound | O(log n) |
| in-order traversal | O(n) |

Order statistics work because every node stores the size of its subtree. To find
the k-th element, compare `k` with the left subtree size and descend.

## Example

```cpp
#include "data_structures/ordered/ordered_set.h"

OrderedSet<int> set;
set.insert(5);
set.insert(1);
set.insert(9);

std::cout << set.kth(1) << '\n';       // 5
std::cout << set.rank(9) << '\n';      // 2
```

## Run the demo

```bash
./build/bin/demo_ordered
```
