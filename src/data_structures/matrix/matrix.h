#ifndef DSA_MATRIX_H
#define DSA_MATRIX_H

#include <ostream>
#include <stdexcept>
#include <vector>

// ---------------------------------------------------------------------------
// Matrix
//
// A small dense matrix stored in row-major order. Supports element access,
// addition, multiplication, transpose, and the identity matrix.
//
// Multiplication is O(n^3) for n x n matrices; a better algorithm would use
// Strassen or blocking, but this version is meant to be readable.
// ---------------------------------------------------------------------------
template <typename T>
class Matrix {
public:
    Matrix(int rows, int columns, T value = T{})
        : rows_(rows), columns_(columns),
          data_(checkedSize(rows, columns), value) {}

    static Matrix identity(int size) {
        Matrix result(size, size, T{});
        for (int i = 0; i < size; ++i) result(i, i) = T{1};
        return result;
    }

    int rows() const { return rows_; }
    int columns() const { return columns_; }

    T& operator()(int row, int column) {
        check(row, column);
        return data_[index(row, column)];
    }

    const T& operator()(int row, int column) const {
        check(row, column);
        return data_[index(row, column)];
    }

    Matrix operator+(const Matrix& other) const {
        if (rows_ != other.rows_ || columns_ != other.columns_) {
            throw std::invalid_argument("Matrix: size mismatch in addition");
        }

        Matrix result(rows_, columns_);
        for (std::size_t i = 0; i < data_.size(); ++i) {
            result.data_[i] = data_[i] + other.data_[i];
        }
        return result;
    }

    Matrix operator*(const Matrix& other) const {
        if (columns_ != other.rows_) {
            throw std::invalid_argument("Matrix: size mismatch in multiplication");
        }

        Matrix result(rows_, other.columns_, T{});
        for (int row = 0; row < rows_; ++row) {
            for (int middle = 0; middle < columns_; ++middle) {
                T value = (*this)(row, middle);
                for (int column = 0; column < other.columns_; ++column) {
                    result(row, column) += value * other(middle, column);
                }
            }
        }
        return result;
    }

    Matrix transpose() const {
        Matrix result(columns_, rows_);
        for (int row = 0; row < rows_; ++row) {
            for (int column = 0; column < columns_; ++column) {
                result(column, row) = (*this)(row, column);
            }
        }
        return result;
    }

    bool operator==(const Matrix& other) const {
        return rows_ == other.rows_ && columns_ == other.columns_ &&
               data_ == other.data_;
    }

    void print(std::ostream& out) const {
        for (int row = 0; row < rows_; ++row) {
            for (int column = 0; column < columns_; ++column) {
                if (column != 0) out << ' ';
                out << (*this)(row, column);
            }
            out << '\n';
        }
    }

private:
    static std::size_t checkedSize(int rows, int columns) {
        if (rows <= 0 || columns <= 0) {
            throw std::invalid_argument("Matrix: dimensions must be positive");
        }
        return static_cast<std::size_t>(rows) * columns;
    }

    std::size_t index(int row, int column) const {
        return static_cast<std::size_t>(row) * columns_ + column;
    }

    void check(int row, int column) const {
        if (row < 0 || row >= rows_ || column < 0 || column >= columns_) {
            throw std::out_of_range("Matrix: index out of range");
        }
    }

    int rows_;
    int columns_;
    std::vector<T> data_;
};

template <typename T>
std::ostream& operator<<(std::ostream& out, const Matrix<T>& matrix) {
    matrix.print(out);
    return out;
}

#endif // DSA_MATRIX_H
