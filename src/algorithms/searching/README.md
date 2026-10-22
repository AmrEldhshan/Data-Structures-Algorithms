# Searching

Searching asks: *is this value in the collection, and where?*

## Files

| File | Algorithm | Input must be sorted | Time | Space |
| --- | --- | --- | --- | --- |
| `linear_search_iterative.h` | Check each element in a loop | No | O(n) | O(1) |
| `linear_search_recursive.h` | Check one element, recurse on the rest | No | O(n) | O(n) stack |
| `binary_search_iterative.h` | Halve the range in a loop | Yes | O(log n) | O(1) |
| `binary_search_recursive.h` | Halve the range recursively | Yes | O(log n) | O(log n) stack |

Each function returns the index of the target, or `-1` if it is absent.

## The binary search invariant

Keep two indices, `low` and `high`, such that the target can only be inside
`[low, high]`. At each step compare the middle element:

```cpp
if (arr[mid] == target) return mid;
if (arr[mid] < target)  low = mid + 1;
else                    high = mid - 1;
```

The loop stops when `low > high`, which means the range is empty. Writing the
boundary updates correctly is the whole difficulty of binary search.

## Why linear search still matters

- The data may be unsorted, and sorting first may cost more than scanning.
- The collection may be a linked list, where jumping to the middle is O(n).
- Linear search is the baseline you compare against.

## Exercise

Take the array `[2, 4, 6, 8, 10, 12]` and trace `binarySearchIterative` for
`target = 7`. Write down `low`, `high`, and `mid` at every step. How many
comparisons did it take?
