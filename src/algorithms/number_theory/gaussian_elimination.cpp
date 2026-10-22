#include <cmath>
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <utility>
#include <vector>

using namespace std;

// ---------------------------------------------------------------------------
// Gaussian elimination (solve Ax = b)
//
// Forward elimination turns the matrix into row-echelon form using partial
// pivoting (choose the largest pivot in the column). Back substitution then
// recovers the unknowns. If a pivot is zero, the system is singular.
//
// Time:  O(n^3)
// Space: O(n^2)
// ---------------------------------------------------------------------------
const double EPSILON = 1e-9;

vector<double> solveLinearSystem(vector<vector<double>> matrix,
                                 vector<double> rhs) {
    int n = static_cast<int>(matrix.size());

    for (int column = 0; column < n; ++column) {
        int pivot = column;
        for (int row = column + 1; row < n; ++row) {
            if (fabs(matrix[row][column]) > fabs(matrix[pivot][column])) {
                pivot = row;
            }
        }

        if (fabs(matrix[pivot][column]) < EPSILON) {
            throw runtime_error("Gaussian elimination: singular matrix");
        }

        swap(matrix[pivot], matrix[column]);
        swap(rhs[pivot], rhs[column]);

        for (int row = column + 1; row < n; ++row) {
            double factor = matrix[row][column] / matrix[column][column];

            for (int k = column; k < n; ++k) {
                matrix[row][k] -= factor * matrix[column][k];
            }
            rhs[row] -= factor * rhs[column];
        }
    }

    // Back substitution.
    vector<double> solution(n, 0.0);
    for (int row = n - 1; row >= 0; --row) {
        double sum = rhs[row];
        for (int column = row + 1; column < n; ++column) {
            sum -= matrix[row][column] * solution[column];
        }
        solution[row] = sum / matrix[row][row];
    }

    return solution;
}

int main() {
    // 2x +  y -  z =  8
    // -3x - y + 2z = -11
    // -2x + y + 2z = -3
    vector<vector<double>> matrix = {
        {2, 1, -1},
        {-3, -1, 2},
        {-2, 1, 2}
    };
    vector<double> rhs = {8, -11, -3};

    vector<double> solution = solveLinearSystem(matrix, rhs);

    cout << "solution: ";
    for (double value : solution) {
        cout << fixed << setprecision(4) << value << ' ';
    }
    cout << "\n(expected: 2 3 -1)\n";

    return 0;
}
