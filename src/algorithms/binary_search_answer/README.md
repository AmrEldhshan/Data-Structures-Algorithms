# Binary search on the answer

Sometimes the array is not the search space. Instead, a **monotone predicate**
`possible(x)` is false for small `x` and true for large `x` (or the reverse).
Binary search finds the boundary.

## File

| File | Problem |
| --- | --- |
| `binary_search_answer.cpp` | Minimum ship capacity to deliver all weights within `D` days |

## Pattern

```text
low  = smallest possible answer
high = largest possible answer

while low < high:
    middle = low + (high - low) / 2
    if possible(middle):
        high = middle        # middle works; try smaller
    else:
        low = middle + 1     # middle fails; answer is larger
```

The predicate must be monotone. If it can flip back and forth, binary search is
not valid.

## Example: ship packages

`possible(capacity)` simulates loading the packages in order and counts the days
needed. A larger capacity never needs more days, so the predicate is monotone.

| Bound | Value |
| --- | --- |
| low | `max(weights)` (one item must fit) |
| high | `sum(weights)` (everything in one day) |
| time | O(n log(sum(weights))) |

## Run

```bash
./build/bin/algo_binary_search_answer
```

## Exercises

1. Change the demo to **minimum eating speed** (Koko eating bananas).
2. Why is `middle = low + (high - low) / 2` safer than `(low + high) / 2`?
3. Find the first day on which a monotone event happens.
4. Prove that the capacity predicate is monotone.
