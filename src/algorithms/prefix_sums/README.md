# Prefix sums and difference arrays

Prefix sums trade O(n) preprocessing for O(1) range-sum queries. Difference
arrays do the reverse: many range updates in O(1) each, then one O(n) pass to
reconstruct the final array.

## File

| File | Contents |
| --- | --- |
| `prefix_sums.cpp` | `RangeSum`, range-sum queries, range additions with a difference array |

## Prefix sums

```text
prefix[0] = 0
prefix[i] = prefix[i - 1] + values[i - 1]

sum(left, right) = prefix[right + 1] - prefix[left]
```

| Operation | Time |
| --- | --- |
| build | O(n) |
| range sum | O(1) |
| point update | O(n) to rebuild (use a Fenwick tree instead) |

## Difference arrays

To add `v` to every element in `[left, right]`:

```text
difference[left] += v
difference[right + 1] -= v
```

After all updates, a prefix sum of `difference` yields the final values.

| Operation | Time |
| --- | --- |
| range update | O(1) |
| final reconstruction | O(n) |

## Run

```bash
./build/bin/algo_prefix_sums
```

## Exercises

1. Build the prefix array for `[3, 1, 4, 1, 5]` and answer `sum(1, 3)`.
2. Why does `difference[right + 1] -= v` need an extra slot?
3. Use a 2D prefix sum to answer rectangle sums in O(1).
4. Compare prefix sums with a Fenwick tree for point updates plus range queries.
