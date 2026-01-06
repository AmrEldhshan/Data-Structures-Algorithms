/*
Heap Class (Max Heap)
---------------------
Dynamic array based Max Heap implementation.

Features:
1. Insert elements while maintaining heap property
2. Extract maximum and minimum elements
3. Heap sort in ascending order
4. Utility functions: print, getSize, isEmpty

Heap Property:
- For Max Heap: parent >= children
- Root always contains the maximum element

Time Complexity:
- insert: O(log n)
- extractMax: O(log n)
- extractMin: O(n) (linear scan)
- heapSort: O(n log n)
- getSize/isEmpty/print: O(n)

Space Complexity:
- O(n) for dynamic array storage
*/

#ifndef HEAP_H
#define HEAP_H

#include <iostream>

class Heap {
private:
    int* heapArray;   // Dynamic array to store heap elements
    int size;         // Current number of elements in the heap
    int capacity;     // Current capacity of the dynamic array

    // Helper functions for index calculation
    int parent(int i) const { return (i - 1) / 2; }
    int left(int i) const { return 2 * i + 1; }
    int right(int i) const { return 2 * i + 2; }

    /*
    Resizes the heap array when capacity is exceeded.
    Doubling strategy used for amortized O(1) insertion.
    */
    void resize(int newCapacity) {
        int* newHeap = new int[newCapacity];
        for (int i = 0; i < size; i++)
            newHeap[i] = heapArray[i];
        delete[] heapArray;
        heapArray = newHeap;
        capacity = newCapacity;
    }

    /*
    Moves the element at index i down the heap to maintain max-heap property.
    Called after extracting max or replacing root.
    */
    void heapifyDown(int i) {
        int largest = i;
        int l = left(i);
        int r = right(i);

        if (l < size && heapArray[l] > heapArray[largest])
            largest = l;
        if (r < size && heapArray[r] > heapArray[largest])
            largest = r;

        if (largest != i) {
            int temp = heapArray[i];
            heapArray[i] = heapArray[largest];
            heapArray[largest] = temp;
            heapifyDown(largest);
        }
    }

    /*
    Moves the element at index i up the heap to maintain max-heap property.
    Called after inserting a new element.
    */
    void heapifyUp(int i) {
        while (i > 0 && heapArray[parent(i)] < heapArray[i]) {
            int temp = heapArray[i];
            heapArray[i] = heapArray[parent(i)];
            heapArray[parent(i)] = temp;
            i = parent(i);
        }
    }

public:
    /*
    Constructor
    Initializes an empty heap with given capacity (default 10)
    */
    Heap(int cap = 10) : size(0), capacity(cap) {
        heapArray = new int[capacity];
    }

    // Destructor: release dynamic memory
    ~Heap() { delete[] heapArray; }

    /*
    Inserts a new element into the heap.
    Maintains max-heap property using heapifyUp.
    Time Complexity: O(log n)
    */
    void insert(int value) {
        if (size == capacity)
            resize(capacity * 2);
        heapArray[size] = value;
        heapifyUp(size);
        size++;
    }

    /*
    Extracts and returns the maximum element (root of the heap).
    Maintains heap property using heapifyDown.
    Time Complexity: O(log n)
    */
    int extractMax() {
        if (size == 0) return -1; // Heap empty
        int maxVal = heapArray[0];
        heapArray[0] = heapArray[size - 1];
        size--;
        heapifyDown(0);
        return maxVal;
    }

    /*
    Extracts and returns the minimum element in the heap.
    Performs linear scan to find minimum, then heapifyDown.
    Time Complexity: O(n)
    */
    int extractMin() {
        if (size == 0) return -1; // Heap empty
        int minIndex = 0;
        for (int i = 1; i < size; i++)
            if (heapArray[i] < heapArray[minIndex])
                minIndex = i;
        int minVal = heapArray[minIndex];
        heapArray[minIndex] = heapArray[size - 1];
        size--;
        heapifyDown(minIndex);
        return minVal;
    }

    /*
    Heap Sort in-place.
    Extracts max repeatedly to sort array in ascending order.
    Heap property restored at the end.
    Time Complexity: O(n log n)
    */
    void heapSort() {
        int originalSize = size;
        for (int i = size - 1; i > 0; i--) {
            int temp = heapArray[0];
            heapArray[0] = heapArray[i];
            heapArray[i] = temp;
            size--;
            heapifyDown(0);
        }
        size = originalSize;
    }

    /*
    Prints heap elements in array order.
    Time Complexity: O(n)
    */
    void print() const {
        for (int i = 0; i < size; i++)
            std::cout << heapArray[i] << " ";
        std::cout << std::endl;
    }

    // Returns number of elements in heap
    int getSize() const { return size; }

    // Returns true if heap is empty
    bool isEmpty() const { return size == 0; }
};

#endif
