# Bit manipulation

Computers store integers as bits. Bit operations are fast and appear in
bitmasks, sets, compression, cryptography, and low-level systems code.

## Files

| File | Contents |
| --- | --- |
| `bit_manipulation.h` | Count set bits, power-of-two check, lowest set bit, get/set/clear/toggle, bit length |
| `../../demos/bit_manipulation_demo.cpp` | Runnable demonstration |

## Useful identities

| Expression | Meaning |
| --- | --- |
| `x & (x - 1)` | Clear the lowest set bit |
| `x & -x` | Isolate the lowest set bit |
| `x \| (1 << i)` | Set bit `i` |
| `x & ~(1 << i)` | Clear bit `i` |
| `x ^ (1 << i)` | Toggle bit `i` |
| `(x >> i) & 1` | Read bit `i` |
| `x && !(x & (x - 1))` | `x` is a power of two |

Two's complement makes `x & -x` work: `-x` is `~x + 1`, so the lowest set bit
survives and everything below it becomes zero.

## Brian Kernighan's popcount

```cpp
while (x != 0) {
    x &= x - 1;
    ++count;
}
```

The loop runs once per **set bit**, not once per bit position. A 64-bit number
with two set bits takes two iterations.

## Why it matters

- Bitmasks represent subsets of up to 64 elements.
- `1 << k` enumerates all subsets of a `k`-element set.
- XOR finds the single unpaired element in an array.
- Bit tricks speed up Fenwick trees, segment trees, and hash functions.

## Run

```bash
./build/bin/demo_bit_manipulation
```

## Exercises

1. Write `isOdd(x)` without `%`.
2. Use `x & -x` to find the lowest set bit of `180`.
3. Reverse the bits of an 8-bit number. How many operations does your version
   need?
4. Count the set bits of `0xFFFFFFFFFFFFFFFF` with both a loop and Brian
   Kernighan's method.
5. Explain why `x ^ x == 0` makes XOR useful for finding a missing number.
