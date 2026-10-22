# Bloom filter

A Bloom filter is a **probabilistic** set. It can answer "is this element in the
set?" with two possible replies:

- **"Definitely not in the set"** — always correct.
- **"Possibly in the set"** — may be a false positive.

There are **no false negatives**. That trade-off is why Bloom filters are used
in databases, caches, and network routers where a small amount of memory must
filter out most useless lookups.

## How it is built

1. Allocate a bit array of `m` bits.
2. Choose `k` hash functions.
3. **Insert(x):** set the `k` bits at `hash_i(x)`.
4. **Query(x):** if *any* of the `k` bits is 0, `x` is definitely absent. If all
   are 1, `x` is possibly present.

```text
bits:  0 1 0 1 1 0 0 1 0 1
          ^     ^       ^
        h1(x)  h2(x)   h3(x)
```

The file `bloom_filter.cpp` implements this with **double hashing**:

```text
hash_i(x) = (h1(x) + i * h2(x)) % m
```

This avoids writing `k` separate hash functions.

## Choosing k

For `n` expected elements and `m` bits:

```text
k = (m / n) * ln(2)
```

This minimises the false-positive rate. The constructor in the example computes
`k` with exactly this formula.

## Complexity

| Operation | Time | Space |
| --- | --- | --- |
| insert | O(k) | O(m) bits |
| query | O(k) | O(m) bits |

`k` is a small constant, so both operations are effectively O(1).

## The `fruitExample.cpp` program

The file is a complete example (renamed to `bloom_filter.cpp` during the
repository cleanup). It builds a filter of fruit names, checks some present
names, and shows that an absent name may still be reported as "possibly
present". Read the top comment block for the full explanation.

## Run

```bash
./build/bin/ds_bloom_filter
```

## Exercise

Why can a Bloom filter never have false negatives? Explain using the bit-setting
rule. Then compute the false-positive rate for `m = 1000`, `n = 100`.
