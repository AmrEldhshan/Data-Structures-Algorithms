# NP-complete problems

These files demonstrate problems for which no known polynomial-time algorithm
exists. They use **backtracking**: try a choice, recurse, and undo the choice if
it fails.

The goal is to see the shape of the search, not to solve large instances. Every
program here is small and readable on purpose.

## Files

| File | Problem | Search space |
| --- | --- | --- |
| `subset_sum.cpp` | Is there a subset with a given sum? | 2ⁿ subsets |
| `knapsack.cpp` | 0/1 knapsack by recursion | 2ⁿ choices |
| `graph_coloring.cpp` | Colour a graph with `m` colours | m^V assignments |
| `hamiltonian_cycle.cpp` | Visit every vertex exactly once and return | V! orderings |
| `traveling_salesman.cpp` | Shortest tour visiting every city | (V-1)! tours |

The comments in `subset_sum.cpp` and `traveling_salesman.cpp` are honest about
the cost: `2^n` subsets and `(n-1)!` tours.

## The backtracking pattern

Most of these programs follow the same skeleton:

```cpp
bool solve(state) {
    if (isComplete(state)) return true;
    for (choice in choices(state)) {
        if (isSafe(choice)) {
            apply(choice);
            if (solve(nextState)) return true;
            undo(choice);            // backtrack
        }
    }
    return false;
}
```

The `undo` step is what makes it backtracking rather than plain recursion.

## Why exponential time is still worth studying

- It teaches systematic search and pruning.
- Some NP-complete problems are small in practice.
- It shows exactly why the polynomial-time DP solutions (like the 0/1 knapsack
  in `algorithms/dynamic_programming/`) are valuable.

## Run

```bash
./build/bin/algo_np_subset_sum
./build/bin/algo_np_knapsack
./build/bin/algo_np_graph_coloring
./build/bin/algo_np_hamiltonian
./build/bin/algo_np_tsp
```

## Exercises

1. Compare the recursive knapsack here with the DP knapsack in
   `algorithms/dynamic_programming/`. Run both on the same input and compare
   the time for `n = 20`.
2. Add a counter for the number of recursive calls in `subset_sum`. How does it
   grow with `n`?
3. Add pruning to the travelling salesman: stop a branch when its partial cost
   is already worse than the best tour found.
