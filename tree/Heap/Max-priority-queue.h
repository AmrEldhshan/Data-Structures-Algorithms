#ifndef MAX_PRIORITY_QUEUE_H
#define MAX_PRIORITY_QUEUE_H

#include <iostream> // For cout, endl
#include <stdexcept> // For out_of_range, invalid_argument
#include <algorithm> // For std::swap
#include <cmath>     // For std::max

template <class T>
class MaxPriorityQueue {
private:
    T* heap;
    int capacity;
    int size; // Number of elements currently in the heap

    // Helper functions (0-based indexing)
    int parent(int i) {
        if (i == 0) return -1; // Root has no parent
        return (i - 1) / 2;
    }
    int left(int i) { return 2 * i + 1; }
    int right(int i) { return 2 * i + 2; }

    void resize(int new_capacity) {
        if (new_capacity < size) {
            new_capacity = size; 
        }
        if (new_capacity == 0) new_capacity = 1; 

        T* newHeap = new T[new_capacity];
        for (int i = 0; i < size; i++) { 
            newHeap[i] = heap[i];
        }
        delete[] heap; 
        heap = newHeap; 
        capacity = new_capacity; 
    }

    // maxHeapify now takes 'current_heap_size' to define its operational boundary.
    void maxHeapify(int i, int current_heap_size) {
        int l = left(i);
        int r = right(i);
        int largest = i; 

        // Check left child, ensuring it's within current_heap_size bounds.
        if (l < current_heap_size && heap[l] > heap[largest])
            largest = l;
        // Check right child, ensuring it's within current_heap_size bounds.
        if (r < current_heap_size && heap[r] > heap[largest])
            largest = r;
        
        if (largest != i) {
            std::swap(heap[i], heap[largest]);
            // Pass current_heap_size down in the recursive call.
            maxHeapify(largest, current_heap_size); 
        }
    }

public:
    // Constructors
    MaxPriorityQueue() : capacity(1), size(0) { 
        heap = new T[capacity];
    }

    MaxPriorityQueue(T* array, int n) : size(n) { 
        capacity = std::max(1, n); 
        heap = new T[capacity];
        for (int i = 0; i < n; i++) {
            heap[i] = array[i];
        }
        buildMaxHeap(); // Calls internal buildMaxHeap which uses 'size'
    }

    ~MaxPriorityQueue() {
        delete[] heap;
    }

	void buildMaxHeap() {
		for (int i = (size / 2) - 1; i >= 0; i--) {
			maxHeapify(i, size);
		}
	}

	// Sorts the elements in the heap array in ascending order (in-place).
	void heapSort() {
    	buildMaxHeap(); // First, ensure the array forms a max-heap.
    	int original_size = size; // Store original size to restore it later.

    	// Iterate from the last element down to the second element (index 1).
    	for (int i = size - 1; i > 0; i--) {
    		std::swap(heap[0], heap[i]); // Move the current max element (root) to the end of the unsorted part.
    		// When calling maxHeapify, pass 'i' as the current effective heap size.
    		// This 'i' represents the boundary of the unsorted part.
    		maxHeapify(0, i); // maxHeapify operates on elements from 0 to i-1.
    	}
    	size = original_size; // Restore the original size of the heap after sorting.
    }

	T extractMax() {
		// extract max running time = O(log(n))
		if (size == 0) {
			throw std::out_of_range("MaxPriorityQueue is empty");
		}

		T result = heap[0];
		size--;
		heap[0] = heap[size]; // we do not make size - 1 as we already minus one from the size above line

    	// Call maxHeapify with the updated 'size' of the heap.
		maxHeapify(0, size);
		return result;

	}

	T maximum() {
    	if (size <= 0) {
    		throw std::out_of_range("Heap is empty: No maximum element.");
    	}
    	return heap[0];
    }

	void increaseKey(int i, T key) {
		//	running time = O(log(n))
		if (key < heap[i]) {
            throw std::invalid_argument("New key is smaller than current key.");
		}
		if (i < 0 || i >= size) {
			throw std::out_of_range("Index out of bounds for increaseKey.");
		}
		heap[i] = key;
		while (i > 0 && heap[parent(i)] < heap[i]) {
			std::swap(heap[i], heap[parent(i)]);
			i = parent(i);
		}
	}


	void decreaseKey(int i, T key) {
		if (key < heap[i]) {
			throw std::invalid_argument("New key is smaller than current key.");
		}
		if (i < 0 || i >= size) {
			throw std::invalid_argument("Index out of bounds for decreaseKey.");
		}
		heap[i] = key;
		while (i > 0 && heap[parent(i)] > heap[i]) {
			std::swap(heap[i], heap[parent(i)]);
			i = parent(i);
		}
	}

	T minimum() {
		if (size == 0) {
			throw std::out_of_range("Heap is empty.");
		}
		return heap[size - 1];

	}
	void insert(T key) {
    	// log(n)
		if (size >= capacity) {
			resize(capacity * 2);
		}
		heap[size] = key;
		int i = size;
		size++;
    	while (i > 0 && heap[parent(i)] < heap[i]) {
    		std::swap(heap[i], heap[parent(i)]);
    		i = parent(i);
    	}
	}

	void remove(T key) {
	    if (size < 1) {
		    throw std::invalid_argument("Heap is empty.");
	    }

    	int index = -1;
    	for (int i = 0; i < size; i++) {
    		if (heap[i] == key) {
    			index = i;
    			break;
    		}
    	}

    	if (index == -1) {
    		throw std::invalid_argument("Key not found in heap.");
    	}

    	// Move the last element to the position of the element to remove
    	size--;
    	heap[index] = heap[size];

    	// If we didn't remove the last element, we need to potentially heapify
    	if (index < size) {
    		// Check if we need to move it up or down
    		if (index > 0 && heap[index] > heap[parent(index)]) {
    			// Move up
    			while (index > 0 && heap[index] > heap[parent(index)]) {
    				std::swap(heap[index], heap[parent(index)]);
    				index = parent(index);
    			}
    		} else {
    			// Move down
    			maxHeapify(index, size);
    		}
    	}

    }
	// Utility functions
	int getSize() const { return size; }
	bool isEmpty() const { return size == 0; }

	void print() const {
    	for (int i = 0; i < size; i++) {
    		std::cout << heap[i] << " ";
    	}
    	std::cout << std::endl;
    }
};

#endif // MAX_PRIORITY_QUEUE_H