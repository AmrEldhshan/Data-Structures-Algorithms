#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include <iostream>
#include <stdexcept>
using namespace std;

template <typename T>
class PriorityQueue {
private:
    struct Node {
        T data;
        int priority;
        Node* next;
        Node(const T& value, int prio) : data(value), priority(prio), next(nullptr) {}
    };

    Node* head;
    int size;

public:
    PriorityQueue() : head(nullptr), size(0) {}

    ~PriorityQueue() {
        clear();
    }

    void clear() {
        while (!isEmpty()) {
            dequeue();
        }
    }

    bool isEmpty() const {
        return head == nullptr;
    }

    int getSize() const {
        return size;
    }

    // Insert keeping the queue sorted by priority (lowest first),
    // but if same priority, insert after all existing with same priority (FIFO)
    void enqueue(const T& item, int priority) {
        Node* newNode = new Node(item, priority);

        if (isEmpty() || priority < head->priority) {
            // New node has higher priority than head, insert at front
            newNode->next = head;
            head = newNode;
        } else {
            Node* current = head;
            // Move until finding node with priority greater than new node's,
            // or reach end or find node with priority > new node's priority
            while (current->next && current->next->priority <= priority) {
                // This ensures stable insertion for same priority (insertion at the end of same priority)
                current = current->next;
            }
            newNode->next = current->next;
            current->next = newNode;
        }
        size++;
    }

    // Remove and return the highest priority element (lowest priority value)
    T dequeue() {
        if (isEmpty()) {
            throw runtime_error("Priority Queue underflow: cannot dequeue from empty queue.");
        }
        Node* temp = head;
        T retVal = temp->data;
        head = head->next;
        delete temp;
        size--;
        return retVal;
    }

    // Return highest priority element without removing
    T front() const {
        if (isEmpty()) {
            throw runtime_error("Priority Queue is empty: cannot get front.");
        }
        return head->data;
    }

    // Display the queue for debugging
    void display() const {
        Node* current = head;
        cout << "Priority Queue (item:priority): ";
        while (current) {
            cout << "(" << current->data << ":" << current->priority << ") ";
            current = current->next;
        }
        cout << endl;
    }
};

#endif // PRIORITY_QUEUE_H
