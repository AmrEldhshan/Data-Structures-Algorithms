# Queues

A queue is **FIFO**: the first element enqueued is the first one dequeued. Think
of a line at a ticket counter.

```text
front -> [ 10 ] [ 20 ] [ 30 ] <- rear
dequeue removes 10; enqueue adds after 30
```

## Files

| File | Backing storage | Enqueue | Dequeue | Notes |
| --- | --- | --- | --- | --- |
| `queue.h` | Singly linked list | O(1) | O(1) | Keeps `front` and `rear` |
| `singly_linked_queue.h` | Singly linked list | O(1) | O(1) | Minimal FIFO |
| `doubly_linked_queue.h` | Doubly linked list | O(1) | O(1) | O(1) at both ends |
| `array_queue.h` | Dynamic array | O(1) amortized | O(1) | Resizes when full |
| `circular_array_queue.h` | Fixed array with wraparound | O(1) | O(1) | Reuses freed slots |
| `deque.h` | Growable circular buffer | O(1) amortized | O(1) amortized | Push/pop at both ends |
| `priority_queue.h` | Sorted linked list | O(n) | O(1) | Highest priority first |
| `heap_priority_queue.h` | Binary heap | O(log n) | O(log n) | Built on `../heaps/heap.h` |

## The circular array idea

A plain array queue wastes space after dequeue:

```text
[ _ _ 30 40 50 ]   // 10 and 20 were removed; the front moved forward
```

A circular queue treats the array as a ring:

```cpp
rear = (rear + 1) % capacity;
front = (front + 1) % capacity;
```

When `rear + 1 == front`, the queue is full. This is why the class tracks both
indices instead of shifting elements.

## Deque

A double-ended queue supports `pushFront`, `pushBack`, `popFront`, and
`popBack`. The implementation is a circular buffer that doubles when full, so
both ends stay `O(1)` amortized. It is the structure behind sliding-window
algorithms and work-stealing schedulers.

## Priority queues

A priority queue is not FIFO. Each element has a priority, and the highest
priority leaves first. The linked-list version scans/keeps order on insert; the
heap version uses `heapifyUp` and `heapifyDown`, giving O(log n) operations.

`heap_priority_queue.h` includes:

```cpp
#include "data_structures/heaps/heap.h"
```

so the include path must contain `src/`.

## Complexity summary

| Structure | Enqueue | Dequeue | Peek |
| --- | --- | --- | --- |
| Linked queue | O(1) | O(1) | O(1) |
| Circular array queue | O(1) | O(1) | O(1) |
| Sorted priority queue | O(n) | O(1) | O(1) |
| Heap priority queue | O(log n) | O(log n) | O(1) |
| Deque (either end) | O(1) amortized | O(1) amortized | O(1) |

## Exercise

Enqueue `1, 2, 3, 4` into a circular queue of capacity 4, dequeue twice, then
enqueue `5, 6`. Draw the array after each step. Where do `5` and `6` go?
