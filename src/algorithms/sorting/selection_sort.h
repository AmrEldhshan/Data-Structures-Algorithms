//
// Created by Amr on 6/5/2025.
//

#ifndef SELECTIONSORT_H
#define SELECTIONSORT_H

/**
 * @file selectionsort.h
 * @brief Basic generic Selection Sort implementation using templates.
 *
 * ----------------------------------------------
 * Algorithm: Selection Sort
 * ----------------------------------------------
 * Repeatedly selects the smallest (or largest) element and moves it
 * to its correct position by swapping.
 *
 * Time Complexity:
 *   - Best Case:    O(n^2)
 *   - Average Case: O(n^2)
 *   - Worst Case:   O(n^2)
 *
 * Space Complexity:
 *   - O(1) — In-place sorting
 *
 * Stable: ❌ No
 * In-Place: ✅ Yes
 */

/**
 * @brief Sorts an array in ascending order using Selection Sort.
 *
 * @tparam T The type of elements in the array.
 * @param arr The array to sort.
 * @param n The number of elements in the array.
 */
template <typename T>
void selectionSort(T arr[], int n) {
	for (int i = 0; i < n - 1; i++) {
		int minIndex = i;

		// Find the index of the smallest element
		for (int j = i + 1; j < n; j++) {
			if (arr[j] < arr[minIndex]) {
				minIndex = j;
			}
		}

		// Swap the smallest element with the current index
		if (minIndex != i) {
			T temp = arr[i];
			arr[i] = arr[minIndex];
			arr[minIndex] = temp;
		}
	}
}

#endif // SELECTIONSORT_H
