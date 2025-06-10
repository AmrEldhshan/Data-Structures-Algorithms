#ifndef DOUBLY_LINKED_LIST_H
#define DOUBLY_LINKED_LIST_H

#include <iostream>
#include <stdexcept>

template <typename T>
class DoublyLinkedList {
private:
    struct Node {
        T data;
        Node* next;
        Node* prev;
        Node(T value) : data(value), next(nullptr), prev(nullptr) {}
    };

    Node* head;
    Node* tail;
    int size;

public:
    // Constructor
    DoublyLinkedList() : head(nullptr), tail(nullptr), size(0) {}

    // Destructor
    ~DoublyLinkedList() {
        clear();
    }

    // Check if list is empty
    bool empty() const {
        return head == nullptr;
    }

    // Get size
    int getSize() const {
        return size;
    }

    // Insert at front
    void push_front(const T& value) {
        Node* newNode = new Node(value);
        newNode->next = head;

        if (head != nullptr)
            head->prev = newNode;
        else
            tail = newNode;

        head = newNode;
        ++size;
    }

    // Insert at back
    void push_back(const T& value) {
        Node* newNode = new Node(value);
        newNode->prev = tail;

        if (tail != nullptr)
            tail->next = newNode;
        else
            head = newNode;

        tail = newNode;
        ++size;
    }

    // Remove from front
    bool pop_front() {
        if (empty()) return false;
        Node* temp = head;
        head = head->next;

        if (head)
            head->prev = nullptr;
        else
            tail = nullptr;

        delete temp;
        --size;
        return true;
    }

    // Remove from back
    bool pop_back() {
        if (empty()) return false;
        Node* temp = tail;
        tail = tail->prev;

        if (tail)
            tail->next = nullptr;
        else
            head = nullptr;

        delete temp;
        --size;
        return true;
    }

    // Search for an item
    bool contains(const T& value) const {
        Node* current = head;
        while (current) {
            if (current->data == value)
                return true;
            current = current->next;
        }
        return false;
    }

    // Insert in sorted order (for ordered doubly linked list)
    void insert_sorted(const T& value) {
        Node* newNode = new Node(value);

        if (!head || value <= head->data) {
            push_front(value);
            delete newNode;
            return;
        }

        if (value >= tail->data) {
            push_back(value);
            delete newNode;
            return;
        }

        Node* current = head->next;
        while (current && current->data < value) {
            current = current->next;
        }

        newNode->next = current;
        newNode->prev = current->prev;
        current->prev->next = newNode;
        current->prev = newNode;

        ++size;
    }

    // Delete a specific value
    bool remove(const T& value) {
        Node* current = head;

        while (current) {
            if (current->data == value) {
                if (current == head) {
                    pop_front();
                } else if (current == tail) {
                    pop_back();
                } else {
                    current->prev->next = current->next;
                    current->next->prev = current->prev;
                    delete current;
                    --size;
                }
                return true;
            }
            current = current->next;
        }
        return false;
    }

    // Print forward
    void print_forward() const {
        Node* current = head;
        while (current) {
            std::cout << current->data << " <-> ";
            current = current->next;
        }
        std::cout << "nullptr\n";
    }

    // Print backward
    void print_backward() const {
        Node* current = tail;
        while (current) {
            std::cout << current->data << " <-> ";
            current = current->prev;
        }
        std::cout << "nullptr\n";
    }

    // Clear the list
    void clear() {
        while (!empty()) {
            pop_front();
        }
    }


    T first() const {
        if (empty()) throw std::runtime_error("List is empty");
        return head->data;
    }

    T back() const {
        if (empty()) throw std::runtime_error("List is empty");
        return tail->data;
    }
    T at(int index) const{
        if (index < 0 || index >= size) {
            throw std::out_of_range("Index out of range");
        }
        Node* current = head;
        for (int i = 0; i < index; ++i) {
            current = current->next;
        }
        return current->data;
    }

    void reverse() {
        Node* current = head;
        Node* temp = nullptr;

        while (current) {
            temp = current->prev;
            current->prev = current->next;
            current->next = temp;
            current = current->prev; // Move to the next node in the original order
        }

        // Swap head and tail
        temp = head;
        head = tail;
        tail = temp;
    }

    // Copy constructor
    DoublyLinkedList(const DoublyLinkedList& other) : head(nullptr), tail(nullptr), size(0) {
        Node* current = other.head;
        while (current) {
            push_back(current->data);
            current = current->next;
        }
    }

    // Assignment operator
    DoublyLinkedList& operator=(const DoublyLinkedList& other) {
        if (this != &other) {
            clear();
            Node* current = other.head;
            while (current) {
                push_back(current->data);
                current = current->next;
            }
        }
        return *this;
    }
    // Move constructor
    DoublyLinkedList(DoublyLinkedList&& other) noexcept
        : head(other.head), tail(other.tail), size(other.size) {
        other.head = nullptr;
        other.tail = nullptr;
        other.size = 0;
    }
    // Move assignment operator
    DoublyLinkedList& operator=(DoublyLinkedList&& other) noexcept {
        if (this != &other) {
            clear();
            head = other.head;
            tail = other.tail;
            size = other.size;

            other.head = nullptr;
            other.tail = nullptr;
            other.size = 0;
        }
        return *this;
    }

    // Iterator class for the doubly linked list
    class Iterator {
    private:
        Node* current;
    public:
        Iterator(Node* node) : current(node) {}

        T& operator*() {
            return current->data;
        }

        Iterator& operator++() {
            current = current->next;
            return *this;
        }

        Iterator& operator--() {
            current = current->prev;
            return *this;
        }

        bool operator!=(const Iterator& other) const {
            return current != other.current;
        }

        bool operator==(const Iterator& other) const {
            return current == other.current;
        }
    };
    Iterator begin() {
        return Iterator(head);
    }
    Iterator end() {
        return Iterator(nullptr);
    }
    // Const iterator class for the doubly linked list
    class ConstIterator {
    private:
        const Node* current;
    public:
        ConstIterator(const Node* node) : current(node) {}

        const T& operator*() const {
            return current->data;
        }

        ConstIterator& operator++() {
            current = current->next;
            return *this;
        }

        ConstIterator& operator--() {
            current = current->prev;
            return *this;
        }

        bool operator!=(const ConstIterator& other) const {
            return current != other.current;
        }

        bool operator==(const ConstIterator& other) const {
            return current == other.current;
        }
    };
    ConstIterator begin() const {
        return ConstIterator(head);
    }
    ConstIterator end() const {
        return ConstIterator(nullptr);
    }
    ConstIterator cbegin() const {
        return ConstIterator(head);
    }
    ConstIterator cend() const {
        return ConstIterator(nullptr);
    }

};

#endif // DOUBLY_LINKED_LIST_H
