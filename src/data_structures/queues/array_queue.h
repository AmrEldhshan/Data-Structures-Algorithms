#ifndef ARRAY_BASED_QUEUE_H
#define ARRAY_BASED_QUEUE_H

#include <iostream>
using namespace std;

template <typename T>
class ArrayQueue {
private:
    T* arr;
    int capacity;
    int frontIndex;
    int rearIndex;
    int currentSize;

    void resize() {
        int newCapacity = capacity * 2;
        T* newArr = new T[newCapacity];

        for (int i = 0; i < currentSize; i++) {
            newArr[i] = arr[(frontIndex + i) % capacity];
        }

        delete[] arr;
        arr = newArr;
        frontIndex = 0;
        rearIndex = currentSize;
        capacity = newCapacity;
    }

public:
    ArrayQueue(int initCapacity = 10) {
        capacity = initCapacity;
        arr = new T[capacity];
        frontIndex = 0;
        rearIndex = 0;
        currentSize = 0;
    }

    ~ArrayQueue() {
        delete[] arr;
    }

    // clear(): empties the queue
    void clear() {
        frontIndex = 0;
        rearIndex = 0;
        currentSize = 0;
    }

    // isEmpty(): returns true if the queue is empty
    bool isEmpty() const {
        return currentSize == 0;
    }

    // isFull(): returns true if the queue is full
    bool isFull() const {
        return currentSize == capacity;
    }

    // enqueue(item): puts item at the end of the queue
    void enqueue(const T& item) {
        if (isFull()) {
            resize();
        }
        arr[rearIndex] = item;
        rearIndex = (rearIndex + 1) % capacity;
        currentSize++;
    }

    // dequeue(): removes and returns item at the front of the queue
    T dequeue() {
        if (isEmpty()) {
            throw runtime_error("Queue underflow: cannot dequeue from an empty queue.");
        }
        T value = arr[frontIndex];
        frontIndex = (frontIndex + 1) % capacity;
        currentSize--;
        return value;
    }

    // first(): returns the first item without removing it
    T first() const {
        if (isEmpty()) {
            throw runtime_error("Queue is empty: cannot access front.");
        }
        return arr[frontIndex];
    }

    // back(): returns the last item without removing it
    T back() const {
        if (isEmpty()) {
            throw runtime_error("Queue is empty: cannot access back.");
        }
        int lastIndex = (rearIndex - 1 + capacity) % capacity;
        return arr[lastIndex];
    }

    // getSize(): returns the current number of elements
    int getSize() const {
        return currentSize;
    }

    // display(): prints all elements for debugging
    void display() const {
        cout << "Queue: ";
        for (int i = 0; i < currentSize; i++) {
            cout << "[ " << arr[(frontIndex + i) % capacity] << " ] ";
        }
        cout << endl;
    }
};

#endif // ARRAY_BASED_QUEUE_H
