#include "matrix.hpp"
#include <iostream>
#include <stdexcept>
#include <iomanip>

using namespace std;

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
        throw invalid_argument("Matrix dimensions mismatch");
    }
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            data[i][j] += other.data[i][j];
        }
    }
}

Matrix Matrix::multiply(const Matrix& other) const {
    if (cols != other.rows) {
        throw invalid_argument("Matrix dimensions mismatch");
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

void Matrix::print() const {
  cout << "Matrix (" << rows << " x " << cols << "):\n";
  for (int i = 0; i < rows; ++i) {
    cout << "| ";
    for (int j = 0; j < cols; ++j) {
      cout << setw(8) << fixed << setprecision(2) << data[i][j] << ' ';
    }
    cout << "|\n";
  }
}

Matrix& Matrix::operator=(const Matrix& other) {
  if (this != &other) {
    deallocateMemory();

    rows = other.rows;
    cols = other.cols;

    allocateMemory();

    for (int i = 0; i < rows; ++i) {
      for (int j = 0; j < cols; ++j) {
        data[i][j] = other.data[i][j];
      }
    }
  }
  return *this;
}

Matrix& Matrix::operator+=(const Matrix& other) {
  if (rows != other.rows || cols != other.cols) {
    throw invalid_argument("Matrix +=: size mismatch");
  }

  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      data[i][j] += other.data[i][j];
    }
  }

  return *this;
}

Matrix& Matrix::operator-=(const Matrix& other) {
  if (rows != other.rows || cols != other.cols) {
    throw invalid_argument("Matrix -=: size mismatch");
  }

  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      data[i][j] -= other.data[i][j];
    }
  }

  return *this;
}

Matrix& Matrix::operator*=(double scalar) {
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      data[i][j] *= scalar;
    }
  }
  return *this;
}

Matrix& Matrix::operator/=(double scalar) {
  if (scalar == 0) {
    throw invalid_argument("Matrix /=: division by zero");
  }

  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      data[i][j] /= scalar;
    }
  }
  return *this;
}


Matrix Matrix::operator+(const Matrix& other) const {
  if (rows != other.rows || cols != other.cols) {
    throw std::invalid_argument("Matrix +: size mismatch");
  }

  Matrix result(rows, cols);
  for (int i = 0; i < rows; ++i)
    for (int j = 0; j < cols; ++j)
      result.data[i][j] = data[i][j] + other.data[i][j];

  return result;
}

Matrix Matrix::operator-(const Matrix& other) const {
  if (rows != other.rows || cols != other.cols) {
    throw std::invalid_argument("Matrix -: size mismatch");
  }

  Matrix result(rows, cols);
  for (int i = 0; i < rows; ++i)
    for (int j = 0; j < cols; ++j)
      result.data[i][j] = data[i][j] - other.data[i][j];

  return result;
}

Matrix Matrix::operator*(const Matrix& other) const {
  if (cols != other.rows) {
    throw std::invalid_argument("Matrix *: incompatible dimensions");
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

Matrix Matrix::operator*(double scalar) const {
  Matrix result(rows, cols);
  for (int i = 0; i < rows; ++i)
    for (int j = 0; j < cols; ++j)
      result.data[i][j] = data[i][j] * scalar;

  return result;
}

Matrix Matrix::operator/(double scalar) const {
  if (scalar == 0.0) {
    throw std::invalid_argument("Matrix /: division by zero");
  }

  Matrix result(rows, cols);
  for (int i = 0; i < rows; ++i)
    for (int j = 0; j < cols; ++j)
      result.data[i][j] = data[i][j] / scalar;

  return result;
}

Matrix operator*(double scalar, const Matrix& mat) {
  return mat * scalar;
}

Matrix operator-(const Matrix& mat) {
  Matrix result(mat.get_height(), mat.get_width());
  for (int i = 0; i < mat.get_height(); ++i) {
    for (int j = 0; j < mat.get_width(); ++j) {
      result.set(i, j, -mat.get(i, j));
    }
  }
  return result;
}

Matrix::Matrix(Matrix&& other) noexcept {
  rows = other.rows;
  cols = other.cols;
  data = other.data;

  other.rows = 0;
  other.cols = 0;
  other.data = nullptr;
}

Matrix& Matrix::operator=(Matrix&& other) noexcept {
  if (this != &other) {
    deallocateMemory();

    rows = other.rows;
    cols = other.cols;
    data = other.data;

    other.rows = 0;
    other.cols = 0;
    other.data = nullptr;
  }
  return *this;
}
