#ifndef DIVISION_METHOD_H
#define DIVISION_METHOD_H
#include <iostream>

/*
Division Hashing Method (Stage 1) — No Collision Resolution
----------------------------------------------------------
Hash Function:
    h(key) = key % table_size

Goal:
    Demonstrate how keys are distributed across the table.
    Collision handling is NOT implemented in this stage.

Time Complexity:
    Insert:   O(1)   (computes index and writes/checks a single slot)
    Search:   O(1)   (checks exactly one slot for the key)
    Delete:   O(1)   (would clear exactly one slot if implemented)
    Display:  O(m)   (m = table_size; prints all slots)

Notes on complexities:
    - These O(1) costs assume the hash maps the key to a single slot and
      there is no probing or chaining. If a collision occurs, insert will
      simply report it (no probing), so it still runs in O(1) time but may
      fail to store the key.
    - This is a *demonstration* stage only. Real hash tables need collision
      resolution (open addressing, chaining, etc.) for robust behavior.

Space Complexity:
    O(m) where m = table_size (array of size m).

Tips:
    - Choose table_size as a PRIME number to reduce patterned collisions
      when using the division method.
    - Use test cases to compare prime vs non-prime table sizes.
*/

class Division_Method {
public:
    explicit Division_Method(int size) {
        table_size = size;
        table = new int[table_size];
        for (int i = 0; i < table_size; i++)
            table[i] = -1; // -1 means empty
    }

    ~Division_Method() {
        delete[] table;
    }

    // Simple hash function
    int hash(int key) const {
        return key % table_size;
    }

    // Insert key (no collision resolution)
    void insert(int key) {
        int index = hash(key);
        if (table[index] == -1) {
            table[index] = key;
        } else {
            std::cout << "[Collision] Key " << key
                      << " -> Index " << index
                      << " (already occupied by " << table[index] << ")\n";
        }
    }

    // Display table content
    void display() const {
        std::cout << "\nHash Table (size = " << table_size << "):\n";
        for (int i = 0; i < table_size; i++) {
            if (table[i] == -1)
                std::cout << i << " : [Empty]\n";
            else
                std::cout << i << " : " << table[i] << "\n";
        }
    }

private:
    int table_size;
    int* table;
};

#endif
