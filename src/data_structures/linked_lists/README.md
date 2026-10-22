# Linked lists

A linked list stores each element in a **node** that also holds a pointer to the
next node. Unlike an array, the elements do not need to sit next to each other
in memory.

```text
head -> [ data | next ] -> [ data | next ] -> [ data | nullptr ]
```

## Files

| File | Idea | Insert | Delete | Search |
| --- | --- | --- | --- | --- |
| `single_linked_list.h` | One pointer per node | O(1) at head, O(n) elsewhere | O(1) at head, O(n) elsewhere | O(n) |
| `doubly_linked_list.h` | `next` **and** `prev` pointers | O(1) at both ends | O(1) at both ends | O(n) |
| `circular_linked_list.h` | Last node points back to the first | O(1) at ends | O(1) at ends | O(n) |
| `ordered_linked_list.h` | Always keeps the list sorted | O(n) | O(n) | O(n) |
| `array_based_list.h` | Array that grows by doubling | O(n) | O(n) | O(n) |
| `skip_list.h` | Several forward levels for fast search | O(log n) avg | O(log n) avg | O(log n) avg |

## How a singly linked list is built

The core is tiny:

```cpp
struct Node {
    T data;
    Node* next;
};
```

The list keeps three fields: `head`, `last`, and `count` (size). Operations are
just pointer rewiring:

- **push_front**: new node points to the old head; update `head`.
- **push_back**: old `last->next` points to the new node; update `last`.
- **pop_front**: move `head` to `head->next`, then delete the old node.
- **insert at index**: walk to the node *before* the position, then rewire.

The `Node` is declared inside the class in some files, so the exact name differs
between implementations. That is normal; focus on the pointer changes.

## Why the tail pointer matters

Without `last`, `push_back` costs O(n) because you must walk the whole list.
Keeping a tail pointer makes appending O(1). This is a good example of spending
one extra pointer to improve a common operation.

## Skip list

`skip_list.h` adds levels of forward pointers. A node with a higher level can
skip many elements, similar to an express train. The file uses a random level
generator and a comparator, and implements `insert`, `erase`, `contains`, and
`printList`.

## Build and run

There is no separate demo target for every list, but the header compiles on its
own. Use the include pattern from the [data structures README](../README.md):

```cpp
#include "data_structures/linked_lists/single_linked_list.h"
```

## Exercises

1. Reverse a singly linked list in place. Draw the three pointers you need.
2. Detect a cycle using Floyd's slow/fast pointers.
3. Why is `DoublyLinkedList` better than `SingleLinkedList` for deleting an
   arbitrary node when you already hold a pointer to it?
4. In `ordered_linked_list.h`, what happens if you insert equal values twice?
