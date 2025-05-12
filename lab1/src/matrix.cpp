#include "matrix.hpp"
#include <iostream>
#include <stdexcept>

void Matrix::allocateMemory() {
    data = new double*[rows];
    for (int i = 0; i < rows; ++i) {
        data[i] = new double[cols];
    }
}

void Matrix::deallocateMemory() {
    for (int i = 0; i < rows; ++i) {
        delete[] data[i];
    }
    delete[] data;
}

Matrix::Matrix(int n) : rows(n), cols(n) {
    allocateMemory();
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            data[i][j] = (i == j) ? 1 : 0;
        }
    }
}

Matrix::Matrix(int m, int n, double fill) : rows(m), cols(n) {
    allocateMemory();
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            data[i][j] = fill;
        }
    }
}

Matrix::Matrix(const Matrix& other) : rows(other.rows), cols(other.cols) {
    allocateMemory();
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            data[i][j] = other.data[i][j];
        }
    }
}

Matrix::~Matrix() {
    deallocateMemory();
}

void Matrix::copy(const Matrix& other) {
    if (rows != other.rows || cols != other.cols) {
        return;
    }
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            data[i][j] = other.data[i][j];
        }
    }

}

double Matrix::get(int i, int j) const {
    return data[i][j];
}

void Matrix::set(int i, int j, double value) {
    data[i][j] = value;
}

void Matrix::negate() {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            data[i][j] = -data[i][j];
        }
    }
}

void Matrix::add_in_place(const Matrix& other) {
    if (rows != other.rows || cols != other.cols) {
        throw std::invalid_argument("Matrix dimensions mismatch");
    }
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            data[i][j] += other.data[i][j];
        }
    }
}

Matrix Matrix::multiply(const Matrix& other) const {
    if (cols != other.rows) {
        throw std::invalid_argument("Matrix dimensions mismatch");
    }
    Matrix result(rows, other.cols, 0);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < other.cols; ++j) {
            for (int k = 0; k < cols; ++k) {
                result.data[i][j] += data[i][k] * other.data[k][j];
            }
        }
    }
    return result;
}