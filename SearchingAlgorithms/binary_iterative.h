/*
Binary Search (Iterative)
-------------------------
Performs a binary search on a sorted array using iteration.
Divides the array in half each step.

Time Complexity:  O(log n)
Space Complexity: O(1)
*/

#ifndef BINARY_ITERATIVE_H
#define BINARY_ITERATIVE_H

int binarySearchIterative(int arr[], int size, int target) {
    int low = 0;
    int high = size - 1;

    while (low <= high) {
        int mid = (low + high) / 2;

        if (arr[mid] == target)
            return mid; // Found
        else if (arr[mid] < target)
            low = mid + 1;
        else
            high = mid - 1;
    }
    return -1; // Not found
}

#endif
