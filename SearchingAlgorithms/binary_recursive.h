/*
Binary Search (Recursive)
-------------------------
Uses recursion to divide the array and search for the target
in either the left or right half.

Time Complexity:  O(log n)
Space Complexity: O(log n)
*/

#ifndef BINARY_RECURSIVE_H
#define BINARY_RECURSIVE_H

int binarySearchRecursive(int arr[], int low, int high, int target) {
    if (low > high)
        return -1; // Base case: not found

    int mid = (low + high) / 2;

    if (arr[mid] == target)
        return mid; // Found
    else if (arr[mid] < target)
        return binarySearchRecursive(arr, mid + 1, high, target);
    else
        return binarySearchRecursive(arr, low, mid - 1, target);
}

#endif
