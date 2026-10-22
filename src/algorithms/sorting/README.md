# Sorting algorithms

Sorting is the classic playground for algorithm analysis. This folder contains
ten sorting algorithms plus randomized selection.

## The O(n²) family

| File | How it works | Stable |
| --- | --- | --- |
| `bubble_sort.h` | Repeatedly swap adjacent out-of-order elements. Includes an optimized early-exit version and a bottom-up version. | Yes |
| `selection_sort.h` | Find the minimum of the unsorted part and swap it to the front. | No |
| `insertion_sort.h` | Insert each element into the already sorted prefix. | Yes |

Insertion sort is the fastest of the three on small or nearly sorted inputs.

## Sub-quadratic algorithms

| File | How it works | Stable |
| --- | --- | --- |
| `shell_sort.h` | Insertion sort with decreasing gaps. | No |
| `merge_sort.h` | Split in half, sort each half, merge. Uses extra arrays. | Yes |
| `quick_sort.h` | Partition around a pivot, then recurse. The pivot here is the first element. | No |
| `heap_sort.h` | Build a max-heap, then move the maximum to the end repeatedly. | No |

Merge sort guarantees O(n log n) but needs O(n) extra space. Quick sort is
usually faster in practice but degrades to O(n²) on already sorted input with a
bad pivot. Heap sort is in-place and always O(n log n).

## Linear-time algorithms

| File | How it works | Requirement |
| --- | --- | --- |
| `counting_sort.h` | Count occurrences, then rebuild the array. | Small integer range |
| `radix_sort.h` | Stable counting sort per digit, least significant first. | Non-negative integers |
| `bucket_sort.h` | Distribute into buckets, sort each bucket, concatenate. | Uniformly distributed values |

These trade memory for speed: O(n + k) time instead of O(n log n).

## Selection

`randomized_select.h` finds the k-th smallest element without fully sorting.
It partitions like quick sort but recurses only into the side containing the
answer, giving O(n) average time.

## Complexity table

| Algorithm | Best | Average | Worst | Space | Stable |
| --- | --- | --- | --- | --- | --- |
| Bubble | O(n) | O(n²) | O(n²) | O(1) | Yes |
| Selection | O(n²) | O(n²) | O(n²) | O(1) | No |
| Insertion | O(n) | O(n²) | O(n²) | O(1) | Yes |
| Shell | O(n log n) | depends | O(n²) | O(1) | No |
| Merge | O(n log n) | O(n log n) | O(n log n) | O(n) | Yes |
| Quick | O(n log n) | O(n log n) | O(n²) | O(log n) | No |
| Heap | O(n log n) | O(n log n) | O(n log n) | O(1) | No |
| Counting | O(n + k) | O(n + k) | O(n + k) | O(k) | Yes |
| Radix | O(d(n + k)) | O(d(n + k)) | O(d(n + k)) | O(n + k) | Yes |
| Bucket | O(n + k) | O(n + k) | O(n²) | O(n + k) | Yes* |

## Run

```bash
./build/bin/dsa_demo        # runs every sorting algorithm on the same array
ctest --test-dir build --output-on-failure
```

## Exercises

1. Add a comparison counter to bubble sort and the optimized bubble sort.
   Compare them on a sorted array.
2. Change the quick sort pivot to the middle element. Does the worst case
   disappear? Why or why not?
3. Why must radix sort use a **stable** digit sort?
4. Implement merge sort without allocating new arrays on every merge.
