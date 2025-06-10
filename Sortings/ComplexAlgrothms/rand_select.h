//
// Created by Amr on 6/5/2025.
//

#ifndef RANDOMIZED_SELECT_H
#define RANDOMIZED_SELECT_H

#include <iostream>
#include <vector>
#include <random>
#include <algorithm>

/**
 * @file randomized_select.h
 * @brief Implementation of Randomized-Select algorithm (QuickSelect) to find the i-th smallest element.
 *
 * -------------------------------------------------
 * Algorithm: Randomized Selection (QuickSelect)
 * -------------------------------------------------
 * This algorithm is a randomized version of the QuickSelect algorithm.
 * It selects a random pivot and partitions the array, recursively searching
 * in the appropriate partition for the i-th smallest element.
 *
 * Time Complexity:
 *   - Best Case:    O(n)
 *   - Average Case: O(n)
 *   - Worst Case:   O(n^2) (rare due to randomization)
 *
 * Space Complexity:
 *   - O(1) auxiliary (in-place operations)
 *
 * Stable: ❌ No
 * In-Place: ✅ Yes
 */

using namespace std;

// Random number generator
random_device rd;
mt19937 gen(rd());

/**
 * @brief Partitions the array around a randomly chosen pivot.
 *
 * @param array The array to partition.
 * @param left The starting index of the subarray.
 * @param right The ending index of the subarray.
 * @return int Index of the pivot after partitioning.
 */
int randomPartition(vector<int>& array, int left, int right) {
    // Choose a random pivot index between left and right
    uniform_int_distribution<> dist(left, right);
    int pivotIndex = dist(gen);

    // Move the chosen pivot to the end
    swap(array[pivotIndex], array[right]);

    int pivot = array[right];
    int smallerIndex = left - 1;

    for (int current = left; current < right; ++current) {
        if (array[current] <= pivot) {
            ++smallerIndex;
            swap(array[smallerIndex], array[current]);
        }
    }

    // Place pivot in its correct position
    swap(array[smallerIndex + 1], array[right]);
    return smallerIndex + 1;
}

/**
 * @brief Finds the i-th smallest element in the array using Randomized Selection.
 *
 * @param array The array containing elements.
 * @param left The starting index of the subarray.
 * @param right The ending index of the subarray.
 * @param orderStatistic The i-th smallest element to find (1-based index).
 * @return int The i-th smallest element in array[left..right].
 */
int randomizedSelect(vector<int>& array, int left, int right, int orderStatistic) {
    // Base case: only one element
    if (left == right)
        return array[left];

    // Partition around a random pivot
    int pivotIndex = randomPartition(array, left, right);

    // Rank of pivot in current subarray
    int pivotRank = pivotIndex - left + 1;

    if (orderStatistic == pivotRank)
        return array[pivotIndex];  // Found the i-th smallest
    else if (orderStatistic < pivotRank)
        return randomizedSelect(array, left, pivotIndex - 1, orderStatistic);
    else
        return randomizedSelect(array, pivotIndex + 1, right, orderStatistic - pivotRank);
}


/**
 * @brief Partition function using the last element as the pivot.
 *
 * @param array The input array to partition.
 * @param leftIndex Starting index of the partition range.
 * @param rightIndex Ending index of the partition range.
 * @return The final index position of the pivot element.
 */
int partitionArray(vector<int>& array, int leftIndex, int rightIndex) {
    int pivotValue = array[rightIndex];
    int pivotFinalIndex = leftIndex - 1;

    for (int currentIndex = leftIndex; currentIndex < rightIndex; ++currentIndex) {
        if (array[currentIndex] <= pivotValue) {
            ++pivotFinalIndex;
            swap(array[pivotFinalIndex], array[currentIndex]);
        }
    }

    swap(array[pivotFinalIndex + 1], array[rightIndex]);
    return pivotFinalIndex + 1;
}

/**
 * @brief Finds the k-th smallest element in the array using deterministic pivot QuickSelect.
 *
 * @param array The input array.
 * @param leftIndex The starting index of the current subarray.
 * @param rightIndex The ending index of the current subarray.
 * @param orderStatistic The desired k-th smallest element (1-based index).
 * @return The value of the k-th smallest element.
 */
int deterministicSelect(vector<int>& array, int leftIndex, int rightIndex, int orderStatistic) {
    if (leftIndex == rightIndex)
        return array[leftIndex];

    int pivotIndex = partitionArray(array, leftIndex, rightIndex);
    int rank = pivotIndex - leftIndex + 1;  // 1-based rank of pivot in current subarray

    if (orderStatistic == rank)
        return array[pivotIndex];
    else if (orderStatistic < rank)
        return deterministicSelect(array, leftIndex, pivotIndex - 1, orderStatistic);
    else
        return deterministicSelect(array, pivotIndex + 1, rightIndex, orderStatistic - rank);
}
#endif // RANDOMIZED_SELECT_H
