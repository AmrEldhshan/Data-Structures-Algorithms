# Bitset

A fixed-size sequence of bits packed into 64-bit words. Compared with
`std::vector<bool>`, the representation is explicit and the word operations are
easy to see.

## File

| File | Contents |
| --- | --- |
| `bitset.h` | `Bitset<N>`: set/reset/flip/test, bulk operations, `count`, `any`, `none`, `all`, bitwise operators, `to_string` |

## Representation

```text
wordCount = ceil(N / 64)
index i lives in word i / 64 at bit position i % 64
```

Index `0` is the least significant bit. Unused high bits in the last word are
cleared after operations such as `setAll`, `flipAll`, and `~` so that `count()`
and `to_string()` only see valid bits.

## Operations

| Operation | Time |
| --- | --- |
| set / reset / flip / test | O(1) |
| count | O(N / 64) |
| any / none / all | O(N / 64) |
| bitwise `&`, `|`, `^`, `~` | O(N / 64) |
| `to_string` | O(N) |

`count()` uses `std::popcount`, which compiles to a single instruction on most
modern CPUs.

## Example

```cpp
#include "data_structures/bitset/bitset.h"

Bitset<10> bits;
bits.set(3);
bits.flip(3);
bits.setAll();
bits.reset(0);

std::cout << bits.to_string() << '\n';
```

## Run the demo

```bash
./build/bin/demo_bitset
```
