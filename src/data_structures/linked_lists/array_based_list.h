#ifndef ARRAY_BASED_LISTS_H
#define ARRAY_BASED_LISTS_H

#include <iostream>
using namespace std;

template <typename T>
class ArrayList {
private:
    T* data;
    int capacity;
    int length;

    void resize(int newCapacity) {
        T* newData = new T[newCapacity];
        for (int i = 0; i < length; i++) {
            newData[i] = data[i];
        }
        delete[] data;
        data = newData;
        capacity = newCapacity;
    }

public:
    // Default constructor
    ArrayList(int cap = 10) {
        capacity = cap;
        data = new T[capacity];
        length = 0;
    }

    // Copy constructor (Deep copy)
    ArrayList(const ArrayList<T>& other) {
        capacity = other.capacity;
        length = other.length;
        data = new T[capacity];
        for (int i = 0; i < length; i++) {
            data[i] = other.data[i];
        }
    }

    // Copy assignment operator
    ArrayList<T>& operator=(const ArrayList<T>& other) {
        if (this != &other) {
            delete[] data;               // Free current data
            this->data = other.data;     // Shallow copy: just copy pointer
            this->capacity = other.capacity;
            this->length = other.length;
        }
        return *this;
    }

    // Destructor
    ~ArrayList() {
        delete[] data;
    }

    // Check if list is empty
    bool isEmpty() const {
        return length == 0;
    }

    // Get number of elements
    int size() const {
        return length;
    }

    // Insert at end
    void insertAtEnd(T value) {
        if (length == capacity) {
            resize(capacity * 2);
        }
        data[length++] = value;
    }

    // Insert at specific position
    void insertAtPosition(int pos, T value) {
        if (pos < 0 || pos > length) {
            cout << "Invalid position.\n";
            return;
        }
        if (length == capacity) {
            resize(capacity * 2);
        }
        for (int i = length; i > pos; --i) {
            data[i] = data[i - 1];
        }
        data[pos] = value;
        length++;
    }

    // Delete at position
    void deleteAtPosition(int pos) {
        if (pos < 0 || pos >= length) {
            cout << "Invalid position.\n";
            return;
        }
        for (int i = pos; i < length - 1; ++i) {
            data[i] = data[i + 1];
        }
        length--;
    }

    // Get value at index
    T getAt(int pos) const {
        if (pos < 0 || pos >= length) {
            throw out_of_range("Index out of range");
        }
        return data[pos];
    }

    // Set value at index
    void setAt(int pos, T value) {
        if (pos < 0 || pos >= length) {
            cout << "Invalid index.\n";
            return;
        }
        data[pos] = value;
    }

    // Display contents
    void display() const {
        for (int i = 0; i < length; ++i) {
            cout << data[i] << " ";
        }
        cout << endl;
    }

    // Clear list
    void clear() {
        length = 0;
    }
};

#endif // ARRAY_BASED_LISTS_H
