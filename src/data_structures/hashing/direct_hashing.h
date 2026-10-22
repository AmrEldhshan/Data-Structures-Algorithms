#ifndef DIRECT_HASHING_H
#define DIRECT_HASHING_H
#include <iostream>

/*
Time Complexity:
    Searching:  O(1)
    Insertion:  O(1)
    Deletion:   O(1)

Disadvantages:
    - High memory consumption.
    - Address space (array) must be as large as the key value, which is inefficient.

Advantages:
    - Extremely fast (requires only one operation).
*/

class Direct_Hashing {
public:
    enum SlotState { EMPTY, OCCUPIED, REMOVED };

    explicit Direct_Hashing(int size) {
        this->table_size = size;
        table = new int[table_size];
        state = new SlotState[table_size];

        for (int i = 0; i < table_size; ++i) {
            table[i] = 0;
            state[i] = EMPTY;
        }
    }

    ~Direct_Hashing() {
        delete[] table;
        delete[] state;
    }

    void insert(int key, int value) {
        if (key >= 0 && key < table_size) {
            table[key] = value;
            state[key] = OCCUPIED;
        } else {
            std::cout << "[Error] Key " << key << " is out of range (0 - "
                      << table_size - 1 << ")\n";
        }
    }

    bool search(int key, int &value) const {
        if (key >= 0 && key < table_size && state[key] == OCCUPIED) {
            value = table[key];
            return true;
        }
        return false;
    }

    void remove(int key) {
        if (key >= 0 && key < table_size && state[key] == OCCUPIED) {
            state[key] = REMOVED;
        } else {
            std::cout << "[Error] Cannot remove: Key " << key
                      << " not found or invalid.\n";
        }
    }

private:
    int table_size;
    int* table;
    SlotState* state;
};

// Example test (you can uncomment to run)
/*
int main() {
    Direct_Hashing dh(10);

    dh.insert(5, 500);
    dh.insert(2, 200);

    int value;
    if (dh.search(5, value))
        std::cout << "Found: " << value << "\n";
    else
        std::cout << "Not found.\n";

    dh.remove(5);

    if (dh.search(5, value))
        std::cout << "Found: " << value << "\n";
    else
        std::cout << "Not found after deletion.\n";

    return 0;
}
*/

#endif // DIRECT_HASHING_H
