#include <iostream>
#include <string>
#include <vector>

using namespace std;

// ---------------------------------------------------------------------------
// N-Queens (backtracking)
//
// Place one queen per row. When trying a column, reject it if another queen
// already occupies that column or either diagonal. The diagonal tests use the
// fact that all cells on a "/" diagonal have the same row + column, and all
// cells on a "\" diagonal have the same row - column.
//
// Time:  O(n!) worst case
// Space: O(n)
// ---------------------------------------------------------------------------
void solve(int row, int n, vector<int>& columns, vector<bool>& usedColumn,
           vector<bool>& usedSum, vector<bool>& usedDifference,
           vector<vector<int>>& solutions) {
    if (row == n) {
        solutions.push_back(columns);
        return;
    }

    for (int column = 0; column < n; ++column) {
        int sum = row + column;
        int difference = row - column + n - 1;

        if (usedColumn[column] || usedSum[sum] || usedDifference[difference]) {
            continue;
        }

        usedColumn[column] = true;
        usedSum[sum] = true;
        usedDifference[difference] = true;
        columns[row] = column;

        solve(row + 1, n, columns, usedColumn, usedSum, usedDifference, solutions);

        usedColumn[column] = false;
        usedSum[sum] = false;
        usedDifference[difference] = false;
    }
}

vector<vector<int>> nQueens(int n) {
    vector<vector<int>> solutions;
    vector<int> columns(n, -1);
    vector<bool> usedColumn(n, false);
    vector<bool> usedSum(2 * n - 1, false);
    vector<bool> usedDifference(2 * n - 1, false);

    solve(0, n, columns, usedColumn, usedSum, usedDifference, solutions);
    return solutions;
}

void printBoard(const vector<int>& columns) {
    int n = static_cast<int>(columns.size());
    for (int row = 0; row < n; ++row) {
        for (int column = 0; column < n; ++column) {
            cout << (columns[row] == column ? "Q " : ". ");
        }
        cout << '\n';
    }
}

int main() {
    for (int n : {4, 8}) {
        vector<vector<int>> solutions = nQueens(n);
        cout << n << "-Queens: " << solutions.size() << " solutions\n";

        if (!solutions.empty()) {
            cout << "first solution:\n";
            printBoard(solutions.front());
        }
        cout << '\n';
    }

    return 0;
}
