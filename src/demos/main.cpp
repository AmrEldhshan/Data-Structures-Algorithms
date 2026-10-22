/*
============================================================
 Educational tour of the Data Structures & Algorithms repo
============================================================

This file is intentionally small. It shows how to include and
call the header-only implementations that live under:

    src/algorithms/sorting/
    src/algorithms/searching/
    src/algorithms/recursion/

Every implementation is written for learning: plain loops,
plain recursion, and comments that explain the idea. Read the
header beside each call to see HOW the algorithm works.
*/

#include "algorithms/recursion/recursion_examples.h"
#include "algorithms/searching/binary_search_iterative.h"
#include "algorithms/searching/binary_search_recursive.h"
#include "algorithms/searching/linear_search_iterative.h"
#include "algorithms/searching/linear_search_recursive.h"
#include "algorithms/sorting/bubble_sort.h"
#include "algorithms/sorting/bucket_sort.h"
#include "algorithms/sorting/counting_sort.h"
#include "algorithms/sorting/heap_sort.h"
#include "algorithms/sorting/insertion_sort.h"
#include "algorithms/sorting/merge_sort.h"
#include "algorithms/sorting/quick_sort.h"
#include "algorithms/sorting/radix_sort.h"
#include "algorithms/sorting/selection_sort.h"
#include "algorithms/sorting/shell_sort.h"

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

static void printArray(const string& label, const vector<int>& values) {
    cout << label;
    for (int value : values) {
        cout << ' ' << value;
    }
    cout << '\n';
}

static vector<int> sortWith(const vector<int>& input,
                            void (*sortFunction)(int*, int)) {
    vector<int> copy = input;
    sortFunction(copy.data(), static_cast<int>(copy.size()));
    return copy;
}

static vector<int> sortWithMerge(const vector<int>& input) {
    vector<int> copy = input;
    mergeSort(copy.data(), 0, static_cast<int>(copy.size()) - 1);
    return copy;
}

static vector<int> sortWithQuick(const vector<int>& input) {
    vector<int> copy = input;
    quickSort(copy.data(), 0, static_cast<int>(copy.size()) - 1);
    return copy;
}

static void runSortingTour() {
    cout << "\n=== Sorting algorithms ===\n";

    const vector<int> input = {42, 7, 19, 3, 88, 15, 42, 1, 23, 5};
    printArray("input          :", input);

    const vector<pair<string, vector<int>>> results = {
        {"bubble sort    :", sortWith(input, bubbleSort<int>)},
        {"selection sort :", sortWith(input, selectionSort<int>)},
        {"insertion sort :", sortWith(input, insertionSort<int>)},
        {"shell sort     :", sortWith(input, ShellSort)},
        {"heap sort      :", sortWith(input, heapSort<int>)},
        {"count sort     :", sortWith(input, countSort)},
        {"radix sort     :", sortWith(input, radixSort)},
        {"bucket sort    :", sortWith(input, bucketSort)},
        {"merge sort     :", sortWithMerge(input)},
        {"quick sort     :", sortWithQuick(input)},
    };

    for (const auto& result : results) {
        printArray(result.first, result.second);
        if (!is_sorted(result.second.begin(), result.second.end())) {
            cout << "  [warning] this result is not sorted\n";
        }
    }
}

static void runSearchingTour() {
    cout << "\n=== Searching algorithms ===\n";

    int sortedValues[] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19};
    const int size = static_cast<int>(sizeof(sortedValues) / sizeof(sortedValues[0]));
    const int target = 13;

    cout << "sorted array   :";
    for (int value : sortedValues) {
        cout << ' ' << value;
    }
    cout << "\ntarget         : " << target << '\n';

    cout << "binary (iter)  : index " << binarySearchIterative(sortedValues, size, target) << '\n';
    cout << "binary (rec)   : index " << binarySearchRecursive(sortedValues, 0, size - 1, target) << '\n';
    cout << "linear (iter)  : index " << sequentialSearchIterative(sortedValues, size, target) << '\n';
    cout << "linear (rec)   : index " << sequentialSearchRecursive(sortedValues, size, target) << '\n';
}

static void runRecursionTour() {
    cout << "\n=== Recursion examples ===\n";

    cout << "5!             : " << Factorial(5) << '\n';
    cout << "Tower of Hanoi with 3 disks:\n";
    solveTowerOfHanoi(3, 'A', 'B', 'C');
}

int main() {
    cout << "Data Structures & Algorithms - educational demo\n";
    cout << "Read the header next to each example to see the implementation.\n";

    runSortingTour();
    runSearchingTour();
    runRecursionTour();

    cout << "\nDone. Explore src/ for more structures and algorithms.\n";
    return 0;
}
