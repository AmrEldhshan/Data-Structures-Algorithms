# Contributing

This repository exists to **teach how data structures and algorithms are built**.
Contributions are welcome whether you are fixing a bug, adding a new topic, or
improving an explanation.

## The most important rule

Do not delete the teaching comments. They explain *why* a line exists, not just
what it does. If you change the behaviour of a function, update the comment to
match the new behaviour. Never replace a commented implementation with an
unexplained one.

## What makes a good contribution here

- One file per concept, with a clear name in `snake_case`.
- A short comment block at the top describing the idea and its complexity.
- The implementation written to be read: clear variable names, small helpers,
  and comments on the non-obvious steps.
- A small runnable example: either a `main()` in the same file or a test under
  `tests/`.
- No build output, IDE files, or binaries.

## Adding a new data structure

1. Pick the right folder under `src/data_structures/`.
2. Create `my_structure.h` (or `my_structure.cpp` if it has an example `main`).
3. Put an include guard around headers.
4. Add the idea and complexity to the top comment block.
5. Add a folder `README.md` entry if the concept is new.
6. Include your header from a test in `tests/` and assert one or two behaviours.
7. Build it:

   ```bash
   cmake -S . -B build
   cmake --build build --parallel
   ctest --test-dir build --output-on-failure
   ```

## Adding a new algorithm

1. Pick the right folder under `src/algorithms/`.
2. Write the algorithm as a plain function first. Avoid clever tricks that hide
   the idea.
3. Add a comment block:

   ```text
   Idea:            one or two sentences
   Time complexity: best / average / worst
   Space:           extra memory used
   Stable:          yes / no (for sorting)
   ```

4. Add a test in `tests/test_algorithms.cpp`.
5. Update the complexity table in `docs/COMPLEXITY_CHEATSHEET.md` and the
   relevant folder README.

## Naming and style

- Files: `snake_case.h` / `snake_case.cpp`.
- Classes: `PascalCase`.
- Functions and variables: `camelCase` (existing code uses this style).
- Prefer the standard library for containers and utilities.
- Keep each function readable; a comment may be better than a clever one-liner.

## Commit messages

Use a short imperative message:

```text
Add iterative AVL deletion
Fix off-by-one in binary search
Explain double hashing probe sequence
```

## Pull requests

- Explain *what you added* and *which complexity or idea it teaches*.
- Mention how you verified it (build + test command).
- Keep unrelated formatting changes out of the same pull request.

## Code of conduct

Be kind. This is a learning repository: questions and beginner-friendly
explanations are always welcome.
