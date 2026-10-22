//
// Created by Amr on 6/4/2025.
//

#ifndef INSERTIONSORT_H
#define INSERTIONSORT_H

/**
 * @file insertionsort.h
 * @brief Basic generic Insertion Sort implementation using templates.
 *
 * ----------------------------------------------
 * Algorithm: Insertion Sort
 * ----------------------------------------------
 * Builds a sorted array by inserting each new element
 * into its correct position relative to the sorted portion.
 *
 * Time Complexity:
 *   - Best Case:    O(n)     (already sorted)
 *   - Average Case: O(n^2)
 *   - Worst Case:   O(n^2)
 *
 * Space Complexity:
 *   - O(1) — In-place sorting
 *
 * Stable: ✅ Yes
 * In-Place: ✅ Yes
 */

/**
 * @brief Sorts an array in ascending order using Insertion Sort.
 *
 * @tparam T The type of elements in the array.
 * @param arr The array to sort.
 * @param size The number of elements in the array.
 */
template <typename T>
void insertionSort(T arr[], int size) {
	for (int i = 1; i < size; i++) {
		T current = arr[i];
		int j = i - 1;

		// Shift elements that are greater than current to the right
		while (j >= 0 && arr[j] > current) {
			arr[j + 1] = arr[j];
			j--;
		}

		// Insert current at the correct position
		arr[j + 1] = current;
	}
}

#endif // INSERTIONSORT_H
