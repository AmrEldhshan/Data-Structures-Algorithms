/****************************************************
 * Tree-Based Disjoint Sets (Union-Find)
 *
 * Representation:
 *  - Each set is represented as a TREE
 *  - Each node stores:
 *      - element id
 *      - pointer to parent
 *      - size of the set (only meaningful at root)
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
 *  - O(n) nodes
 ****************************************************/

#include <iostream>
using namespace std;

// Node of the tree
struct Node {
    int id;         // element identifier
    Node* parent;   // pointer to parent
    int size;       // number of elements in this set (valid only at root)

    Node(int _id) {
        id = _id;
        parent = this;   // initially parent is itself (root)
        size = 1;        // singleton set
    }
};

class DisjointSetsTree {
private:
    Node** nodes;   // array of pointers to nodes
    int n;

public:
    // Constructor
    DisjointSetsTree(int n) {
        this->n = n;
        nodes = new Node*[n];
        for (int i = 0; i < n; i++) {
            nodes[i] = new Node(i);
        }
    }

    // Find operation
    // Follows parent pointers until reaching the root
    Node* Find(Node* x) {
        while (x->parent != x) {
            x = x->parent;
        }
        return x;
    }

    // Wrapper for Find using element id
    int Find(int a) {
        return Find(nodes[a])->id;
    }

    // Union operation using WEIGHT RULE
    void Union(int a, int b) {
        Node* rootA = Find(nodes[a]);
        Node* rootB = Find(nodes[b]);

        if (rootA == rootB)
            return; // already in the same set

        // Weight rule: attach smaller tree under larger tree
        if (rootA->size < rootB->size) {
            rootA->parent = rootB;
            rootB->size += rootA->size;
        } else {
            rootB->parent = rootA;
            rootA->size += rootB->size;
        }
    }

    // Destructor
    ~DisjointSetsTree() {
        for (int i = 0; i < n; i++)
            delete nodes[i];
        delete[] nodes;
    }
};

// Example usage
int main() {
    DisjointSetsTree ds(5);

    ds.Union(1, 2);
    ds.Union(3, 4);
    ds.Union(0, 1);
    ds.Union(1, 3);

    for (int i = 0; i < 5; i++) {
        cout << "Find(" << i << ") = " << ds.Find(i) << endl;
    }

    return 0;
}
