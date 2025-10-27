//
// Created by Amr on 6/5/2025.
//

#ifndef COUNTSORT_H
#define COUNTSORT_H

#include <vector>
#include <iostream>
using namespace std;

/**
 * @file CountSort.h
 * @brief Implementation of Counting Sort algorithm.
 *
 * Counting Sort is an integer sorting algorithm suitable for sorting
 * elements when the range of input data (max value) is not significantly larger than the number of elements.
 * It counts occurrences of each distinct element and calculates positions.
 *
 * Time Complexity:
 * - Best, Average, Worst Case: O(n + k)
 *   where n = number of elements, k = range of input values.
 *
 * Space Complexity:
 * - O(n + k): requires extra arrays for counting and output.
 *
 * Stable: ✅ Yes
 * In-Place: ❌ No (uses additional space)
 */

/**
 * @brief Sorts an array of non-negative integers using Counting Sort.
 *
 * @param arr The input array to sort.
 * @param size The number of elements in the array.
 */
void countSort(int arr[], int size) {
    if (size <= 0) return;

    // 1. Find the maximum value in the array
    int maxValue = arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] > maxValue) {
            maxValue = arr[i];
        }
    }

    // 2. Create a count array to store frequencies
    vector<int> count(maxValue + 1, 0);

    // 3. Count occurrences of each value
    for (int i = 0; i < size; i++) {
        count[arr[i]]++;
    }


    // 4. Calculate cumulative count
    for (int i = 1; i <= maxValue; i++) {
        count[i] += count[i - 1];
    }

    // 5. Create output array
    vector<int> output(size);

    // 6. Build the output array (going backwards for stability)
    for (int i = size - 1; i >= 0; i--) {
        output[count[arr[i]] - 1] = arr[i];
        count[arr[i]]--;
    }

    // 7. Copy back to original array
    for (int i = 0; i < size; i++) {
        arr[i] = output[i];
    }

}

#endif // COUNTSORT_H
