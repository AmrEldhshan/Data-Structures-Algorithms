#ifndef DOUBLE_HASHING_H
#define DOUBLE_HASHING_H

#include <iostream>
using namespace std;

/*
--------------------------------------------------------
Double Hashing (Open Addressing)
--------------------------------------------------------
Idea:
    Use a second hash function to compute the probe step.

Hash Functions:
    h1(key) = key % table_size
    h2(key) = R - (key % R)    // R should be a prime < table_size

Probe Sequence:
    index = (h1(key) + i * h2(key)) % table_size

Pros:
    - Avoids both primary and secondary clustering.
    - Provides excellent key distribution.

Cons:
    - Slightly more complex (two hash functions).
    - Must carefully choose R and table size.
    - Deletion is tricky.

Cost:
    - Average Case: O(1)
    - Worst Case: O(n)
--------------------------------------------------------
*/

class DoubleHashing {
private:
    int* table;          // Dynamic array for hash table
    int tableSize;       // Total table slots
    int prime;           // Prime used for second hash
    int count;           // Number of elements inserted
    const int EMPTY = -1;

    // Primary hash
    int hash1(int key) const {
        return key % tableSize;
    }

    // Secondary hash (must not produce zero)
    int hash2(int key) const {
        return prime - (key % prime);
    }

public:
    // Constructor
    DoubleHashing(int size = 11, int primeNum = 7) {
        tableSize = size;
        prime = primeNum;
        table = new int[tableSize];
        for (int i = 0; i < tableSize; ++i)
            table[i] = EMPTY;
        count = 0;
    }

    // Destructor
    ~DoubleHashing() {
        delete[] table;
    }

    // Insert key using double hashing
    void insert(int key) {
        if (count == tableSize) {
            cout << "Hash Table is Full! Rehash needed.\n";
            return;
        }

        int index = hash1(key);
        int step = hash2(key);
        int i = 0;

        // Probe sequence: h1 + i*h2
        while (table[(index + i * step) % tableSize] != EMPTY) {
            i++;
            if (i == tableSize) {
                cout << "Cannot insert key (no empty slot found).\n";
                return;
            }
        }

        table[(index + i * step) % tableSize] = key;
        count++;
    }

    // Search for a key
    bool search(int key) const {
        int index = hash1(key);
        int step = hash2(key);
        int i = 0;

        while (table[(index + i * step) % tableSize] != EMPTY) {
            if (table[(index + i * step) % tableSize] == key)
                return true;
            i++;
            if (i == tableSize)
                break;
        }
        return false;
    }

    // Display hash table
    void display() const {
        cout << "\nHash Table (Double Hashing):\n";
        for (int i = 0; i < tableSize; ++i) {
            cout << i << ": ";
            if (table[i] != EMPTY)
                cout << table[i];
            else
                cout << "EMPTY";
            cout << endl;
        }
    }
};

#endif
