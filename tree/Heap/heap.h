#ifndef HEAP_H
#define HEAP_H

#include <iostream>
using namespace std;

template <class T>
class MaxHeap {
private:
    T* heap;
    int capacity;
    int size;

    int parent(int i)     { return i / 2; }
    int leftChild(int i)  { return 2 * i; }
    int rightChild(int i) { return 2 * i + 1; }

    void resize() {
        capacity = (capacity == 0) ? 2 : capacity * 2;
        T* newHeap = new T[capacity];
        for (int i = 1; i <= size; i++) {
            newHeap[i] = heap[i];
        }
        delete[] heap;
        heap = newHeap;
    }

    void maxHeapify(int i, int heapSize) {
		// log(n) or o(h)
        int l = leftChild(i);
        int r = rightChild(i);
        int largest = i;

        if (l <= heapSize && heap[l] > heap[largest])
            largest = l;
        if (r <= heapSize && heap[r] > heap[largest])
            largest = r;

        if (largest != i) {
            swap(heap[i], heap[largest]);
            maxHeapify(largest, heapSize);
        }
    }

    void buildMaxHeap() {
		// O(n*log(n)) -> This is not an asymptotically tight upper bound
		// O(n)
        for (int i = size / 2; i >= 1; i--) {
            maxHeapify(i, size);
        }
    }

public:
    MaxHeap() : capacity(2), size(0) {
        heap = new T[capacity];
    }

    MaxHeap(int capacity) : capacity(capacity + 1), size(0) {
        heap = new T[capacity + 1]; // +1 for 1-based indexing
    }

    MaxHeap(T* array, int n) : capacity(n * 2 + 1), size(n) {
        heap = new T[capacity];
        for (int i = 1; i <= n; i++) {
            heap[i] = array[i - 1];
        }
        buildMaxHeap();
    }

    ~MaxHeap() {
        delete[] heap;
    }

    void heapSort() {
		// O(n * logn)
        buildMaxHeap(); // o(n)
        for (int i = size; i > 1; i--) {
            swap(heap[1], heap[i]);
            maxHeapify(1, i - 1); // o(logn)
        }
    }

    void print() const {
        for (int i = 1; i <= size; i++) {
            cout << heap[i] << " ";
        }
        cout << endl;
    }

    void insert(T value) {
        if (size + 1 >= capacity) resize();
        heap[++size] = value;
        int i = size;
        while (i > 1 && heap[parent(i)] < heap[i]) {
            swap(heap[i], heap[parent(i)]);
            i = parent(i);
        }
    }

    T extractMax() {
        if (size == 0) throw runtime_error("Heap is empty");
        T maxVal = heap[1];
        heap[1] = heap[size--];
        maxHeapify(1, size);
        return maxVal;
    }
};

#endif // HEAP_H
