# Range query algorithms

Offline and data-structure-based ways to answer many range queries quickly.

## Files

| File | Algorithm | Time |
| --- | --- | --- |
| `mos_algorithm.cpp` | Mo's algorithm (range sums) | O((n + q)√n) |

## Mo's algorithm

Given `q` range queries, sort them by the block of their left endpoint and by
the right endpoint. Consecutive queries usually differ by only a few positions,
so the current window can be adjusted incrementally.

```text
block = sqrt(n)
sort by (left / block, right)  // alternate right direction per block
```

Adding or removing one element must be O(1); here it updates a running sum.
Classic applications include distinct values, frequencies, and range mode.

## Run

```bash
./build/bin/algo_mos
```

## Exercises

1. Add a `distinct` counter to answer "how many distinct values in [l, r]?".
2. Try block size `n / sqrt(q)` and compare the number of movements.
3. Why does alternating the right endpoint direction help?
4. Extend the template to support point updates (Mo's algorithm with updates).
