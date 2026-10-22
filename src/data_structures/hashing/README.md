# Hashing

A hash table maps a key to an array index with a **hash function**:

```text
index = h(key) % table_size
```

The ideal is O(1) average time. The hard part is **collisions**: two different
keys can produce the same index.

## Stage 1 — hash functions (no collision handling)

These files show how the index is computed. They are deliberately simple so you
can focus on the mapping.

| File | Hash function | Idea |
| --- | --- | --- |
| `direct_hashing.h` | `h(key) = key` | The key *is* the index. O(1), but wastes memory |
| `division_method.h` | `h(key) = key % m` | Choose `m` to be prime for good spread |
| `multiplication_method.h` | `floor(m * frac(key * A))` | Uses the fractional part of `key * A` |
| `mid_square_method.h` | middle digits of `key²` | The middle digits depend on all digits of the key |
| `folding_method.h` | add/reverse groups of digits | Good for long numeric keys |

## Stage 2 — collision resolution

### Separate chaining (open hashing)

Each table slot holds a container of keys. Collisions are simply appended to the
container.

| File | Chain type | Lookup cost |
| --- | --- | --- |
| `separate_chaining.h` | `std::list` | O(1 + α) average |
| `separate_chaining_variants.h` | linked list, BST, AVL | O(α) to O(log α) per chain |

`α = n / m` is the **load factor**: elements divided by slots. Chaining degrades
gracefully when α grows.

### Open addressing (closed hashing)

All keys stay inside the table. On a collision, probe for another slot.

| File | Probe sequence | Problem |
| --- | --- | --- |
| `linear_probing.h` | `(h + i) % m` | Primary clustering |
| `quadratic_probing.h` | `(h + i²) % m` | Secondary clustering |
| `double_hashing.h` | `(h1 + i * h2) % m` | Best spread, needs a good `h2` |

Deletion is tricky in open addressing: you cannot simply empty a slot or later
searches break. The implementations mark removed slots instead.

### A complete hash map

`hash_map.h` combines the ideas above into a reusable `HashMap<Key, Value>`:
separate chaining, a configurable maximum load factor, automatic rehashing, and
`insert`, `find`, `erase`, `contains`, and `operator[]`. This is the structure
you would actually use as a dictionary.

## Complexity

| Operation | Average | Worst |
| --- | --- | --- |
| search | O(1) | O(n) |
| insert | O(1) | O(n) |
| delete | O(1) | O(n) |

The worst case happens when many keys collide. A good hash function and a load
factor below ~0.7 keep the average near O(1).

## Exercise

Insert keys `5, 15, 25, 35` into a table of size 10 using division hashing.
Draw the probes for linear probing, quadratic probing, and double hashing. Which
one spreads the keys best?
