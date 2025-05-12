#pragma once

class Matrix {
  private:
    int rows;
    int cols;
    double** data;

    void allocateMemory();
    void deallocateMemory();
    
  public:
    Matrix(int n);                              
    Matrix(int m, int n, double fill = 0);   
    Matrix(const Matrix& other);                
    ~Matrix();                                  

    double get(int i, int j) const;
    void set(int i, int j, double value);
    int get_height() const { return rows; }
    int get_width() const { return cols; }

    void negate();
    void add_in_place(const Matrix& other);
    void copy(const Matrix& other);
    Matrix multiply(const Matrix& other) const;

    void print() const;

    Matrix& operator=(const Matrix& other);

    Matrix& operator+=(const Matrix& other);
    Matrix& operator-=(const Matrix& other);
    Matrix& operator*=(double scalar);
    Matrix& operator/=(double scalar);

    Matrix operator+(const Matrix& other) const;
    Matrix operator-(const Matrix& other) const;
    Matrix operator*(const Matrix& other) const;

    Matrix operator*(double scalar) const;
    Matrix operator/(double scalar) const;

    friend Matrix operator*(double scalar, const Matrix& mat);
    friend Matrix operator-(const Matrix& mat);

    Matrix(Matrix&& other) noexcept;
    Matrix& operator=(Matrix&& other) noexcept;
};
