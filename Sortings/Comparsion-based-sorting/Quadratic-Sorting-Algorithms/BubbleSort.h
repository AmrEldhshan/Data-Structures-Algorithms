//
// Created by Amr on 6/4/2025.
//

#ifndef BUBBLESORT_H
#define BUBBLESORT_H

/**
 * @file bubblesort.h
 * @brief Basic generic Bubble Sort implementation using templates.
 *
 * ----------------------------------------------
 * Algorithm: Bubble Sort
 * ----------------------------------------------
 * Compares each adjacent pair and swaps them if they are
 * in the wrong order. Repeats the process for all elements.
 *
 * Time Complexity:
 *   - Best Case:    O(n^2) can be imporved to o(n)
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
 * @brief Sorts an array in ascending order using Bubble Sort.
 *
 * @tparam T The type of elements in the array.
 * @param arr The array to sort.
 * @param n The number of elements in the array.
 */
template <typename T>
void bubbleSort(T arr[], int n) {
	for (int i = 0; i < n - 1; i++) {
		// Compare each adjacent pair and swap if out of order
		for (int j = 0; j < n - i - 1; j++) {
			if (arr[j] > arr[j + 1]) {
				// Swap arr[j] and arr[j+1]
				T temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
		}
	}
}


template <typename T>
void bubbleSortOptimized(T arr[], int n) {
	for (int i = 0; i < n - 1; i++) {
		bool swapped = false;

		for (int j = 0; j < n - i - 1; j++) {
			if (arr[j] > arr[j + 1]) {
				T temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
				swapped = true;
			}
		}

		if (!swapped) {
			// No swaps in this pass → array is already sorted
			break;
		}
	}
}
template <typename T>
void bubbleSortBottomUp(T arr[], int n) {
	for (int i = 0; i < n - 1; i++) {
		for (int j = n - 1; j > i ; --j){
			if (arr[j] < arr[j - 1]) {
				T temp = arr[j];
				arr[j] = arr[j - 1];
				arr[j - 1] = temp;
			}
		}
	}
}

#endif // BUBBLESORT_H
