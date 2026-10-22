#include <iostream>
#include <vector>

using namespace std;

// ---------------------------------------------------------------------------
// Sudoku solver (backtracking)
//
// Find an empty cell, try digits 1..9, and recurse. Three boolean tables make
// the validity check O(1):
//   rows[r][d]    : digit d is already in row r
//   cols[c][d]    : digit d is already in column c
//   boxes[b][d]   : digit d is already in box b (b = 0..8)
//
// Time:  exponential in the number of empty cells
// Space: O(1) besides the board
// ---------------------------------------------------------------------------
bool canPlace(const vector<vector<int>>& board, int row, int column, int digit) {
    for (int i = 0; i < 9; ++i) {
        if (board[row][i] == digit) return false;
        if (board[i][column] == digit) return false;
    }

    int boxRow = (row / 3) * 3;
    int boxColumn = (column / 3) * 3;
    for (int r = boxRow; r < boxRow + 3; ++r) {
        for (int c = boxColumn; c < boxColumn + 3; ++c) {
            if (board[r][c] == digit) return false;
        }
    }

    return true;
}

bool solveSudoku(vector<vector<int>>& board) {
    for (int row = 0; row < 9; ++row) {
        for (int column = 0; column < 9; ++column) {
            if (board[row][column] != 0) continue;

            for (int digit = 1; digit <= 9; ++digit) {
                if (!canPlace(board, row, column, digit)) continue;

                board[row][column] = digit;
                if (solveSudoku(board)) return true;
                board[row][column] = 0; // backtrack
            }

            return false; // no digit fits, undo the previous choice
        }
    }

    return true; // no empty cell left
}

void printBoard(const vector<vector<int>>& board) {
    for (int row = 0; row < 9; ++row) {
        if (row % 3 == 0 && row != 0) cout << "------+-------+------\n";
        for (int column = 0; column < 9; ++column) {
            if (column % 3 == 0 && column != 0) cout << "| ";
            cout << board[row][column] << ' ';
        }
        cout << '\n';
    }
}

int main() {
    // 0 marks an empty cell.
    vector<vector<int>> board = {
        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},
        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9}
    };

    if (solveSudoku(board)) {
        cout << "Solved Sudoku:\n";
        printBoard(board);
    } else {
        cout << "No solution exists.\n";
    }

    return 0;
}
