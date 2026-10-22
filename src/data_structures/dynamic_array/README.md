# Dynamic array

A growable contiguous array built from scratch. It mirrors the core behaviour of
`std::vector`: a pointer to a heap block, a live `size`, and an allocated
`capacity`.

## File

| File | Contents |
| --- | --- |
| `dynamic_array.h` | `DynamicArray<T>`: rule of five, `reserve`, `push_back`, `pop_back`, `insert`, `erase`, `resize`, iterators |

## Growth strategy

When `size == capacity`, allocate twice as much space, copy the live elements,
and release the old block. Although one append can cost O(n), doubling makes the
**amortised** cost O(1).

```text
capacity: 1 -> 2 -> 4 -> 8 -> 16 ...
```

## Complexity

| Operation | Time |
| --- | --- |
| access / front / back | O(1) |
| push_back / pop_back | O(1) amortised |
| insert / erase in the middle | O(n) |
| reserve | O(n) |
| copy | O(n) |
| resize | O(n) |

## Rule of five

The class owns a raw pointer, so it defines a destructor, copy constructor, move
constructor, copy assignment, and move assignment. Copying deep-copies the
buffer; moving transfers ownership and leaves the source empty.

## Example

```cpp
#include "data_structures/dynamic_array/dynamic_array.h"

DynamicArray<int> values;
values.push_back(10);
values.push_back(20);
values.insert(1, 15);
```

## Run the demo

```bash
./build/bin/demo_dynamic_array
```
