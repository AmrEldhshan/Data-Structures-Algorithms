#ifndef MID_SQUARE_METHOD_H
#define MID_SQUARE_METHOD_H
#include <iostream>
#include <cmath>
#include <string>
#include <algorithm>

/*
Mid-Square Hashing Method (Stage 1)
-----------------------------------
Hash Function:
    h(key) = middle digits of (key * key)

Goal:
    Demonstrate how keys are distributed using the mid-square method.
    Collision handling is NOT implemented in this stage.

How it works:
    1. Square the key.
    2. Extract the middle digits (or bits).
    3. Take modulo table_size to fit the hash table.

Advantages:
    - Key patterns are less likely to cause clustering.
    - Works well even when keys share similar prefixes or suffixes.

Disadvantages:
    - Slightly slower than division (extra multiplication and digit extraction).
    - Still susceptible to collisions (if middle digits overlap).

Time Complexity:
    Insert:   O(1)   → constant work to compute square, extract middle, insert.
    Search:   O(1)
    Delete:   O(1)
    Display:  O(m)   → m = table_size

Space Complexity:
    O(m) → array of size m

Tips:
    - Choose table_size as a PRIME number to minimize secondary collisions.
    - Try different digit extraction strategies to see the effect.
*/

class Mid_Square_Method {
public:
    explicit Mid_Square_Method(int size) {
        table_size = size;
        table = new int[table_size];
        for (int i = 0; i < table_size; i++)
            table[i] = -1; // -1 means empty
    }

    ~Mid_Square_Method() {
        delete[] table;
    }

    // Mid-Square Hash Function
    int hash(int key) const {
        long long squared = static_cast<long long>(key) * key;
        int num_digits = std::to_string(squared).length();

        // Extract middle digits — here we take the middle 2 digits
        int mid = num_digits / 2;
        int extract_len = 2;

        std::string sq_str = std::to_string(squared);
        std::string mid_digits = sq_str.substr(
            std::max(0, mid - extract_len / 2),
            extract_len
        );

        int mid_val = std::stoi(mid_digits);
        return mid_val % table_size;
    }

    // Insert key (no collision resolution)
    void insert(int key) {
        int index = hash(key);
        if (table[index] == -1) {
            table[index] = key;
        } else {
            std::cout << "[Collision] Key " << key
                      << " -> Index " << index
                      << " (occupied by " << table[index] << ")\n";
        }
    }

    // Display table
    void display() const {
        std::cout << "\nHash Table (Mid-Square Method, size = " << table_size << "):\n";
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
