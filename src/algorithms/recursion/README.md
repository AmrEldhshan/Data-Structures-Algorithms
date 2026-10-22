# Recursion

A recursive function solves a problem by calling itself on a smaller input. Two
things are required:

1. **Base case** — the smallest input, solved directly.
2. **Recursive case** — reduce the input and call the function again.

Without a base case (or with a wrong one) the calls never stop, and the stack
overflows.

## Files

`recursion_examples.h` contains:

### Factorial

```text
n! = n * (n - 1)!        for n > 1
0! = 1! = 1              base case
```

Time O(n), space O(n) for the call stack.

### Tower of Hanoi

Move `n` disks from `source` to `target` using `auxiliary`, one disk at a time,
never placing a larger disk on a smaller one.

```text
move(n, source, auxiliary, target)
    move(n-1, source, target, auxiliary)
    move disk n from source to target
    move(n-1, auxiliary, source, target)
```

The number of moves is **2ⁿ - 1**, so the time is O(2ⁿ). This is the standard
example of an exponential algorithm that is still useful for teaching.

## How to trace recursion

Draw the call tree. For `move(3, A, B, C)`:

```text
move(3, A, B, C)
├── move(2, A, C, B)
│   ├── move(1, A, B, C)
│   ├── move disk 2 A -> B
│   └── move(1, C, A, B)
├── move disk 3 A -> C
└── move(2, B, A, C)
```

Every node is one function call. The depth of the tree is the maximum stack
size.

## Exercise

Change the base case of `solveTowerOfHanoi` back to `numbersOfDisks == 1` without
the `return`. Run it with 2 disks. What goes wrong, and why?
