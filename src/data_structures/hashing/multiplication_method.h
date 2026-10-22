#ifndef MULTIPLICATION_METHOD_H
#define MULTIPLICATION_METHOD_H

#include <iostream>
#include <cmath>

/*
 * Multiplication Hashing Method (Stage 1) — No Collision Resolution
 * ------------------------------------------------------------------
 * Hash Function:
 *     h(key) = floor( table_size * ((key * A) mod 1) )
 *
 *     where:
 *         A ≈ (√5 − 1) / 2 ≈ 0.6180339887  (Knuth’s recommended value)
 *
 * Goal:
 *     Demonstrate how keys are distributed across the table using
 *     the multiplication method. Collision handling is NOT implemented
 *     in this stage — collisions are simply reported.
 *
 * Time Complexity:
 *     Insert:   O(1)   (computes index and writes/checks a single slot)
 *     Search:   O(1)   (checks exactly one slot for the key)
 *     Delete:   O(1)   (clears exactly one slot if the key matches)
 *     Display:  O(m)   (prints all slots; m = table_size)
 *
 * Notes:
 *     - Collisions are not resolved. If a slot is already occupied,
 *       the new key will not be inserted and a message will be shown.
 *     - This version uses dynamic arrays for flexibility.
 *
 * Space Complexity:
 *     O(m) where m = table_size
 *
 * Tip:
 *     Choose table_size as a power of 2 to maximize uniformity.
 */

class MultiplicationHash {
private:
    int* table;                // dynamically allocated hash table
    int tableSize;             // number of slots
    static constexpr double A = 0.6180339887;  // Knuth’s constant

    // Core hash function
    int hash(int key) const {
        double fractional = (key * A) - std::floor(key * A); // (k * A mod 1)
        return static_cast<int>(std::floor(tableSize * fractional));
    }

public:
    // Constructor
    explicit MultiplicationHash(int size) : tableSize(size) {
        table = new int[tableSize];
        for (int i = 0; i < tableSize; ++i)
            table[i] = -1; // -1 represents empty
    }

    // Destructor
    ~MultiplicationHash() {
        delete[] table;
    }

    // Insert key
    void insert(int key) {
        int index = hash(key);
        if (table[index] == -1) {
            table[index] = key;
            std::cout << "Inserted key " << key << " at index " << index << ".\n";
        } else {
            std::cout << "Collision detected! Slot " << index
                      << " already contains key " << table[index]
                      << ". Key " << key << " not inserted.\n";
        }
    }

    // Search key
    bool search(int key) const {
        int index = hash(key);
        if (table[index] == key) {
            std::cout << "Key " << key << " found at index " << index << ".\n";
            return true;
        } else {
            std::cout << "Key " << key << " not found.\n";
            return false;
        }
    }

    // Delete key
    void remove(int key) {
        int index = hash(key);
        if (table[index] == key) {
            table[index] = -1;
            std::cout << "Key " << key << " deleted from index " << index << ".\n";
        } else {
            std::cout << "Key " << key << " not found — cannot delete.\n";
        }
    }

    // Display entire hash table
    void display() const {
        std::cout << "\n--- Hash Table (Multiplication Method) ---\n";
        for (int i = 0; i < tableSize; ++i) {
            if (table[i] == -1)
                std::cout << "[" << i << "] : EMPTY\n";
            else
                std::cout << "[" << i << "] : " << table[i] << "\n";
        }
        std::cout << "------------------------------------------\n";
    }
};

#endif // MULTIPLICATION_METHOD_H
