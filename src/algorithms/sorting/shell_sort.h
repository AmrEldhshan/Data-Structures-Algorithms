//
// Created by Amr on 6/5/2025.
//

#ifndef SHELLSORT_H
#define SHELLSORT_H

/**
 * @file shellsort.h
 * @brief Implementation of Shell Sort algorithm.
 *
 * Shell Sort is an optimized version of Insertion Sort that allows the exchange of far-apart elements.
 * It reduces the total number of shifts/swaps needed by initially comparing distant elements.
 *
 * ------------------------------------------------------------
 * Time Complexity (depends on gap sequence):
 * - Best Case:    O(n log n)
 * - Average Case: O(n^3/2) or better with optimized gaps
 * - Worst Case:   O(n^2) using basic gaps like n/2, n/4, ...
 *
 * Space Complexity:
 * - O(1): In-place sorting, requires no additional memory.
 *
 * Stable: ❌ Not guaranteed
 * In-Place: ✅ Yes
 */

/**
 * @brief Sorts an array in ascending order using the Shell Sort algorithm.
 *
 * @param arr The array to be sorted.
 * @param size The number of elements in the array.
 */
void ShellSort(int arr[], int size) {
	// Start with a large gap, then reduce the gap
	for (int gap = size / 2; gap > 0; gap /= 2) {

		// Perform a gapped insertion sort for this gap size
		for (int i = gap; i < size; i++) {
			int current = arr[i];
			int j = i;

			// Shift earlier elements that are greater than current
			while (j >= gap && arr[j - gap] > current) {
				arr[j] = arr[j - gap];
				j -= gap;
			}

			// Insert the current element into the correct location
			arr[j] = current;
		}
	}
}

#endif // SHELLSORT_H
