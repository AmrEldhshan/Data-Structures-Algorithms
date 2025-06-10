//
// Created by Amr on 6/5/2025.
//

#ifndef QUICKSORT_H
#define QUICKSORT_H

/**
 * @file quicksort.h
 * @brief Implementation of Quick Sort algorithm.
 *
 * Quick Sort هو خوارزمية تقسيم وتحكم (Divide and Conquer) لترتيب العناصر.
 * تختار عنصر كـ "pivot" (محور)، وتوزع العناصر بحيث العناصر الأصغر من الـ pivot تكون على اليسار،
 * والعناصر الأكبر منه تكون على اليمين، ثم تطبق الخوارزمية بشكل متكرر على الجزأين.
 *
 * ------------------------------
 * Time Complexity:
 * - Best Case:    O(n log n)  (عندما يتم تقسيم المصفوفة بشكل متوازن)
 * - Average Case: O(n log n)
 * - Worst Case:   O(n^2)      (عندما يكون المحور أقل أو أكبر من كل العناصر تقريباً)
 *
 * Space Complexity:
 * - O(log n) في المتوسط لاستخدام الستاك العودي (recursion stack)
 *
 * Stable: ❌ غير مستقر (قد يغير ترتيب العناصر المتساوية)
 * In-Place: ✅ نعم (لا يحتاج لمصفوفة إضافية كبيرة)
 */

#include <iostream>
#include <iomanip>

/**
 * @brief Partitions the array around a pivot chosen as the first element.
 *        Elements smaller than the pivot are moved to the left,
 *        and elements greater or equal are moved to the right.
 *
 * @param arr The array to partition.
 * @param start The starting index of the subarray.
 * @param end The ending index of the subarray.
 * @return int The final position of the pivot after partitioning.
 */
int partition(int arr[], int start, int end) {
    int pivotValue = arr[start];
    int smallerElementIndex = start;

    // Print initial state
    std::cout << "\n=== Partition Step ===\n";
    std::cout << "Range: [" << start << " to " << end << "]\n";
    std::cout << "Initial array: ";
    for(int i = start; i <= end; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << "\nPivot: " << pivotValue << " (at index " << start << ")\n";
    std::cout << "-------------------\n";

    for (int currentIndex = start + 1; currentIndex <= end; currentIndex++) {
        if (arr[currentIndex] < pivotValue) {
            smallerElementIndex++;
            if (smallerElementIndex != currentIndex) {
                std::cout << "Swap: " << arr[currentIndex] << " (idx " << currentIndex << ") <-> "
                         << arr[smallerElementIndex] << " (idx " << smallerElementIndex << ")\n";
                int temp = arr[smallerElementIndex];
                arr[smallerElementIndex] = arr[currentIndex];
                arr[currentIndex] = temp;
            }
        }
    }

    // Final pivot placement
    if (start != smallerElementIndex) {
        std::cout << "Final pivot placement: " << arr[start] << " (idx " << start << ") <-> "
                 << arr[smallerElementIndex] << " (idx " << smallerElementIndex << ")\n";
        int temp = arr[smallerElementIndex];
        arr[smallerElementIndex] = arr[start];
        arr[start] = temp;
    }

    // Print result
    std::cout << "Result: ";
    for(int i = start; i <= end; i++) {
        if (i == smallerElementIndex) std::cout << "[" << arr[i] << "] ";
        else std::cout << arr[i] << " ";
    }
    std::cout << "\n===================\n";

    return smallerElementIndex;
}

/**
 * @brief الدالة الرئيسية لخوارزمية Quick Sort التي تنفذ الترتيب بشكل متكرر.
 *
 * @param arr المصفوفة التي سيتم ترتيبها.
 * @param start بداية الجزء الذي سيتم ترتيبه.
 * @param end نهاية الجزء الذي سيتم ترتيبه.
 */
void quickSort(int arr[], int start, int end) {
    if (start < end) {
        std::cout << "\nQuickSort called on range [" << start << " to " << end << "]\n";
        int pivotIndex = partition(arr, start, end);
        quickSort(arr, start, pivotIndex - 1);
        quickSort(arr, pivotIndex + 1, end);
    }
}

#endif // QUICKSORT_H
