#ifndef QUADRATIC_PROBING_H
#define QUADRATIC_PROBING_H

#include <iostream>
#include <cmath>
using namespace std;

/*
---------------------------------------------
Quadratic Probing (Open Addressing)
---------------------------------------------
Pros:
- Reduces primary clustering.
- Still simple and efficient to implement.
- Faster than chaining when table is not crowded.

Cons:
- Secondary clustering still exists.
- Needs careful choice of constants c1, c2 and table size.
- Deletion handling is complex.

Cost:
- Average Case: O(1)
- Worst Case: O(n)
---------------------------------------------
*/

class QuadraticProbing {
private:
    int* table;        // Dynamic array for the hash table
    int tableSize;     // Size of the hash table
    int count;         // Number of elements inserted
    const int EMPTY = -1;

    int hashFunction(int key) const {
        return key % tableSize;
    }

public:
    QuadraticProbing(int size = 10) {
        tableSize = size;
        table = new int[tableSize];
        for (int i = 0; i < tableSize; ++i)
            table[i] = EMPTY;
        count = 0;
    }

    ~QuadraticProbing() {
        delete[] table;
    }

    // Insert key using quadratic probing
    void insert(int key) {
        if (count == tableSize) {
            cout << "Hash Table is Full! Rehash needed.\n";
            return;
        }

        int index = hashFunction(key);
        int i = 0;

        // Quadratic probing formula: (h(k) + i^2) % tableSize
        while (table[(index + i * i) % tableSize] != EMPTY) {
            i++;
            if (i == tableSize) {
                cout << "Cannot insert key (no empty slot found).\n";
                return;
            }
        }

        table[(index + i * i) % tableSize] = key;
        count++;
    }

    // Search for a key
    bool search(int key) {
        int index = hashFunction(key);
        int i = 0;

        while (table[(index + i * i) % tableSize] != EMPTY) {
            if (table[(index + i * i) % tableSize] == key)
                return true;
            i++;
            if (i == tableSize)
                break;
        }

        return false;
    }

    // Display hash table
    void display() {
        cout << "\nHash Table (Quadratic Probing):\n";
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
