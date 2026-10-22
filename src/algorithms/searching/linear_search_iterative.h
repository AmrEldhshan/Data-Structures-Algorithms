/*
Sequential Search (Iterative)
-----------------------------
Implements a simple linear search that checks each element
sequentially until the target is found or the array ends.

Time Complexity:  O(n)
Space Complexity: O(1)
*/

#ifndef SEQUENTIAL_ITERATIVE_H
#define SEQUENTIAL_ITERATIVE_H

int sequentialSearchIterative(int arr[], int size, int target) {
    for (int i = 0; i < size; i++) {
        if (arr[i] == target)
            return i; // Found
    }
    return -1; // Not found
}

#endif
