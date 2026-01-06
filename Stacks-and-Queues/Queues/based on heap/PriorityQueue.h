/*
PriorityQueue Class
------------------
Implements a priority queue using the Heap class (composition).

Features:
- insert(value)             : Add element with priority
- extractHighestPriority()   : Remove element with highest priority (max)
- isEmpty()                 : Check if queue is empty
- print()                   : Display elements

Time Complexity:
- insert: O(log n)
- extractHighestPriority: O(log n)
- isEmpty/print: O(n)
*/

#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H

#include "Heap.h"

class PriorityQueue {
private:
    Heap heap; // Heap object as a member

public:
    /*
    Constructor
    Initializes an empty priority queue with given initial capacity
    */
    PriorityQueue(int cap = 10) : heap(cap) {}

    /*
    Inserts a value into the priority queue.
    Calls heap's insert function.
    Time Complexity: O(log n)
    */
    void insert(int value) {
        heap.insert(value);
    }

    /*
    Extracts the element with highest priority (max element).
    Calls heap's extractMax function.
    Time Complexity: O(log n)
    */
    int extractHighestPriority() {
        return heap.extractMax();
    }

    /*
    Returns true if the priority queue is empty
    Time Complexity: O(1)
    */
    bool isEmpty() const {
        return heap.isEmpty();
    }

    /*
    Prints the priority queue elements in heap array order
    Time Complexity: O(n)
    */
    void print() const {
        heap.print();
    }
};

#endif
