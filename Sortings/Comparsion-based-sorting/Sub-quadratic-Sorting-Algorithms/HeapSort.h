//
// Created by Amr on 6/5/2025.
//

#ifndef HEAPSORT_H
#define HEAPSORT_H

/**
 * @file heapsort.h
 * @brief Heap Sort implementation using templates.
 *
 * ----------------------------------------------
 * Algorithm: Heap Sort (Max Heap)
 * ----------------------------------------------
 * Steps:
 * 1. Build a max heap from the input array.
 * 2. Repeatedly extract the maximum element from the heap
 *    and move it to the end of the array.
 *
 * Time Complexity:
 *   - Best Case:    O(n log n)
 *   - Average Case: O(n log n)
 *   - Worst Case:   O(n log n)
 *
 * Space Complexity:
 *   - O(1) — In-place sorting
 *
 * Stable: ❌ No
 * In-Place: ✅ Yes
 */

/**
 * @brief Maintains the max heap property for a subtree rooted at index 'rootIndex'.
 *
 * @tparam T The type of elements in the array.
 * @param array The array representing the heap.
 * @param heapSize The size of the heap within the array.
 * @param rootIndex The root index of the subtree to heapify.
 */
template <typename T>
void heapify(T array[], int heapSize, int rootIndex) {
    int largestIndex = rootIndex;               // Initialize largest as root
    int leftChildIndex = 2 * rootIndex + 1;     // Left child index
    int rightChildIndex = 2 * rootIndex + 2;    // Right child index

    // If left child exists and is greater than root
    if (leftChildIndex < heapSize && array[leftChildIndex] > array[largestIndex]) {
        largestIndex = leftChildIndex;
    }

    // If right child exists and is greater than current largest
    if (rightChildIndex < heapSize && array[rightChildIndex] > array[largestIndex]) {
        largestIndex = rightChildIndex;
    }

    // If largest is not root, swap and continue heapifying
    if (largestIndex != rootIndex) {
        T temp = array[rootIndex];
        array[rootIndex] = array[largestIndex];
        array[largestIndex] = temp;

        heapify(array, heapSize, largestIndex);
    }
}

/**
 * @brief Sorts the array in ascending order using Heap Sort algorithm.
 *
 * @tparam T The type of elements in the array.
 * @param array The array to sort.
 * @param size The number of elements in the array.
 */
template <typename T>
void heapSort(T array[], int size) {
    // Build max heap
    for (int i = (size / 2) - 1; i >= 0; i--) {
        heapify(array, size, i);
    }

    // Extract elements one by one from heap or you can simply outout in descending order
    for (int i = size - 1; i > 0; i--) {
        // Move current root (max element) to the end
        T temp = array[0];
        array[0] = array[i];
        array[i] = temp;

        // Heapify reduced heap
        heapify(array, i, 0);
    }
}

#endif // HEAPSORT_H
