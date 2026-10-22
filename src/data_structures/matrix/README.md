# Matrix

A small dense matrix stored in **row-major** order. It is used by the matrix
exponentiation and Gaussian elimination examples, and it keeps the
implementation visible instead of hiding it behind a library.

## File

| File | Contents |
| --- | --- |
| `matrix.h` | `Matrix<T>`: construction, element access, addition, multiplication, transpose, identity, equality, printing |

## Indexing

```text
index(row, column) = row * columns + column
```

All access goes through `operator()`, which checks the bounds. The private
`checkedSize` helper also rejects non-positive dimensions.

## Operations

| Operation | Time | Notes |
| --- | --- | --- |
| element access | O(1) | bounds-checked |
| addition | O(rows × columns) | dimensions must match |
| multiplication | O(n³) for n × n | `columns == other.rows` |
| transpose | O(rows × columns) | returns a new matrix |
| identity | O(n²) | static helper |

The multiplication loop is ordered `row → middle → column` so the inner loop
walks contiguous memory in the right-hand matrix. Strassen and blocking are
possible improvements, but they obscure the basic algorithm.

## Example

```cpp
#include "data_structures/matrix/matrix.h"

Matrix<long long> a(2, 2, 0);
a(0, 0) = 1;
a(0, 1) = 1;
a(1, 0) = 1;

Matrix<long long> b = a * a;
```

## Run the demo

```bash
./build/bin/demo_matrix
```
