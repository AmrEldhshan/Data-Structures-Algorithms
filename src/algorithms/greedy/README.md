# Greedy algorithms

A greedy algorithm makes the choice that looks best **right now** and never
reconsiders. That is fast, but it is only correct when the problem has the
**greedy-choice property**: a locally optimal choice can be extended to a
globally optimal solution.

## Files

| File | Problem | Greedy choice | Time |
| --- | --- | --- | --- |
| `activity_selection.cpp` | Maximum non-overlapping activities | Earliest finish time | O(n log n) |
| `fractional_knapsack.cpp` | Maximum value with a weight limit | Highest value per weight | O(n log n) |
| `huffman_coding.cpp` | Shortest prefix-free codes | Merge two least frequent nodes | O(n log n) |
| `merge_intervals.cpp` | Merge overlapping ranges | Keep the furthest end | O(n log n) |
| `jump_game.cpp` | Minimum jumps to the end | Extend the current reach | O(n) |

## Activity selection

Sort by finish time and take an activity whenever it starts after the last
chosen finish. Choosing the earliest finish leaves the most room for the
remaining activities. This is the classic exchange-argument proof.

## Fractional knapsack

Items can be split, so take them in decreasing order of `value / weight`. The
last item may be taken partially.

Compare this with `../../algorithms/dynamic_programming/knapsack.cpp`: for 0/1
knapsack the same greedy choice can be wrong, which is why that problem needs
DP.

## Huffman coding

Repeatedly merge the two least frequent nodes. A min-priority queue gives
`O(n log n)`. The resulting tree gives each character a prefix-free binary code;
frequent characters end up with short codes.

| Text | Original bits | Huffman bits |
| --- | --- | --- |
| `abracadabra` | 88 | 23 |

## Merge intervals

Sort by start time. The next interval either overlaps the current one (extend
its end) or starts a new group. Sorting is what makes a single left-to-right
pass sufficient.

## Jump game

Track the furthest index reachable with the current jump and the end of the
current jump's range. When the scan reaches that end, take one more jump and
extend the range to the furthest index seen. If the range cannot advance past a
zero, the end is unreachable.

## When greedy fails

Try coins `{1, 3, 4}` and amount `6`. Greedy takes `4 + 1 + 1` (3 coins), but the
optimum is `3 + 3` (2 coins). Whenever a greedy choice can block a better
combination, use DP or search instead.

## Run

```bash
./build/bin/algo_activity_selection
./build/bin/algo_fractional_knapsack
./build/bin/algo_huffman
./build/bin/algo_merge_intervals
./build/bin/algo_jump_game
```

## Exercises

1. Prove that earliest-finish is optimal for activity selection.
2. Change the activity list so two different maximum sets exist.
3. Run fractional knapsack on `{value, weight} = {60,10}, {100,20}, {120,30}`
   with capacity 50.
4. Decode a Huffman bit string using the tree. Why is no separator needed?
5. Give a counterexample showing that greedy coin change is not always optimal.
