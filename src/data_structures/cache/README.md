# LRU cache

An **LRU (least recently used)** cache keeps a fixed number of entries and
evicts the entry that has gone unused for the longest time. It is the standard
caching policy in operating systems, databases, and web servers.

## Files

| File | Contents |
| --- | --- |
| `lru_cache.h` | `LruCache<Key, Value>` |

## Why two structures?

Neither structure alone is enough:

| Structure | Fast lookup? | Fast recency update? |
| --- | --- | --- |
| Hash map | Yes, O(1) | No, no ordering |
| Linked list | No, O(n) lookup | Yes, O(1) move |
| **Both together** | **Yes** | **Yes** |

The hash map maps each key to its node in a doubly linked list. The list keeps
recency order:

```text
most recent                                      least recent
   [ a ] <-> [ c ] <-> [ b ] <-> [ d ]
     ^                              ^
   get/put                        eviction
```

- `get(key)` finds the node and moves it to the front.
- `put(key, value)` inserts at the front; if the cache is full, it removes the
  node at the back first.
- `erase(key)` removes a node from both structures.

`std::list::splice` moves a node without copying the value, so a recency update
is O(1).

## Complexity

| Operation | Average | Worst |
| --- | --- | --- |
| `get` | O(1) | O(n) |
| `put` | O(1) | O(n) |
| `contains` | O(1) | O(n) |
| `erase` | O(1) | O(n) |

The worst case is hash collisions; `std::unordered_map` normally keeps lookups
constant on average.

## Run

```bash
./build/bin/demo_lru_cache
```

## Exercises

1. Trace `put("one", 1)`, `put("two", 2)`, `get("one")`, `put("three", 3)` on a
   capacity-2 cache. Which key is evicted?
2. Why must the hash map store an **iterator** to the list node instead of a
   copy of the key?
3. Implement `peek(key)`, which returns a value **without** changing recency.
4. What changes if the policy becomes LFU (least frequently used)?
