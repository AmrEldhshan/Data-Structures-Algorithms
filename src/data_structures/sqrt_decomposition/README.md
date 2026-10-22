# Sqrt decomposition

Split an array into blocks of roughly `√n` elements. A range operation handles
whole blocks with a block-level value and at most two partial blocks element by
element.

## File

| File | Contents |
| --- | --- |
| `sqrt_decomposition.h` | `SqrtDecomposition<T>`: range add and range sum |

## Why √n?

- A range touches at most two partial blocks: O(√n) elements.
- It touches at most O(√n) whole blocks.

So both partial work and block work are O(√n). Choosing a different block size
balances the two costs for a specific workload.

## Complexity

| Operation | Time |
| --- | --- |
| build | O(n) |
| range add | O(√n) |
| range sum | O(√n) |
| point access | O(1) |

## Lazy blocks

`blockAdd[block]` stores an addition applied to the whole block. A partial-block
operation pushes the value into the individual elements it touches, and a full
block update only changes `blockAdd` and `blockSum`.

## Run the demo

```bash
./build/bin/demo_sqrt_decomposition
```
