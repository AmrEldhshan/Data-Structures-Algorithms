/*
============================================================
 Tests for the header-only sorting / searching algorithms
============================================================

These tests are deliberately simple: they build small arrays,
run each implementation, and check the expected result. They
are a quick way to check that an algorithm still behaves after
you change it.

The checks use a small `require` function instead of `assert`
so they also run in Release builds (where `assert` is removed).
*/

#include "algorithms/bit_manipulation/bit_manipulation.h"
#include "algorithms/number_theory/number_theory.h"
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
#include "algorithms/sorting/randomized_select.h"
#include "algorithms/sorting/selection_sort.h"
#include "algorithms/sorting/shell_sort.h"

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

namespace {

int failures = 0;

void require(bool condition, const string& message) {
    if (!condition) {
        cerr << "FAILED: " << message << '\n';
        ++failures;
    }
}

vector<int> makeInput() {
    return {42, 7, 19, 3, 88, 15, 42, 1, 23, 5};
}

void requireSorted(const string& name, const vector<int>& values) {
    require(is_sorted(values.begin(), values.end()),
            name + " produced an unsorted array");
}

template <typename Sort>
void checkSort(const string& name, Sort sortFunction) {
    vector<int> values = makeInput();
    sortFunction(values.data(), static_cast<int>(values.size()));
    requireSorted(name, values);
}

} // namespace

int main() {
    // --- Quadratic sorting algorithms -------------------------------------
    checkSort("bubbleSort", bubbleSort<int>);
    checkSort("selectionSort", selectionSort<int>);
    checkSort("insertionSort", insertionSort<int>);

    // --- Sub-quadratic sorting algorithms --------------------------------
    checkSort("shellSort", ShellSort);
    checkSort("heapSort", heapSort<int>);

    {
        vector<int> values = makeInput();
        mergeSort(values.data(), 0, static_cast<int>(values.size()) - 1);
        requireSorted("mergeSort", values);
    }
    {
        vector<int> values = makeInput();
        quickSort(values.data(), 0, static_cast<int>(values.size()) - 1);
        requireSorted("quickSort", values);
    }

    // --- Linear-time sorting algorithms ----------------------------------
    // These implementations expect non-negative, small values.
    {
        vector<int> values = {42, 7, 19, 3, 88, 15, 1, 23, 5};
        countSort(values.data(), static_cast<int>(values.size()));
        requireSorted("countSort", values);
    }
    {
        vector<int> values = {42, 7, 19, 3, 88, 15, 1, 23, 5};
        radixSort(values.data(), static_cast<int>(values.size()));
        requireSorted("radixSort", values);
    }
    {
        vector<int> values = {42, 7, 19, 3, 88, 15, 1, 23, 5};
        bucketSort(values.data(), static_cast<int>(values.size()));
        requireSorted("bucketSort", values);
    }

    // --- Order statistic -------------------------------------------------
    {
        vector<int> values = makeInput();
        const int thirdSmallest =
            randomizedSelect(values, 0, static_cast<int>(values.size()) - 1, 3);
        require(thirdSmallest == 5, "randomizedSelect should return 5 as the 3rd smallest");
    }

    // --- Searching -------------------------------------------------------
    {
        int values[] = {1, 3, 5, 7, 9, 11, 13};
        const int size = static_cast<int>(sizeof(values) / sizeof(values[0]));
        require(binarySearchIterative(values, size, 9) == 4,
                "binarySearchIterative should find index 4");
        require(binarySearchRecursive(values, 0, size - 1, 9) == 4,
                "binarySearchRecursive should find index 4");
        require(sequentialSearchIterative(values, size, 9) == 4,
                "sequentialSearchIterative should find index 4");
        require(sequentialSearchRecursive(values, size, 9) == 4,
                "sequentialSearchRecursive should find index 4");
        require(binarySearchIterative(values, size, 100) == -1,
                "binarySearchIterative should return -1 for a missing value");
    }

    // --- Number theory ---------------------------------------------------
    require(number_theory::gcd(30, 18) == 6, "gcd(30, 18) should be 6");
    require(number_theory::lcm(30, 18) == 90, "lcm(30, 18) should be 90");
    require(number_theory::modPow(3, 200, 1'000'000'007) == 136318165,
            "modPow(3, 200) mismatch");
    require(number_theory::modInverse(3, 1'000'000'007) == 333333336,
            "modInverse(3) mismatch");
    require(number_theory::totient(36) == 12, "totient(36) should be 12");
    require(number_theory::factorize(36).size() == 2,
            "36 should have two distinct prime factors");
    require(number_theory::binomialMod(10, 3, 1'000'000'007) == 120,
            "C(10, 3) should be 120");
    require(number_theory::catalan(10) == 16796, "Catalan(10) should be 16796");

    // --- Bit manipulation ------------------------------------------------
    require(bits::countSetBits(0b10110100ULL) == 4,
            "countSetBits(0b10110100) should be 4");
    require(bits::isPowerOfTwo(1024), "1024 should be a power of two");
    require(!bits::isPowerOfTwo(0), "0 is not a power of two");
    require(bits::lowestSetBitIndex(0b10110100ULL) == 2,
            "lowest set bit of 0b10110100 should be index 2");
    require(bits::bitLength(0b10110100ULL) == 8,
            "bitLength(0b10110100) should be 8");
    require(bits::setBit(0, 3) == 8, "setBit(0, 3) should be 8");
    require(bits::clearBit(0b1111, 2) == 0b1011, "clearBit(0b1111, 2) failed");
    require(bits::toggleBit(0b1010, 0) == 0b1011, "toggleBit(0b1010, 0) failed");

    // --- Recursion -------------------------------------------------------
    require(Factorial(0) == 1, "0! should be 1");
    require(Factorial(5) == 120, "5! should be 120");

    if (failures == 0) {
        cout << "All algorithm tests passed.\n";
        return 0;
    }

    cerr << failures << " test(s) failed.\n";
    return 1;
}
