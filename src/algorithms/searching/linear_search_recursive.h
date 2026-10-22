/*
Sequential Search (Recursive)
-----------------------------
Recursively checks each element from the start until the
target is found or the end of the array is reached.

Time Complexity:  O(n)
Space Complexity: O(n)  // due to recursive stack
*/

#ifndef SEQUENTIAL_RECURSIVE_H
#define SEQUENTIAL_RECURSIVE_H

int sequentialSearchRecursive(int arr[], int size, int target, int index = 0) {
    if (index >= size)
        return -1; // Base case: not found
    if (arr[index] == target)
        return index; // Found
    return sequentialSearchRecursive(arr, size, target, index + 1);
}

#endif
