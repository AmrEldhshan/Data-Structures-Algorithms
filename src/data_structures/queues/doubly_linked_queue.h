#ifndef DLL_QUEUE_H
#define DLL_QUEUE_H

#include <iostream>
using namespace std;

template <typename T>
class DLLQueue {
private:
    struct Node {
        T data;
        Node* prev;
        Node* next;
        Node(const T& val) : data(val), prev(nullptr), next(nullptr) {}
    };

    Node* frontNode;
    Node* rearNode;
    int size;

public:
    DLLQueue() : frontNode(nullptr), rearNode(nullptr), size(0) {}

    ~DLLQueue() {
        clear();
    }

    void enqueue(const T& value) {
        Node* newNode = new Node(value);
        if (isEmpty()) {
            frontNode = rearNode = newNode;
        } else {
            rearNode->next = newNode;
            newNode->prev = rearNode;
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
        if (frontNode) {
            frontNode->prev = nullptr;
        } else {
            rearNode = nullptr; // queue empty now
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

    void displayForward() const {
        Node* current = frontNode;
        while (current) {
            cout << current->data << " <- ";
            current = current->next;
        }
        cout << "NULL\n";
    }

    void displayBackward() const {
        Node* current = rearNode;
        while (current) {
            cout << current->data << " -> ";
            current = current->prev;
        }
        cout << "NULL\n";
    }
};

#endif // DLL_QUEUE_H
