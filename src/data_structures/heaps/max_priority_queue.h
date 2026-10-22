/*
Max-Priority Queue Implementation (Dynamic Array-Based Heap)
------------------------------------------------------------
Data Structure:
    Binary Max-Heap implemented using a dynamically allocated array.

Goal:
    Efficiently manage a collection of elements where extraction of the
    maximum element is required in logarithmic time.

Operations and Complexities:
    buildMaxHeap()   : O(n)
    insert(key)      : O(log n)
    extractMax()     : O(log n)
    increaseKey(i,k) : O(log n)
    decreaseKey(i,k) : O(log n)
    maximum()        : O(1)
    remove(key)      : O(log n)
    heapSort()       : O(n log n)
    print()          : O(n)
    clear()          : O(1)

Space Complexity:
    O(n)
        - n: number of elements in the heap.
        - Backed by a dynamically allocated array that resizes as needed.

Design Notes:
    - Uses 0-based indexing for heap relationships:
          parent(i) = (i - 1) / 2
          left(i)   = 2 * i + 1
          right(i)  = 2 * i + 2
    - Automatically doubles capacity when full.
    - No STL or external libraries are used — implemented entirely
      with raw dynamic arrays.
    - Designed for clarity, safety, and educational demonstration
      of heap-based priority queues.

References:
    - Based on principles from *Introduction to Algorithms (CLRS)*,
      Chapter 6: Heapsort and Priority Queues.
*/

#ifndef MAX_PRIORITY_QUEUE_H
#define MAX_PRIORITY_QUEUE_H

#include <iostream>
#include <stdexcept>

template <typename T>
class MaxPriorityQueue {
private:
    T* heap;
    int capacity;
    int size;

    // ---------------- Helper Functions ----------------
    inline int parent(int i) const { return (i - 1) / 2; }
    inline int left(int i) const { return 2 * i + 1; }
    inline int right(int i) const { return 2 * i + 2; }

    void resize(int new_capacity) {
        if (new_capacity < size) new_capacity = size;
        if (new_capacity < 1) new_capacity = 1;

        T* newHeap = new T[new_capacity];
        for (int i = 0; i < size; ++i)
            newHeap[i] = heap[i];

        delete[] heap;
        heap = newHeap;
        capacity = new_capacity;
    }

    void maxHeapify(int i, int current_size) {
        int l = left(i);
        int r = right(i);
        int largest = i;

        if (l < current_size && heap[l] > heap[largest])
            largest = l;
        if (r < current_size && heap[r] > heap[largest])
            largest = r;

        if (largest != i) {
            T temp = heap[i];
            heap[i] = heap[largest];
            heap[largest] = temp;
            maxHeapify(largest, current_size);
        }
    }

    void buildMaxHeap() {
        for (int i = (size / 2) - 1; i >= 0; --i)
            maxHeapify(i, size);
    }

public:
    // ---------------- Constructors & Destructor ----------------
    MaxPriorityQueue() : capacity(1), size(0) {
        heap = new T[capacity];
    }

    MaxPriorityQueue(const T* array, int n) : capacity(n), size(n) {
        if (n < 0) throw std::invalid_argument("Invalid size.");
        heap = new T[capacity];
        for (int i = 0; i < n; ++i)
            heap[i] = array[i];
        buildMaxHeap();
    }

    MaxPriorityQueue(const MaxPriorityQueue& other)
        : capacity(other.capacity), size(other.size) {
        heap = new T[capacity];
        for (int i = 0; i < size; ++i)
            heap[i] = other.heap[i];
    }

    MaxPriorityQueue& operator=(const MaxPriorityQueue& other) {
        if (this != &other) {
            delete[] heap;
            capacity = other.capacity;
            size = other.size;
            heap = new T[capacity];
            for (int i = 0; i < size; ++i)
                heap[i] = other.heap[i];
        }
        return *this;
    }

    ~MaxPriorityQueue() {
        delete[] heap;
    }

    // ---------------- Core Heap Operations ----------------
    void insert(T key) {
        if (size >= capacity)
            resize(capacity * 2);

        int i = size;
        heap[i] = key;
        size++;

        // Fix the heap upwards
        while (i > 0 && heap[parent(i)] < heap[i]) {
            T temp = heap[i];
            heap[i] = heap[parent(i)];
            heap[parent(i)] = temp;
            i = parent(i);
        }
    }

    T extractMax() {
        if (size == 0)
            throw std::out_of_range("Heap is empty.");

        T maxVal = heap[0];
        heap[0] = heap[size - 1];
        size--;

        maxHeapify(0, size);
        return maxVal;
    }

    T maximum() const {
        if (size == 0)
            throw std::out_of_range("Heap is empty.");
        return heap[0];
    }

    void increaseKey(int i, T newKey) {
        if (i < 0 || i >= size)
            throw std::out_of_range("Invalid index.");
        if (newKey < heap[i])
            throw std::invalid_argument("New key is smaller than current key.");

        heap[i] = newKey;
        while (i > 0 && heap[parent(i)] < heap[i]) {
            T temp = heap[i];
            heap[i] = heap[parent(i)];
            heap[parent(i)] = temp;
            i = parent(i);
        }
    }

    void decreaseKey(int i, T newKey) {
        if (i < 0 || i >= size)
            throw std::out_of_range("Invalid index.");
        if (newKey > heap[i])
            throw std::invalid_argument("New key is larger than current key.");

        heap[i] = newKey;
        maxHeapify(i, size);
    }

    void remove(T key) {
        if (size == 0)
            throw std::out_of_range("Heap is empty.");

        int index = -1;
        for (int i = 0; i < size; ++i) {
            if (heap[i] == key) {
                index = i;
                break;
            }
        }

        if (index == -1)
            throw std::invalid_argument("Key not found.");

        heap[index] = heap[size - 1];
        size--;

        // Fix heap property
        if (index > 0 && heap[index] > heap[parent(index)]) {
            while (index > 0 && heap[index] > heap[parent(index)]) {
                T temp = heap[index];
                heap[index] = heap[parent(index)];
                heap[parent(index)] = temp;
                index = parent(index);
            }
        } else {
            maxHeapify(index, size);
        }
    }

    // ---------------- Utility Functions ----------------
    void clear() { size = 0; }

    void shrinkToFit() {
        if (capacity > size)
            resize(size);
    }

    bool isEmpty() const { return size == 0; }

    int getSize() const { return size; }

    void print() const {
        for (int i = 0; i < size; ++i)
            std::cout << heap[i] << " ";
        std::cout << std::endl;
    }

    void heapSort() {
        buildMaxHeap();
        int original_size = size;
        for (int i = size - 1; i > 0; --i) {
            T temp = heap[0];
            heap[0] = heap[i];
            heap[i] = temp;
            maxHeapify(0, i);
        }
        size = original_size;
    }
};

#endif // MAX_PRIORITY_QUEUE_H
