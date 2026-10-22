#include <algorithm>
#include <cmath>
#include <functional>
#include <iostream>
#include <limits>
#include <queue>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

using namespace std;

// ---------------------------------------------------------------------------
// A* search on a grid
//
// A* is Dijkstra with a heuristic: f(n) = g(n) + h(n), where g is the cost so
// far and h estimates the remaining cost. On a 4-direction grid with unit
// costs, Manhattan distance is an admissible and consistent heuristic.
//
// With a consistent heuristic, the first time the goal is popped its cost is
// optimal. Time is O(E log V) in the worst case, usually much less.
// ---------------------------------------------------------------------------
struct Node {
    int row;
    int column;
    int costSoFar;

    bool operator>(const Node& other) const {
        return costSoFar > other.costSoFar;
    }
};

int manhattan(int row, int column, int goalRow, int goalColumn) {
    return abs(row - goalRow) + abs(column - goalColumn);
}

vector<pair<int, int>> aStar(const vector<string>& grid,
                             pair<int, int> start,
                             pair<int, int> goal) {
    int rows = static_cast<int>(grid.size());
    int columns = static_cast<int>(grid[0].size());

    const int INF = numeric_limits<int>::max() / 4;
    vector<vector<int>> distance(rows, vector<int>(columns, INF));
    vector<vector<pair<int, int>>> parent(
        rows, vector<pair<int, int>>(columns, {-1, -1}));

    // (f, g, row, column)
    priority_queue<tuple<int, int, int, int>,
                   vector<tuple<int, int, int, int>>,
                   greater<>> open;

    distance[start.first][start.second] = 0;
    open.push({manhattan(start.first, start.second, goal.first, goal.second),
               0, start.first, start.second});

    const int dr[] = {-1, 1, 0, 0};
    const int dc[] = {0, 0, -1, 1};

    while (!open.empty()) {
        auto [estimate, costSoFar, row, column] = open.top();
        open.pop();

        (void)estimate;

        if (row == goal.first && column == goal.second) break;
        if (costSoFar != distance[row][column]) continue;

        for (int direction = 0; direction < 4; ++direction) {
            int nextRow = row + dr[direction];
            int nextColumn = column + dc[direction];

            if (nextRow < 0 || nextRow >= rows ||
                nextColumn < 0 || nextColumn >= columns) continue;
            if (grid[nextRow][nextColumn] == '#') continue;

            int candidate = distance[row][column] + 1;
            if (candidate >= distance[nextRow][nextColumn]) continue;

            distance[nextRow][nextColumn] = candidate;
            parent[nextRow][nextColumn] = {row, column};

            int f = candidate + manhattan(nextRow, nextColumn,
                                          goal.first, goal.second);
            open.push({f, candidate, nextRow, nextColumn});
        }
    }

    if (distance[goal.first][goal.second] == INF) return {};

    vector<pair<int, int>> path;
    pair<int, int> current = goal;
    while (current.first != -1) {
        path.push_back(current);
        current = parent[current.first][current.second];
    }
    reverse(path.begin(), path.end());
    return path;
}

int main() {
    vector<string> grid = {
        "S.....#",
        ".##.#..",
        "..#.#.#",
        "..#...#",
        "....##.",
        "#.#....",
        "...#..G"
    };

    pair<int, int> start = {0, 0};
    pair<int, int> goal = {6, 6};

    vector<pair<int, int>> path = aStar(grid, start, goal);

    if (path.empty()) {
        cout << "no path\n";
        return 0;
    }

    cout << "path length: " << path.size() - 1 << " steps\n";
    for (const auto& [row, column] : path) {
        if (grid[row][column] == '.') grid[row][column] = '*';
    }

    for (const string& line : grid) cout << line << '\n';

    return 0;
}
