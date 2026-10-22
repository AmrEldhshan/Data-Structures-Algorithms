# Sets

Ordered integer sets with fast predecessor/successor queries.

## Files

| File | Structure | Universe | Operations |
| --- | --- | --- | --- |
| `van_emde_boas.h` | Van Emde Boas set (two-level layout) | 16-bit integers | O(1) insert/remove/contains/successor/predecessor |

## Van Emde Boas layout

A full vEB tree splits a universe `U` into `√U` clusters of size `√U`, and
recurses on both the clusters and a summary of non-empty clusters. This
implementation flattens that idea into two levels:

```text
universe: 2^16 values
high 8 bits -> cluster index (0..255)
low  8 bits -> bit inside the cluster
summary     -> which clusters are non-empty
```

Each cluster is a 256-bit bitset (`4 × uint64_t`). The summary is also a 256-bit
bitset. Finding the next set bit uses `std::countr_zero`; finding the previous
set bit uses `std::countl_zero`.

## Complexity

With the fixed 16-bit universe, every operation is O(1). A recursive vEB tree
keeps `O(log log U)` time for arbitrary universes.

## Run the demo

```bash
./build/bin/demo_van_emde_boas
```
