#include "data_structures/matrix/matrix.h"

#include <iostream>

using namespace std;

int main() {
    Matrix<int> a(2, 3, 0);
    a(0, 0) = 1; a(0, 1) = 2; a(0, 2) = 3;
    a(1, 0) = 4; a(1, 1) = 5; a(1, 2) = 6;

    Matrix<int> b(3, 2, 0);
    b(0, 0) = 7; b(0, 1) = 8;
    b(1, 0) = 9; b(1, 1) = 10;
    b(2, 0) = 11; b(2, 1) = 12;

    cout << "A =\n" << a;
    cout << "B =\n" << b;
    cout << "A * B =\n" << a * b;
    cout << "transpose(A) =\n" << a.transpose();

    Matrix<int> identity = Matrix<int>::identity(3);
    cout << "identity(3) =\n" << identity;

    Matrix<int> sum = a + Matrix<int>(2, 3, 1);
    cout << "A + all-ones =\n" << sum;

    return 0;
}
