//
// Created by Amr on 6/5/2025.
//

#ifndef RADIXSORT_H
#define RADIXSORT_H

#include <iostream>
#include <vector>
#include <algorithm>

/**
 * @file RadixSort.h
 * @brief Implementation of Radix Sort algorithm using Counting Sort as a subroutine.
 *
 * Radix Sort processes numbers digit by digit starting from the least significant digit (LSD)
 * to the most significant digit (MSD), using a stable sort like Counting Sort at each step.
 *
 * ------------------------------
 * Time Complexity:
 * - Best Case:    O(n * k), in slides = O(d*(n+k)), we assuemd that the k is always 10 then we replace the k with the d that the maximum number of digits
 * - Average Case: O(n * k)
 * - Worst Case:   O(n * k)
 * where k is the number of digits in the maximum number.
 *
 * Space Complexity:
 * - O(n + k)
 *
 * Stable: ✅ Yes
 * In-Place: ❌ No
 */

/**
 * @brief Helper function to get the maximum value in the array.
 */
int getMax(int arr[], int size) {
    int maxVal = arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] > maxVal)
            maxVal = arr[i];
    }
    return maxVal;
}

/**
 * @brief Counting Sort based on the digit represented by exp (exponent).
 *
 * @param arr The array to sort.
 * @param exp The current digit exponent (1, 10, 100, ...).
 */
void countingSortByDigit(int arr[], int size, int exp) {
    int output[1000]; // assume that the maximum value is <= 1000
    int count[10]{0};


    // count digit frequencies
    for (int i = 0; i < size; i++){
        int digit = (arr[i] / exp) % 10;
        count[digit]++;
    }


    // cumulative count
    for (int i = 1; i<=size; i++){
        count[i] += count[i-1];
    }

    // build the output array
    for (int i = size - 1; i>=0;i--){
        int digit = (arr[i] / exp) % 10;
        output[count[digit] - 1] = arr[i];
        count[digit]--;
    }

    // copy stored data back
    // Copy sorted data back
    for (int i = 0; i < size; i++)
        arr[i] = output[i];

}

/**
 * @brief Radix Sort algorithm (LSD variant).
 *
 * @param arr The array to sort.
 */
void radixSort(int arr[], int size) {
    int maxVal = getMax(arr, size);

    for (int exp = 1; maxVal / exp > 0; exp *= 10){
        countingSortByDigit(arr, size, exp);

    }
}

#endif // RADIXSORT_H
