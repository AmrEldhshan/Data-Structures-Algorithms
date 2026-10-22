#ifndef FOLDING_METHOD_H
#define FOLDING_METHOD_H
#include <iostream>
#include <string>
#include <algorithm>

/*
Folding Hashing Method (Stage 1)
---------------------------------
Implements both:
    - Fold-Shifting: Add all parts as they are.
    - Fold-Boundary: Reverse outer parts before adding.

Example:
    Key: 12345678
    Parts: 12, 34, 56, 78

    Fold-Shifting  → (12 + 34 + 56 + 78) = 180 → 180 % 100 = 80
    Fold-Boundary → (21 + 34 + 56 + 87) = 198 → 198 % 100 = 98

Collision handling is NOT implemented in this stage.

Time Complexity:
    Insert:   O(1)
    Search:   O(1)
    Delete:   O(1)
    Display:  O(m)

Space Complexity:
    O(m)
*/

class Folding_Method {
public:
    explicit Folding_Method(int size) {
        table_size = size;
        table = new int[table_size];
        for (int i = 0; i < table_size; i++)
            table[i] = -1;
    }

    ~Folding_Method() {
        delete[] table;
    }

    // --- Fold-Shifting ---
    int hash_fold_shifting(int key) const {
        std::string key_str = std::to_string(std::abs(key));
        int group_size = 2; // 2 digits per group
        int sum = 0;

        for (size_t i = 0; i < key_str.length(); i += group_size) {
            std::string part = key_str.substr(i, group_size);
            sum += std::stoi(part);
        }

        return sum % table_size;
    }

    // --- Fold-Boundary ---
    int hash_fold_boundary(int key) const {
        std::string key_str = std::to_string(std::abs(key));
        int group_size = 2;
        int num_parts = (key_str.length() + group_size - 1) / group_size;
        int sum = 0;

        for (int i = 0; i < num_parts; i++) {
            int start = i * group_size;
            std::string part = key_str.substr(start, group_size);

            // Reverse outer parts only
            if (i == 0 || i == num_parts - 1)
                std::reverse(part.begin(), part.end());

            sum += std::stoi(part);
        }

        return sum % table_size;
    }

    // Insert key using selected method
    void insert(int key, bool use_boundary = false) {
        int index = use_boundary ? hash_fold_boundary(key)
                                 : hash_fold_shifting(key);

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
        std::cout << "\nHash Table (Folding Method, size = " << table_size << "):\n";
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

/*
int main() {
    Folding_Method fm(100);

    fm.insert(12345678, false); // Fold-Shifting
    fm.insert(12345678, true);  // Fold-Boundary

    fm.display();
}
*/

