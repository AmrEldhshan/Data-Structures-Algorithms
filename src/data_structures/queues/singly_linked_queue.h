#ifndef SLL_QUEUE_H
#define SLL_QUEUE_H

#include <iostream>
using namespace std;

template <typename T>
class SLLQueue {
private:
    struct Node {
        T data;
        Node* next;
        Node(const T& val) : data(val), next(nullptr) {}
    };

    Node* frontNode;
    Node* rearNode;
    int size;

public:
    SLLQueue() : frontNode(nullptr), rearNode(nullptr), size(0) {}

    ~SLLQueue() {
        clear();
    }

    void enqueue(const T& value) {
        Node* newNode = new Node(value);
        if (isEmpty()) {
            frontNode = rearNode = newNode;
        } else {
            rearNode->next = newNode;
            rearNode = newNode;
        }
        size++;
    }

    T dequeue() {
        if (isEmpty()) {
            throw runtime_error("Queue underflow: dequeue from empty queue.");
        }
        Node* temp = frontNode;
        T val = temp->data;
        frontNode = frontNode->next;
        if (!frontNode) {
            rearNode = nullptr; // queue is now empty
        }
        delete temp;
        size--;
        return val;
    }

    T front() const {
        if (isEmpty()) {
            throw runtime_error("Queue is empty: cannot access front.");
        }
        return frontNode->data;
    }

    bool isEmpty() const {
        return frontNode == nullptr;
    }

    int getSize() const {
        return size;
    }

    void clear() {
        while (!isEmpty()) {
            dequeue();
        }
    }

    void display() const {
        Node* current = frontNode;
        while (current) {
            cout << current->data << " <- ";
            current = current->next;
        }
        cout << "NULL\n";
    }
};

#endif // SLL_QUEUE_H
