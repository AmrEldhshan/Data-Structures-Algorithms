# Strings

## Files

| File | Structure | Use |
| --- | --- | --- |
| `suffix_array.cpp` | Suffix array (doubling) | Substring search, suffix ordering |
| `rope.h` | Rope | Tree of string chunks with O(log n) edits |
| `suffix_automaton.h` | Suffix automaton | All substrings, occurrences, distinct count |

## Suffix automaton

A suffix automaton is a minimal DFA that recognises every substring of a text.
Each state has a `link` (suffix link) and `length` (longest string in the
state). Building it is O(n); checking a pattern is O(m). Subtree sizes over the
suffix-link tree give the number of occurrences of each pattern.

## Suffix array

A suffix array is the list of all suffixes of a string, sorted
lexicographically. It is a compact index for substring search, pattern
matching, and compression.

For `"banana"`:

```text
suffixes (0-based start)        sorted suffixes
0: banana                      5: a
1: anana                       3: ana
2: nana                        1: anana
3: ana                         0: banana
4: na                          4: na
5: a                           2: nana
```

The suffix array is the list of starting indices in sorted order:

```text
[5, 3, 1, 0, 4, 2]
```

## How this implementation builds it

`src/data_structures/strings/suffix_array.cpp` uses the **doubling** technique:

1. Rank each character.
2. Sort suffixes by the pair `(rank[i], rank[i + 2^k])`.
3. Double `k` until `2^k >= n`.
4. After O(log n) rounds, the ranks give the suffix order.

The implementation uses a hand-written heap sort (`sort`) for the rounds, so its
construction time is **O(n log² n)**. A radix-sort version can reach O(n log n).

## Searching

To search for a pattern, binary-search the suffix array. Each comparison checks
the pattern against a suffix. With the array alone, a search costs
`O(m log n)` comparisons, where `m` is the pattern length.

## Credits

The file header credits the original student authors:

```text
20231157: Marawan Mohamed badr
20231116: Amr Khaled Ahmed
20230387: Marwan Mohamed Hassen
20230367: Mahmoud Ibraheem Mohamed
```

## Run

```bash
./build/bin/ds_suffix_array
./build/bin/demo_suffix_automaton
```

## Exercises

1. Build the suffix array for `"mississippi"` by hand.
2. Why does doubling only need O(log n) rounds?
3. Which data structure would you add to make pattern matching O(m + log n)?
   (Hint: the longest common prefix array.)
