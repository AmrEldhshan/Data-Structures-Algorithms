#include <iostream>
using namespace std;

int graph[10][10] = {
    {0,1,0,1,0},
    {1,0,1,1,1},
    {0,1,0,0,1},
    {1,1,0,0,1},
    {0,1,1,1,0}
};

int path[10];
int n = 5;

bool isSafe(int v, int pos) {
    if (!graph[path[pos - 1]][v])
        return false;

    for (int i = 0; i < pos; i++)
        if (path[i] == v)
            return false;

    return true;
}

bool hamiltonian(int pos) {
    if (pos == n)
        return graph[path[pos - 1]][path[0]];

    for (int v = 1; v < n; v++) {
        if (isSafe(v, pos)) {
            path[pos] = v;
            if (hamiltonian(pos + 1))
                return true;
            path[pos] = -1;
        }
    }
    return false;
}

int main() {
    path[0] = 0;
    for (int i = 1; i < n; i++)
        path[i] = -1;

    if (hamiltonian(1)) {
        for (int i = 0; i < n; i++)
            cout << path[i] << " ";
        cout << path[0];
    } else {
        cout << "No Hamiltonian Cycle";
    }
}
