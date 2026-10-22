# Two pointers and sliding window

Many array and string problems become linear once you maintain a moving
interval instead of recomputing from scratch. The two pointers usually move in
the same direction (a sliding window) or towards each other (a sorted-array
search).

## Files

| File | Problem | Time |
| --- | --- | --- |
| `sliding_window.cpp` | Max sum of `k` consecutive values | O(n) |
| `sliding_window.cpp` | Longest substring without repeated characters | O(n) |
| `sliding_window.cpp` | Minimum window containing a pattern | O(n) |
| `sliding_window.cpp` | Two-sum on a sorted array | O(n) |

## Fixed-size window

For a sum over exactly `k` elements, compute the first window once, then add the
new element and subtract the element that leaves:

```text
windowSum += values[right] - values[right - k]
```

Each step is O(1), so the whole scan is O(n).

## Variable-size window

For "longest substring without repeats", expand `right`. When a character
repeats inside the window, move `left` past its previous occurrence. Every index
enters and leaves the window at most once, so the total work is O(n).

The minimum-window problem is similar but shrinks the window from the left
**while it is still valid**, recording the smallest valid window seen.

## Two pointers on sorted data

For two-sum on a sorted array:

```text
sum too small -> move left pointer right
sum too large -> move right pointer left
```

Each pointer moves at most `n` steps, so the scan is O(n). Sorting first would
cost O(n log n).

## Run

```bash
./build/bin/algo_sliding_window
```

## Exercises

1. Find the maximum average of any `k` consecutive values.
2. Find the longest substring with at most two distinct characters.
3. Find the smallest subarray with sum at least `S` (all values positive).
4. Why does the two-pointer two-sum require sorted input?
5. Prove that the variable-size window is O(n), not O(n²).
