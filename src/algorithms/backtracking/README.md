# Backtracking

Backtracking builds a solution one choice at a time. After recursing, it **undoes**
the choice and tries the next one. The recursion tree can be huge, so pruning
invalid branches early is what makes the approach practical.

## Files

| File | Problem | Pruning |
| --- | --- | --- |
| `n_queens.cpp` | Place `n` queens with no attacks | Column and diagonal sets |
| `sudoku_solver.cpp` | Fill a 9x9 Sudoku | Row, column, and box checks |
| `permutations.cpp` | Permutations, combinations, subsets | Loop bounds |
| `rat_in_maze.cpp` | Find a path through a grid | Walls and visited cells |
| `palindrome_partitioning.cpp` | Split a string into palindromes | Palindrome check |

The NP-complete folder also uses backtracking for subset sum, knapsack,
colouring, Hamiltonian cycle, and TSP.

## N-Queens

Place one queen per row. A column is rejected if it is already used. Diagonals
are identified by `row + column` and `row - column`:

```text
"\" diagonal: row - column is constant
"/" diagonal: row + column is constant
```

The 8-Queens problem has 92 solutions. The demo prints the first one.

## Sudoku

Find an empty cell, try digits `1..9`, and recurse. `canPlace` checks the row,
column, and 3x3 box. If no digit fits, return `false` and let the caller undo
its previous choice.

## Permutations, combinations, subsets

All three share the same shape:

```text
choose
recurse
unchoose
```

- **Permutations:** swap the current position with each later position.
- **Combinations:** start the next loop at `i + 1` so order does not matter.
- **Subsets:** at each element, branch into "exclude" and "include".

## Rat in a maze

Mark the current cell, try the allowed moves (here right and down), and unmark
it when every branch fails. The unmark step is the **backtrack**: without it,
failed branches would block valid paths that share cells.

## Palindrome partitioning

At each start index, try every end index. If `text[start..end]` is a palindrome,
choose it and recurse on `end + 1`. The current list is the partial partition;
when `start` reaches the end, the partition is complete.

## Run

```bash
./build/bin/algo_n_queens
./build/bin/algo_sudoku
./build/bin/algo_permutations
./build/bin/algo_rat_in_maze
./build/bin/algo_palindrome_partition
```

## Exercises

1. Count the recursive calls for 4-Queens. How many are pruned?
2. Modify N-Queens to print all 92 solutions for `n = 8`.
3. Solve a Sudoku with a cell that has no valid digit. What does the program
   print?
4. Generate permutations of a string with duplicate letters without duplicates
   in the output. What extra check is needed?
5. Why is the "include/exclude" subset recursion `O(2ⁿ)`?
