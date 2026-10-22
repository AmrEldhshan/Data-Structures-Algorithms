// number of way = !(n-1)
// backtracking code will destroy your dreams about time and fast code

#include <iostream>
#include <climits>
using namespace std;

int n = 4;
int dist[10][10] = {
    {0, 10, 15, 20},
    {10, 0, 35, 25},
    {15, 35, 0, 30},
    {20, 25, 30, 0}
};

bool visited[10];
int ans = INT_MAX;

void tsp(int curr, int count, int cost) {
    if (count == n && dist[curr][0]) {
        ans = min(ans, cost + dist[curr][0]);
        return;
    }

    for (int i = 0; i < n; i++) {
        if (!visited[i] && dist[curr][i]) {
            visited[i] = true;
            tsp(i, count + 1, cost + dist[curr][i]);
            visited[i] = false;
        }
    }
}

int main() {
    visited[0] = true;
    tsp(0, 1, 0);
    cout << "Minimum cost = " << ans;
}


// do not write this code, that`s a shit
