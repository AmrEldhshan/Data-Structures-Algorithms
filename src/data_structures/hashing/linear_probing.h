#ifndef LINEAR_PROBING_H
#define LINEAR_PROBING_H
#include <iostream>

/*
Linear Probing (Open Addressing)
--------------------------------
Concept:
    When a collision occurs, the algorithm checks the next slot (index + 1)
    in a circular manner until an empty slot is found.

Hash Function:
    h(k, i) = (h'(k) + i) % table_size
    where:
        - h'(k) = key % table_size
        - i = number of attempts (probe count)

Example:
    Suppose table_size = 7, keys = {10, 17, 24}
    h(10) = 3, h(17) = 3 (collision), h(17, 1) = 4, h(24) = 3 (collision),
    h(24, 1) = 4 (collision), h(24, 2) = 5 → stored at index 5.

Advantages:
    - Simple and easy to implement.
    - Fast access time in low load factor (α < 0.7).

Disadvantages:
    - Primary Clustering (continuous blocks of occupied cells).
    - Performance degrades as table fills up.
    - Deletion requires special handling.

Time Complexity (Average Case):
    Insert:   O(1)
    Search:   O(1)
    Delete:   O(1)
Worst Case:
    O(n)
*/

class LinearProbing {
public:
    enum SlotState { EMPTY, OCCUPIED, DELETED };

    explicit LinearProbing(int size) {
        table_size = size;
        keys = new int[table_size];
        values = new int[table_size];
        state = new SlotState[table_size];

        for (int i = 0; i < table_size; ++i) {
            keys[i] = 0;
            values[i] = 0;
            state[i] = EMPTY;
        }
    }

    ~LinearProbing() {
        delete[] keys;
        delete[] values;
        delete[] state;
    }

    // Basic hash function
    int hash(int key) const {
        return key % table_size;
    }

    // Insert key-value pair
    void insert(int key, int value) {
        int index = hash(key);
        int start = index;
        int probe = 0;

        while (state[index] == OCCUPIED && keys[index] != key) {
            index = (index + 1) % table_size;
            probe++;

            if (index == start) {
                std::cout << "[Error] Hash table is full!\n";
                return;
            }
        }

        keys[index] = key;
        values[index] = value;
        state[index] = OCCUPIED;

        std::cout << "Inserted key " << key << " at index " << index
                  << " after " << probe << " probes.\n";
    }

    // Search key
    bool search(int key, int &value) const {
        int index = hash(key);
        int start = index;

        while (state[index] != EMPTY) {
            if (state[index] == OCCUPIED && keys[index] == key) {
                value = values[index];
                return true;
            }
            index = (index + 1) % table_size;
            if (index == start) break;
        }
        return false;
    }

    // Delete key
    void remove(int key) {
        int index = hash(key);
        int start = index;

        while (state[index] != EMPTY) {
            if (state[index] == OCCUPIED && keys[index] == key) {
                state[index] = DELETED;
                std::cout << "Removed key " << key << " from index " << index << ".\n";
                return;
            }
            index = (index + 1) % table_size;
            if (index == start) break;
        }
        std::cout << "[Error] Key " << key << " not found.\n";
    }

    // Display hash table
    void display() const {
        std::cout << "\nHash Table (Linear Probing):\n";
        for (int i = 0; i < table_size; ++i) {
            std::cout << i << " : ";
            if (state[i] == EMPTY)
                std::cout << "[Empty]\n";
            else if (state[i] == DELETED)
                std::cout << "[Deleted]\n";
            else
                std::cout << "Key=" << keys[i] << ", Value=" << values[i] << "\n";
        }
    }

private:
    int table_size;
    int* keys;
    int* values;
    SlotState* state;
};

#endif // LINEAR_PROBING_H
