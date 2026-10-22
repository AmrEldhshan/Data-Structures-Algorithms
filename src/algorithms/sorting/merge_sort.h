//
// Created by Amr on 6/5/2025.
//

#ifndef MERGESORT_H
#define MERGESORT_H

#include <iostream>
using namespace std;

/**
 * @file mergesort.h
 * @brief Implementation of Merge Sort algorithm.
 *
 * Merge Sort is a classic divide and conquer sorting algorithm.
 * It divides the array into two halves, recursively sorts them,
 * then merges the two sorted halves into one sorted array.
 *
 * ------------------------------
 * Time Complexity:
 * - Best Case:    O(n log n)
 * - Average Case: O(n log n)
 * - Worst Case:   O(n log n)
 *
 * Space Complexity:
 * - O(n): Requires additional temporary array for merging.
 *
 * Stable: ✅ Yes (preserves order of equal elements)
 * In-Place: ❌ No (requires extra space for merging)
 */

/**
 * @brief Merge two sorted subarrays of arr[].
 * The first subarray is arr[left..mid]
 * The second subarray is arr[mid+1..right]
 *
 * @param arr The array containing the subarrays.
 * @param left Left index of the first subarray.
 * @param mid Middle index, ending first subarray.
 * @param right Right index of the second subarray.
 */
void merge(int arr[], int left, int mid, int right) {

    cout << "\nMerging arrays from index " << left << " to " << right << endl;
    cout << "Left subarray: ";
    for(int i = left; i <= mid; i++) cout << arr[i] << " ";
    cout << "\nRight subarray: ";
    for(int i = mid+1; i <= right; i++) cout << arr[i] << " ";
    cout << endl;

    int leftSize = mid - left + 1;
    int rightSize = right - mid;

    int* leftArr = new int[leftSize];
    int* rightArr = new int[rightSize];

    for (int i = 0; i < leftSize; i++) {
        leftArr[i] = arr[left + i];
    }
    for (int i = 0; i < rightSize; i++) {
        rightArr[i] = arr[mid + 1 + i];
    }

    int leftIdx = 0;
    int rightIdx = 0;
    int mergedIdx = left;

    while (leftIdx < leftSize && rightIdx < rightSize) {
        if (leftArr[leftIdx] <= rightArr[rightIdx]) {
            arr[mergedIdx++] = leftArr[leftIdx++];
        } else {
            arr[mergedIdx++] = rightArr[rightIdx++];
        }
    }

    while (leftIdx < leftSize) {
        arr[mergedIdx++] = leftArr[leftIdx++];
    }

    while (rightIdx < rightSize) {
        arr[mergedIdx++] = rightArr[rightIdx++];
    }

    cout << "After merging: ";
    for(int i = left; i <= right; i++) cout << arr[i] << " ";
    cout << endl;

    delete[] leftArr;
    delete[] rightArr;
}

/**
 * @brief Recursive Merge Sort function to sort the array.
 *
 * @param arr The array to sort.
 * @param left Starting index.
 * @param right Ending index.
 */
void mergeSort(int arr[], int left, int right) {
    if(left < right){
        cout << "\nSplitting array from index " << left << " to " << right << endl;
        int mid = (right + left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

#endif // MERGESORT_H
