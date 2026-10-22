# Big integer

Arbitrary-precision signed integer arithmetic. Values are stored as base-10^9
limbs in a `std::vector<int>`, least significant limb first. Each limb fits
comfortably in a 32-bit integer, and the base is a power of ten so conversion to
and from strings is simple.

## File

| File | Contents |
| --- | --- |
| `big_integer.h` | `BigInteger`: parsing, printing, comparison, addition, subtraction, multiplication |

## Representation

```text
123456789012345678901234567890
= 123 | 456789012 | 345678901 | 234567890
  ^       ^           ^           ^
  most significant limb ... least significant limb
```

A separate `negative_` flag stores the sign. Zero is never negative.

## Algorithms

| Operation | Method | Time |
| --- | --- | --- |
| parse / print | split/join groups of 9 digits | O(n) |
| compare | sign, then limb count, then limbs | O(n) |
| add / subtract | carry or borrow per limb | O(n) |
| multiply | schoolbook grade-school multiplication | O(n · m) |

Addition of opposite signs reduces to comparing magnitudes and subtracting the
smaller from the larger. Multiplication uses `long long` for the intermediate
product of two 9-digit limbs, which stays below 10^18.

Division and modular arithmetic are not implemented; they are good extensions.

## Example

```cpp
#include "data_structures/big_integer/big_integer.h"

BigInteger a("123456789012345678901234567890");
BigInteger b("987654321098765432109876543210");

std::cout << (a * b).toString() << '\n';
```

## Run the demo

```bash
./build/bin/demo_big_integer
```
