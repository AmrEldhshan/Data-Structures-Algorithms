#include <iostream>
#include <string>
#include <vector>

using namespace std;

// ---------------------------------------------------------------------------
// Rat in a maze (backtracking)
//
// 1 = open cell, 0 = wall. Move right or down, mark the current cell, recurse,
// then unmark it if the branch fails. Printing the successful path shows how
// backtracking explores and then abandons dead ends.
//
// Time:  O(2^(rows + columns)) worst case for two directions
// Space: O(rows * columns)
// ---------------------------------------------------------------------------
bool findPath(vector<vector<int>>& maze, int row, int column,
              vector<vector<bool>>& visited, vector<pair<int, int>>& path) {
    int rows = static_cast<int>(maze.size());
    int columns = static_cast<int>(maze[0].size());

    if (row < 0 || row >= rows || column < 0 || column >= columns) return false;
    if (maze[row][column] == 0 || visited[row][column]) return false;

    visited[row][column] = true;
    path.push_back({row, column});

    if (row == rows - 1 && column == columns - 1) return true;

    if (findPath(maze, row + 1, column, visited, path)) return true; // down
    if (findPath(maze, row, column + 1, visited, path)) return true; // right

    // Backtrack: this cell is not on the solution path.
    path.pop_back();
    visited[row][column] = false;
    return false;
}

int main() {
    vector<vector<int>> maze = {
        {1, 0, 0, 0, 0},
        {1, 1, 0, 1, 0},
        {0, 1, 0, 1, 0},
        {0, 1, 1, 1, 0},
        {0, 0, 0, 1, 1}
    };

    vector<vector<bool>> visited(maze.size(), vector<bool>(maze[0].size(), false));
    vector<pair<int, int>> path;

    if (findPath(maze, 0, 0, visited, path)) {
        cout << "path found:\n";
        for (const auto& [row, column] : path) {
            cout << "  (" << row << ", " << column << ")\n";
        }

        cout << "\nmaze with path marked by *:\n";
        vector<string> drawing;
        for (const auto& row : maze) {
            string line;
            for (int cell : row) line += (cell == 0 ? '#' : '.');
            drawing.push_back(line);
        }
        for (const auto& [row, column] : path) drawing[row][column] = '*';

        for (const string& line : drawing) cout << line << '\n';
    } else {
        cout << "no path\n";
    }

    return 0;
}
