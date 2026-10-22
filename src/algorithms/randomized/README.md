# Randomized algorithms

Randomness can simplify an algorithm or make it faster on average. These
examples use a fixed seed so the demos are repeatable; real code should use a
proper random source.

## File

| File | Algorithm | Time |
| --- | --- | --- |
| `randomized.cpp` | Fisher-Yates shuffle, reservoir sampling | O(n) |

## Fisher-Yates shuffle

Walk from the end of the array. At position `i`, swap with a uniformly random
position in `[0, i]`. Every permutation is equally likely, and the algorithm is
O(n) with O(1) extra space.

The common mistake is to pick from the whole array at every step, which produces
a biased shuffle.

## Reservoir sampling

Choose `k` items from a stream whose length is not known in advance:

1. Put the first `k` items in the reservoir.
2. For item `i` (`i >= k`), pick a random slot in `[0, i]`.
3. If the slot is `< k`, replace that reservoir entry.

Every item ends up in the sample with probability `k / n`.

## Run

```bash
./build/bin/algo_randomized
```

## Exercises

1. Run the shuffle with 100,000 trials and count how often each value lands at
   index 0.
2. Prove that reservoir sampling is uniform.
3. Use `std::random_device` to seed the generator.
4. Modify the shuffle to produce a random permutation of a linked list.
