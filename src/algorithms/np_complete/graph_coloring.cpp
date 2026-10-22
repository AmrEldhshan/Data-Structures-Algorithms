#include <iostream>
using namespace std;

int graph[10][10] = {
    {0,1,1,1},
    {1,0,1,0},
    {1,1,0,1},
    {1,0,1,0}
};

int color[10];
int n = 4, m = 3;

bool isSafe(int v, int c) {
    for (int i = 0; i < n; i++)
        if (graph[v][i] && color[i] == c)
            return false;
    return true;
}

bool graphColoring(int v) {
    if (v == n)
        return true;

    for (int c = 1; c <= m; c++) {
        if (isSafe(v, c)) {
            color[v] = c;
            if (graphColoring(v + 1))
                return true;
            color[v] = 0;
        }
    }
    return false;
}

int main() {
    if (graphColoring(0)) {
        for (int i = 0; i < n; i++)
            cout << color[i] << " ";
    } else {
        cout << "No solution";
    }
}
