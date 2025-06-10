#ifndef CIRCULAR_ARRAY_BASED_QUEUE_H
#define CIRCULAR_ARRAY_BASED_QUEUE_H

#include <iostream>
#include <stdexcept>
using namespace std;

template <typename T>
class CircularQueue {
private:
    T* data;          // Pointer to dynamically allocated array holding the queue elements
    int capacity;     // Maximum number of elements queue can hold
    int frontIndex;   // Index of the front element in the queue
    int rearIndex;    // Index of the last (rear) element in the queue
    int size;         // Current number of elements in the queue

public:
    // Constructor initializes the queue with given capacity (default 100)
    // Allocates array and sets frontIndex and rearIndex appropriately
    CircularQueue(int cap = 100) : capacity(cap), frontIndex(0), rearIndex(-1), size(0) {
        data = new T[capacity];  // allocate the array dynamically
    }

    // Destructor to clean up the allocated memory
    ~CircularQueue() {
        delete[] data;
    }

    // clear(): empties the queue by resetting indices and size
    void clear() {
        frontIndex = 0;
        rearIndex = -1;
        size = 0;
    }

    // isEmpty(): returns true if queue has no elements
    bool isEmpty() const {
        return size == 0;
    }

    // isFull(): returns true if queue is at full capacity
    bool isFull() const {
        return size == capacity;
    }

    // enqueue(item): adds an item to the rear of the queue
    void enqueue(const T& item) {
        if (isFull()) {
            throw runtime_error("Queue overflow: cannot enqueue to full queue.");
        }
        // Move rearIndex forward circularly (wrap around if needed)
        rearIndex = (rearIndex + 1) % capacity;
        data[rearIndex] = item;  // Insert the new element
        size++;                  // Increment size after successful insert
    }

    // dequeue(): removes and returns the front item of the queue
    T dequeue() {
        if (isEmpty()) {
            throw runtime_error("Queue underflow: cannot dequeue from empty queue.");
        }
        T frontItem = data[frontIndex]; // Store the item to return
        frontIndex = (frontIndex + 1) % capacity; // Move frontIndex forward circularly
        size--;  // Decrement size after removing an element
        return frontItem;
    }

    // first(): returns the front item without removing it
    T first() const {
        if (isEmpty()) {
            throw runtime_error("Queue is empty: cannot access first.");
        }
        return data[frontIndex];
    }

    // getSize(): returns the current number of elements in the queue
    int getSize() const {
        return size;
    }

    // display(): prints all queue elements from front to rear in order
    void display() const {
        if (isEmpty()) {
            cout << "Queue is empty.\n";
            return;
        }
        cout << "Queue elements: ";
        // Loop through size elements, starting at frontIndex and wrapping around
        for (int i = 0; i < size; i++) {
            cout << data[(frontIndex + i) % capacity] << " ";
        }
        cout << endl;
    }
};

#endif // CIRCULAR_ARRAY_BASED_QUEUE_H
