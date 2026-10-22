//
// Created by Amr on 6/5/2025.
//

#ifndef BUCKETSORT_H
#define BUCKETSORT_H

#include <iostream>

/**
 * @file BucketSort.h
 * @brief Implementation of Bucket Sort using static 2D array (no pointers).
 *
 * Bucket Sort works by distributing elements into multiple "buckets",
 * sorting each bucket, and then concatenating them back.
 *
 * Time Complexity:
 * - Best Case: O(n + k)   in slides its O(n) + ∑(i=1 -> n-1) O(ni^2)
 * - Average Case: O(n + k)
 * - Worst Case: O(n^2)
 *
 * Space Complexity: O(n + k)
 * Stable: ✅ (if internal sort is stable)
 * In-Place: ❌ (needs additional buckets)
 */

// Constants
const int MAX_BUCKETS = 10;   // Number of buckets
const int MAX_SIZE = 1000;    // Maximum size for each bucket (adjust as needed)

/**
 * @brief Sorts a bucket using Insertion Sort (Stable)
 */
void insertionSort(int bucket[], int size) {
    for (int i = 1; i < size; ++i) {
        int key = bucket[i];
        int j = i - 1;

        // Shift elements greater than key to the right
        while (j >= 0 && bucket[j] > key) {
            bucket[j + 1] = bucket[j];
            j--;
        }

        // Insert the key into the correct position
        bucket[j + 1] = key;
    }
}

/**
 * @brief Main Bucket Sort algorithm
 *
 * @param arr[] The array to sort
 * @param n     The size of the array
 */
void bucketSort(int arr[], int n) {
    // Step 1: Find the maximum value in the array
    int maxVal = arr[0];
    for (int i = 1; i < n; ++i) {
        if (arr[i] > maxVal)
            maxVal = arr[i];
    }

    // Step 2: Initialize 2D buckets and size array
    int buckets[MAX_BUCKETS][MAX_SIZE] = {0}; // [10][1000] each row elements is a bucket
    int bucketSizes[MAX_BUCKETS] = {0};  // Track the number of elements in each bucket

    // Step 3: Distribute array elements into buckets
    for (int i = 0; i < n; ++i) {
        int index = (arr[i] * MAX_BUCKETS) / (maxVal + 1); // Normalize value to bucket index
        // This does Normalization for the element, so that it turns from the range [0, Maxval] to the range [0, max_buckets - 1]. and avoid deviding on zero or avoid storing the maximum in zero -> 13 / 13 = 1 -> *10 = 10 -> bucket index is zero
        buckets[index][bucketSizes[index]++] = arr[i];     // Insert into appropriate bucket in a cumulative way for the bucket sizes and a cumulative filling for the buckts to store the dublicating elemetns next to other
    }

    // Step 4: Sort each bucket using insertion sort
    for (int i = 0; i < MAX_BUCKETS; ++i) {
        insertionSort(buckets[i], bucketSizes[i]);
    }

    // Step 5: Concatenate all buckets back into original array
    int idx = 0;
    for (int i = 0; i < MAX_BUCKETS; ++i) {
        for (int j = 0; j < bucketSizes[i]; ++j) {
            arr[idx++] = buckets[i][j];
        }
    }
}

#endif // BUCKETSORT_H
