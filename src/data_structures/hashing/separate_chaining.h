#ifndef SEPARATE_CHAINING_H
#define SEPARATE_CHAINING_H

#include <iostream>
#include <list>

/*
Separate Chaining (Open Hashing)
--------------------------------
Concept:
    When two keys hash to the same index (collision), we store them
    in a linked list (chain) at that index.

Hash Function:
    h(key) = key % table_size

Structure:
    table[i] -> Linked List of keys that map to index i

Time Complexity:
    Best Case:      O(1)
    Average Case:   O(1 + α)     (α = Load Factor = n / m)
    Worst Case:     O(n)         (All keys in one list)

Goal:
    Demonstrate how Separate Chaining handles collisions efficiently
    using linked lists for storage within each hash slot.

Advantages:
    - Simple and efficient for low load factors (α < 1).
    - No need to rehash or probe for new slots.
    - Works well even if the hash table fills up.
    - Deletion is straightforward (just remove from the list).

Disadvantages:
    - Requires extra memory for linked list nodes.
    - Performance degrades if too many elements hash to the same index.
    - Cache performance is worse compared to open addressing.
*/

class SeparateChaining {
private:
    int table_size;
    std::list<int>* table;  // dynamic array of linked lists

    // Hash Function
    int hash(int key) const {
        return key % table_size;
    }

public:
    // Constructor
    explicit SeparateChaining(int size) {
        table_size = size;
        table = new std::list<int>[table_size];  // allocate dynamic array of lists
    }

    // Destructor
    ~SeparateChaining() {
        delete[] table;
    }

    // Insert key into the hash table
    void insert(int key) {
        int index = hash(key);
        table[index].push_back(key);
        std::cout << "[Insert] Key " << key << " -> Index " << index << "\n";
    }

    // Search key in hash table
    bool search(int key) const {
        int index = hash(key);
        for (int val : table[index]) {
            if (val == key)
                return true;
        }
        return false;
    }

    // Delete key from hash table
    void remove(int key) {
        int index = hash(key);
        table[index].remove(key);
        std::cout << "[Delete] Key " << key << " removed from Index " << index << "\n";
    }

    // Display table contents
    void display() const {
        std::cout << "\nHash Table (Separate Chaining):\n";
        for (int i = 0; i < table_size; i++) {
            std::cout << "[" << i << "] -> ";
            for (int val : table[i])
                std::cout << val << " -> ";
            std::cout << "NULL\n";
        }
        std::cout << std::endl;
    }
};

#endif // SEPARATE_CHAINING_H
