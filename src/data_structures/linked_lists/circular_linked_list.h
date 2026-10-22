#ifndef CIRCULAR_LINKED_LIST_H
#define CIRCULAR_LINKED_LIST_H

#include <iostream>
using namespace std;

template <typename T>
class CircularDoublyLinkedList {
private:
    struct Node {
        T data;
        Node* next;
        Node* prev;
        Node(T value) : data(value), next(nullptr), prev(nullptr) {}
    };

    Node* head;
    int size;

public:
    CircularDoublyLinkedList() : head(nullptr), size(0) {}

    ~CircularDoublyLinkedList() {
        clear();
    }

    bool isEmpty() const {
        return size == 0;
    }

    int getSize() const {
        return size;
    }

    void insertAtBeginning(const T& value) {
        Node* newNode = new Node(value);
        if (isEmpty()) {
            head = newNode;
            head->next = head;
            head->prev = head;
        } else {
            Node* tail = head->prev;
            newNode->next = head;
            newNode->prev = tail;
            tail->next = newNode;
            head->prev = newNode;
            head = newNode;
        }
        size++;
    }

    void insertAtEnd(const T& value) {
        Node* newNode = new Node(value);
        if (isEmpty()) {
            head = newNode;
            head->next = head;
            head->prev = head;
        } else {
            Node* tail = head->prev;
            tail->next = newNode;
            newNode->prev = tail;
            newNode->next = head;
            head->prev = newNode;
        }
        size++;
    }

    void deleteFirst() {
        if (isEmpty()) {
            cout << "List is empty, cannot delete." << endl;
            return;
        }

        if (size == 1) {
            delete head;
            head = nullptr;
        } else {
            Node* tail = head->prev;
            Node* temp = head;
            head = head->next;
            head->prev = tail;
            tail->next = head;
            delete temp;
        }
        size--;
    }

    void deleteLast() {
        if (isEmpty()) {
            cout << "List is empty, cannot delete." << endl;
            return;
        }

        if (size == 1) {
            delete head;
            head = nullptr;
        } else {
            Node* tail = head->prev;
            Node* newTail = tail->prev;
            newTail->next = head;
            head->prev = newTail;
            delete tail;
        }
        size--;
    }

    void clear() {
        while (!isEmpty()) {
            deleteFirst();
        }
    }

    void printList() const {
        if (isEmpty()) {
            cout << "List is empty." << endl;
            return;
        }

        Node* current = head;
        do {
            cout << current->data << " ";
            current = current->next;
        } while (current != head);
        cout << endl;
    }

    void printListReverse() const {
        if (isEmpty()) {
            cout << "List is empty." << endl;
            return;
        }

        Node* current = head->prev;
        do {
            cout << current->data << " ";
            current = current->prev;
        } while (current != head->prev);
        cout << endl;
    }

    bool search(const T& value) const {
        if (isEmpty()) return false;

        Node* current = head;
        do {
            if (current->data == value)
                return true;
            current = current->next;
        } while (current != head);

        return false;
    }

    void removeIf(bool (*predicate)(T)) {
        if (isEmpty()) return;

        Node* current = head;
        int count = size; // prevent infinite loop after deletion
        while (count--) {
            Node* nextNode = current->next;
            if (predicate(current->data)) {
                if (current == head) {
                    deleteFirst();
                    current = head;
                    continue;
                } else if (current == head->prev) {
                    deleteLast();
                } else {
                    current->prev->next = current->next;
                    current->next->prev = current->prev;
                    delete current;
                    size--;
                }
            }
            current = nextNode;
        }
    }

    void sort() {
        if (isEmpty() || size == 1) return;

        Node* sorted = nullptr;

        auto insertSorted = [&](Node* node) {
            if (!sorted) {
                sorted = node;
                sorted->next = sorted->prev = sorted;
                return;
            }

            Node* curr = sorted;
            do {
                if (node->data < curr->data) {
                    Node* prev = curr->prev;
                    prev->next = node;
                    node->prev = prev;
                    node->next = curr;
                    curr->prev = node;

                    if (curr == sorted) sorted = node;
                    return;
                }
                curr = curr->next;
            } while (curr != sorted);

            Node* tail = sorted->prev;
            tail->next = node;
            node->prev = tail;
            node->next = sorted;
            sorted->prev = node;
        };

        Node* curr = head;
        Node* next;
        do {
            next = curr->next;
            curr->next = curr->prev = curr;  // isolate
            insertSorted(curr);
            curr = next;
        } while (curr != head);

        head = sorted;
    }

    void reverse() {
        if (isEmpty() || size == 1) return;

        Node* current = head;
        do {
            Node* temp = current->next;
            current->next = current->prev;
            current->prev = temp;
            current = temp;
        } while (current != head);

        head = head->prev;
    }
};

// Sample main for demonstration
// int main() {
//     CircularDoublyLinkedList<int> list;

//     list.insertAtBeginning(10);
//     list.insertAtBeginning(20);
//     list.insertAtEnd(30);
//     list.insertAtEnd(40);

//     cout << "Circular List (Forward): ";
//     list.printList();

//     cout << "Circular List (Reverse): ";
//     list.printListReverse();

//     list.deleteFirst();
//     cout << "After deleting first element (Forward): ";
//     list.printList();

//     list.deleteLast();
//     cout << "After deleting last element (Forward): ";
//     list.printList();

//     list.sort();
//     cout << "After sorting: ";
//     list.printList();

//     list.reverse();
//     cout << "After reversing: ";
//     list.printList();

//     bool found = list.search(30);
//     cout << "Element 30 found: " << (found ? "Yes" : "No") << endl;

//     return 0;
// }

#endif // CIRCULAR_LINKED_LIST_H
