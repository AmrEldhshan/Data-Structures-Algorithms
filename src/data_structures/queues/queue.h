#ifndef QUEUES_H
#define QUEUES_H
#include <iostream>
using namespace std;

template <typename T>
class Queue {
private:
    struct Node {
        T data;
        Node* next;
        Node(const T& value) : data(value), next(nullptr) {}
    };

    Node* front;
    Node* rear;
    int size;

public:
    // Constructor
    Queue() : front(nullptr), rear(nullptr), size(0) {}

    // Destructor
    ~Queue() {
        clear();
    }

    // Copy constructor
    Queue(const Queue& other) : front(nullptr), rear(nullptr), size(0) {
        Node* current = other.front;
        while (current) {
            enqueue(current->data);
            current = current->next;
        }
    }

    // Copy assignment operator
    Queue& operator=(const Queue& other) {
        if (this != &other) {
            clear();
            Node* current = other.front;
            while (current) {
                enqueue(current->data);
                current = current->next;
            }
        }
        return *this;
    }

    void clear() {
        while (!isEmpty()) {
            dequeue();
        }
    }

    bool isEmpty() const {
        return front == nullptr;
    }

    void enqueue(const T& item) {
        Node* newNode = new Node(item);
        if (isEmpty()) {
            front = rear = newNode;
        } else {
            rear->next = newNode;
            rear = newNode;
        }
        size++;
    }

    T dequeue() {
        if (isEmpty()) {
            throw runtime_error("Queue underflow: cannot dequeue from an empty queue.");
        }
        Node* temp = front;
        T value = temp->data;
        front = front->next;
        if (front == nullptr) {
            rear = nullptr;
        }
        delete temp;
        size--;
        return value;
    }

    T first() const {
        if (isEmpty()) {
            throw runtime_error("Queue is empty: cannot access the first item.");
        }
        return front->data;
    }

    T back() const {  // Fixed: Changed Back to back for consistency
        if (isEmpty()) {
            throw runtime_error("Queue is empty: cannot access the last item.");  // Fixed error message
        }
        return rear->data;
    }

    int getSize() const {
        return size;
    }

    void display() const {
        Node* current = front;
        while (current) {
            cout << "[ " << current->data << " ]";
            current = current->next;
        }
        cout << endl;
    }


};

#endif // QUEUES_H
