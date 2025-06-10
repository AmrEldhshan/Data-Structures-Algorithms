#ifndef HEAP_H
#define HEAP_H
// zero based index
#include <iostream>
using namespace std;
template <class T>
class MaxHeap {
private:
	T* heap;
	int capacity;
	int size;

	T parent(int i){return (i)/2;}
	T leftChild(int i){return (2*i);}
	T rightChild(int i){return (2*i+1);}

	void resize() {
		capacity = (capacity == 0) ? 1 : capacity * 2;
		T* newHeap = new T[capacity];
		for (int i = 0; i < size; i++) {
			newHeap[i] = heap[i];
		}
		delete[] heap;
		heap = newHeap;
	}

public:
	MaxHeap(): capacity(0), size(0), heap(nullptr) {}

	MaxHeap(int capacity): capacity(capacity), size(0) {
		heap = new T[capacity];
	}

	MaxHeap(T* array, int n) : capacity(n * 2), size(n) {
		heap = new T[capacity];
		for (int i = 0; i < n; i++) {
			heap[i] = array[i];
		}
		buildMaxHeap();
	}

	// Destructor
	~MaxHeap() {
		delete[] heap;
	}


	void maxHeapify(int i, int heapSize) {
		// time complexisty is O(h) or O(log(n))
		int l = leftChild(i);
		int r = rightChild(i);
		int largest = i;

		if(l < heapSize && heap[l] > heap[i]) {
			largest = l;
		}
		if(r < heapSize && heap[r] > heap[i]) {
			largest = r;
		}
		if(largest != i) { // this is the base case that stop the recursive
			// if the largest element index is on the top then do not make and more recursive
			swap(heap[i], heap[largest]);
			maxHeapify(largest, heapSize);
		}
	}


	void buildMaxHeap() {
		// running time is O(n)

		for (int i = (size / 2); i > 0; i--) {
			maxHeapify(i, size);
		}
	}


	void heapSort(){
		buildMaxHeap();
		// running time = O(n*log(n)) -> O(n) form buiding * log(n) from the heapify
		for (int i = size - 1; i > 0; i--) {
			swap(heap[0], heap[i]);
			maxHeapify(0, i);

		}
	}




	void print() const{
		for (int i = 1; i <= size; i++) {
			std::cout << heap[i] << " ";
		}
		cout << endl;
	}

};


#endif // HEAP_H
