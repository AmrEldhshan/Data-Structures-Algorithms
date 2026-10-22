/****************************************************
 * Array-Based Disjoint Sets (Union-Find)
 *
 * Representation:
 *  - parent[i] : parent of element i
 *  - size[i]   : number of elements in the set
 *                (valid only if i is a root)
 *
 * Operations:
 *  - Find(a)
 *  - Union(a, b) using WEIGHT RULE (union by size)
 *
 * Time Complexity:
 *  - Find()  : O(log n)
 *  - Union() : O(log n)
 *
 * Space Complexity:
 *  - O(n) for parent[] and size[]
 ****************************************************/

#include <iostream>
using namespace std;

class DisjointSetsArray {
private:
    int* parent;
    int* size;
    int n;

public:
    // Constructor
    DisjointSetsArray(int n) {
        this->n = n;
        parent = new int[n];
        size = new int[n];

        // Initialize singleton sets
        for (int i = 0; i < n; i++) {
            parent[i] = i;  // each element is its own root
            size[i] = 1;    // each set has size 1
        }
    }

    // Find operation
    // Follows parent chain until root
    int Find(int a) {
        while (parent[a] != a) {
            a = parent[a];
        }
        return a;
    }

    // Union operation using WEIGHT RULE
    void Union(int a, int b) {
        int rootA = Find(a);
        int rootB = Find(b);

        if (rootA == rootB)
            return; // already in same set

        // Attach smaller set under larger set
        if (size[rootA] < size[rootB]) {
            parent[rootA] = rootB;
            size[rootB] += size[rootA];
        } else {
            parent[rootB] = rootA;
            size[rootA] += size[rootB];
        }
    }

    // Destructor
    ~DisjointSetsArray() {
        delete[] parent;
        delete[] size;
    }
};

// Example usage
int main() {
    DisjointSetsArray ds(5);

    ds.Union(1, 2);
    ds.Union(3, 4);
    ds.Union(0, 1);
    ds.Union(1, 3);

    for (int i = 0; i < 5; i++) {
        cout << "Find(" << i << ") = " << ds.Find(i) << endl;
    }

    return 0;
}
