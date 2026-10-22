# Heaps

A **binary heap** is a complete binary tree stored in an array. No pointers are
needed: the tree shape is implied by the indices.

```text
index:   0    1    2    3    4    5
value:  50   30   40   10   20   35

parent(i) = (i - 1) / 2
left(i)   = 2 * i + 1
right(i)  = 2 * i + 2
```

In a **max-heap**, every parent is greater than or equal to its children, so the
maximum is always at index `0`. A **min-heap** is the mirror image.

## Files

| File | What it is |
| --- | --- |
| `heap.h` | `Heap`: integer max-heap with `insert`, `extractMax`, `extractMin`, `heapSort`, `buildMaxHeap` |
| `max_heap.h` | `MaxHeap<T>`: template version for any comparable type |
| `max_priority_queue.h` | `MaxPriorityQueue`: priority-queue operations on top of a heap |
| `min_heap.h` | `MinHeap<T>`: template min-heap with `push`, `pop`, `top` |
| `min_max_heap.h` | `MinMaxHeap<T>`: O(1) minimum and maximum |
| `binomial_heap.h` | `BinomialHeap<T>`: collection of binomial trees with meld |
| `pairing_heap.h` | `PairingHeap<T>`: meldable heap with pairing extract |
| `fibonacci_heap.h` | `FibonacciHeap<T>`: lazy tree collection, O(1) insert |

## The two core operations

### heapifyUp (used by insert)

Place the new value at the end of the array, then swap it with its parent while
it is larger. It rises at most the height of the tree: O(log n).

### heapifyDown (used by extract)

After removing the root, move the last element to the root. Then repeatedly swap
it with its larger child until the heap property returns: O(log n).

## Build a heap in O(n)

Calling `insert` n times costs O(n log n). Building bottom-up is faster:

```cpp
for (int i = size / 2 - 1; i >= 0; --i)
    heapifyDown(i);
```

Most nodes are near the bottom, so the total work is O(n). `buildMaxHeap()` in
`heap.h` uses this idea to restore the heap after `heapSort()`.

## Complexity

| Operation | Time |
| --- | --- |
| peek max | O(1) |
| insert | O(log n) |
| extract max / min | O(log n)* |
| build heap | O(n) |
| heap sort | O(n log n) |
| search for arbitrary value | O(n) |

\* `extractMin` scans the array in this implementation, so it is O(n). A
min-heap would make it O(log n).

## Run the demos

```bash
./build/bin/demo_heap
./build/bin/demo_min_heap
./build/bin/demo_min_max_heap
./build/bin/demo_binomial_heap
./build/bin/demo_pairing_heap
./build/bin/demo_fibonacci_heap
```

## Exercise

Insert `10, 30, 20, 5, 15` into a max-heap and draw the array after each
insertion. Then call `extractMax()` and draw it again.
