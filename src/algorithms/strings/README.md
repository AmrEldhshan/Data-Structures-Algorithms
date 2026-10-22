# String algorithms

String matching asks where a pattern occurs inside a text. The naive method
compares every position and can cost O(nm). The algorithms here reuse work to
get closer to O(n + m).

## Files

| File | Algorithm | Time | Idea |
| --- | --- | --- | --- |
| `kmp.cpp` | Knuth-Morris-Pratt | O(n + m) | Prefix function avoids re-checking matched characters |
| `z_algorithm.cpp` | Z-algorithm | O(n + m) | `z[i]` = length of the prefix starting at `i` |
| `rabin_karp.cpp` | Rabin-Karp | O(n + m) expected | Rolling hash, verify on a hash match |
| `manacher.cpp` | Manacher | O(n) | Longest palindromic substring using mirrored radii |
| `aho_corasick.cpp` | Aho-Corasick | O(n + total pattern length + matches) | Trie + failure links for many patterns at once |
| `boyer_moore.cpp` | Boyer-Moore | O(nm) worst, sublinear typical | Compare from the right and skip using the bad-character rule |
| `lcp_kasai.cpp` | Kasai LCP | O(n) | LCP between adjacent suffixes in suffix-array order |
| `lcp_two_strings.cpp` | Binary-search LCP | O(n log n) | Longest common prefix of two strings |

## KMP

When a mismatch happens after matching `k` characters, the prefix function
`lps[k-1]` tells us the longest prefix that is also a suffix of the matched
part. We can keep that part and continue instead of restarting at the next text
position.

```text
pattern: a b a b a
lps:     0 0 1 2 3
```

## Z-algorithm

`z[i]` is the length of the longest substring starting at `i` that matches a
prefix of the string. Build `pattern + separator + text`; every position where
`z[i] >= pattern.size()` is a match.

The Z-box `[left, right)` lets us copy values from the mirror position inside
the box, so the total work is linear.

## Rabin-Karp

Hash every window and compare hashes first. A hash match is confirmed with a
real character comparison, so collisions cost time but never give a wrong
answer. This is the algorithm behind plagiarism detectors and multi-pattern
search (with a set of pattern hashes).

## Manacher

Insert `#` separators so odd and even palindromes are handled uniformly:

```text
"abba"  ->  "^#a#b#b#a#$"
```

`p[i]` is the palindrome radius at centre `i`. Mirroring inside the current
rightmost palindrome avoids re-expanding characters we already know match.

## Aho-Corasick

Build a trie of all patterns, then add **failure links** with BFS. The failure
link of a node points to the longest proper suffix that is also a trie prefix.
While scanning the text, follow failure links on a mismatch. Output links let
us report every pattern that ends at the current position, including overlapping
ones. This is the standard multi-pattern search algorithm.

## Boyer-Moore

Compare the pattern against the text from right to left. On a mismatch, the
**bad-character rule** shifts the pattern so the mismatched text character lines
up with its last occurrence in the pattern (or past it). Long skips make the
average case sublinear. The full algorithm also uses the good-suffix rule; this
demo keeps the bad-character rule to stay readable.

## Kasai LCP

For a suffix array `sa`, `lcp[i]` is the longest common prefix of suffixes
`sa[i-1]` and `sa[i]`. Kasai's trick uses the previous answer: when moving from
suffix `i` to suffix `i + 1`, the LCP can drop by at most one. Each character is
examined O(1) times overall, so the array is built in O(n).

## LCP of two strings

Binary search the prefix length. The predicate "the first `length` characters
match" is monotone, so the search is valid. Each comparison costs O(length), so
the total is O(n log n) here; a rolling hash or suffix array makes each check
O(1) expected.

## Run

```bash
./build/bin/algo_kmp
./build/bin/algo_z_algorithm
./build/bin/algo_rabin_karp
./build/bin/algo_manacher
./build/bin/algo_aho_corasick
./build/bin/algo_boyer_moore
./build/bin/algo_lcp_kasai
./build/bin/algo_lcp_two_strings
```

## Exercises

1. Build the prefix function for `"ababaca"` by hand.
2. How many comparisons does naive search make for `"aaaaaa"` and `"aaa"`?
   Compare with KMP.
3. Change the Rabin-Karp base from 257 to 2. What happens to collisions?
4. Manacher returns one longest palindrome. Modify it to count all palindromic
   substrings.
5. Why does the separator have to be a character that cannot appear in the
   pattern or text?
