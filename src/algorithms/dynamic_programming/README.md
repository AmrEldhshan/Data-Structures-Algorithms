# Dynamic programming

Dynamic programming (DP) solves a problem by combining answers to **overlapping
subproblems**. It needs two properties:

1. **Optimal substructure** — the best answer is built from best answers to
   smaller problems.
2. **Overlapping subproblems** — the same smaller problem is solved many times.

DP avoids recomputation by storing results (memoisation) or by filling a table in
the right order (tabulation).

## Files

| File | Problem | Time | Space |
| --- | --- | --- | --- |
| `fibonacci.cpp` | Fibonacci three ways | O(2ⁿ) / O(log n) / O(n) | O(n) / O(log n) / O(1) |
| `knapsack.cpp` | 0/1 knapsack | O(nW) | O(W) |
| `lis.cpp` | Longest increasing subsequence | O(n log n) | O(n) |
| `lcs.cpp` | Longest common subsequence | O(mn) | O(mn) |
| `edit_distance.cpp` | Levenshtein distance | O(mn) | O(mn) |
| `coin_change.cpp` | Minimum coins + number of ways | O(nA) | O(A) |
| `matrix_chain.cpp` | Optimal matrix multiplication order | O(n³) | O(n²) |
| `rod_cutting.cpp` | Maximum revenue from a rod | O(n²) | O(n) |
| `longest_palindromic_subsequence.cpp` | LPS length | O(n²) | O(n²) |
| `unbounded_knapsack.cpp` | Unbounded knapsack | O(nW) | O(W) |
| `partition_equal_subset.cpp` | Equal-sum partition | O(nS) | O(S) |
| `tsp_bitmask.cpp` | Travelling salesman (Held-Karp) | O(2ⁿ n²) | O(2ⁿ n) |
| `tree_dp.cpp` | Maximum-weight independent set on a tree | O(V) | O(V) |
| `digit_dp.cpp` | Count numbers with a digit-sum property | O(digits × sum × 10) | O(sum) |
| `interval_dp.cpp` | Burst balloons (interval DP) | O(n³) | O(n²) |

## Fibonacci

| Method | Idea | Time | Space |
| --- | --- | --- | --- |
| Plain recursion | `fib(n) = fib(n-1) + fib(n-2)` | O(2ⁿ) | O(n) stack |
| Matrix exponentiation | Raise `[[1,1],[1,0]]` to the n-th power | O(log n) | O(log n) |
| Iterative DP | Keep only the last two values | O(n) | O(1) |

The recursive version recomputes the same values exponentially many times. The
iterative version keeps a rolling window of two values, which is the smallest
possible state.

## 0/1 knapsack

Given `n` items with weight `wt[i]` and value `val[i]`, and a capacity `W`, choose
items to maximise value without exceeding `W`. Each item is taken or left.

```text
dp[w] = maximum value with capacity w

for each item i:
    for w from W down to wt[i]:
        dp[w] = max(dp[w], val[i] + dp[w - wt[i]])
```

The loop runs **backwards** so that each item is used at most once.

## Longest increasing subsequence

`dp[i]` is the best length ending at `i`, which gives an easy O(n²) solution.
The faster version keeps `tails[len - 1]`, the smallest possible tail of an
increasing subsequence of length `len`. Replacing a tail with a smaller value
never hurts future extensions.

## Longest common subsequence

For strings `a` and `b`:

```text
a[i-1] == b[j-1] : dp[i][j] = dp[i-1][j-1] + 1
otherwise        : dp[i][j] = max(dp[i-1][j], dp[i][j-1])
```

The table is `(m+1) x (n+1)`. Walking backwards from `dp[m][n]` reconstructs one
LCS; several answers of the same length may exist.

## Edit distance

`dp[i][j]` is the cost of turning `a[0..i)` into `b[0..j)` using insert, delete,
or replace. The three transitions correspond exactly to the last operation:

```text
insert  : dp[i][j-1] + 1
delete  : dp[i-1][j] + 1
replace : dp[i-1][j-1] + (a[i-1] != b[j-1])
```

## Coin change

- **Minimum coins:** `dp[amount] = min(dp[amount - coin] + 1)`.
- **Combinations:** coins on the outside, amounts on the inside.
- **Permutations:** amounts on the outside, coins on the inside.

The loop order changes the meaning of the result. This is one of the most
common DP mistakes.

## Matrix chain multiplication

Multiplying matrices is associative, so the parenthesisation changes the number
of scalar multiplications. `dp[i][j]` is the cheapest way to multiply matrices
`i..j`; trying every split `k` gives an O(n³) algorithm. The `split` table is
used to print the optimal order.

## Rod cutting

A rod of length `n` can be cut into pieces with prices `price[length]`.
`dp[length] = max(price[cut] + dp[length - cut])`. This is the unbounded
knapsack pattern: a piece can be reused.

## Longest palindromic subsequence

`dp[i][j]` is the LPS length inside `s[i..j]`:

```text
s[i] == s[j] : dp[i][j] = dp[i+1][j-1] + 2
otherwise    : dp[i][j] = max(dp[i+1][j], dp[i][j-1])
```

Unlike a palindromic substring, the characters do not need to be contiguous.

## Unbounded knapsack

Unlike 0/1 knapsack, each item may be used any number of times. Iterate
`w` **forward** so the state `dp[w - weight]` may already include the same item:

```text
for each item i:
    for w from weight[i] to W:
        dp[w] = max(dp[w], value[i] + dp[w - weight[i]])
```

Forward order = reuse allowed; backward order = each item once.

## Partition equal subset

The question "can the array be split into two equal-sum halves?" is subset sum
with target `sum / 2`. If the total is odd, the answer is immediately false.
`dp[s]` records whether some subset reaches sum `s`.

## Bitmask TSP (Held-Karp)

`dp[mask][v]` is the cheapest tour that starts at `0`, visits exactly the
vertices in `mask`, and ends at `v`. Adding a city `u` costs
`dp[mask][v] + dist[v][u]`. There are `2ⁿ` masks and `n` endpoints, so the
algorithm is O(2ⁿ n²) instead of the O(n!) brute force.

## Tree DP

Root the tree and return two values from each subtree: the best weight when the
current vertex is **taken** and when it is **skipped**. If a vertex is taken, its
children must be skipped; if it is skipped, each child may be taken or skipped.
The parent chooses the better combination.

## Digit DP

Count numbers in `[0, N]` whose digits satisfy a property (here: digit sum).
The state is `(position, sum, tight)`, where `tight` means the prefix still
equals `N`'s prefix. Once `tight` is false, the remaining positions are free and
the result can be cached.

## Interval DP: burst balloons

Add a virtual balloon of value 1 at each end. If balloon `k` is the **last** one
burst in the open interval `(left, right)`, it earns
`nums[left] * nums[k] * nums[right]`, and the two subintervals are independent.
Trying every `k` gives `dp[left][right]` in O(n³). The same shape solves matrix
chain multiplication, optimal BST, and polygon triangulation.

## How to design a DP solution

1. Define the state. Ask "what information do I need to describe a subproblem?"
2. Write the recurrence: how does the state depend on smaller states?
3. Choose the order: bottom-up table or top-down recursion with a cache.
4. Find the base cases.
5. Check the space: can you keep only the previous row?

## Run

```bash
./build/bin/algo_fibonacci
./build/bin/algo_knapsack_dp
./build/bin/algo_lis
./build/bin/algo_lcs
./build/bin/algo_edit_distance
./build/bin/algo_coin_change
./build/bin/algo_matrix_chain
./build/bin/algo_rod_cutting
./build/bin/algo_lps
./build/bin/algo_unbounded_knapsack
./build/bin/algo_partition
./build/bin/algo_tsp_bitmask
./build/bin/algo_tree_dp
./build/bin/algo_digit_dp
./build/bin/algo_interval_dp
```

## Exercises

1. Time `fibRecursive(35)` and `fibDP(35)`. Explain the gap.
2. Change the knapsack loop to run forward. Why does that compute the
   *unbounded* knapsack instead of 0/1?
3. In `lis.cpp`, print `tails` after every element. Why does it stay sorted?
4. Reconstruct the actual LCS for `"AGGTAB"` and `"GXTXAYB"`.
5. Compute the edit distance between `"intention"` and `"execution"`.
6. In `coin_change.cpp`, swap the loops in `countCombinations`. What do you get?
7. Add a `dp` table printout to the matrix-chain program and trace it by hand.
