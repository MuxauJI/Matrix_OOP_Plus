#ifndef SRC__MATRIX_OOP_H_
#define SRC__MATRIX_OOP_H_

#define _EPSILON 1e-7
// #define DEBUG 0
// #define ALLOC_METHOD 1
#include <cmath>
#include <exception>
#include <iostream>

class Matrix {
 private:
  int rows_, cols_;
  double** matrix_;
  void AllocateMemory();
  void FreeMemory();
  double& GetValue(int row, int col);
  void SetValue(int row, int col, double val);

 public:
  Matrix();
  Matrix(int rows, int cols);
  Matrix(const Matrix& other);
  Matrix(Matrix&& other);
  ~Matrix();
  int GetCols() const;
  int GetRows() const;
  double& operator()(int row, int col);
  void operator()(int row, int col, double val);
  double* operator[](int row);
  Matrix& operator=(const Matrix& other);
  Matrix& operator+=(const Matrix& other);
  Matrix& operator-=(const Matrix& other);
  Matrix& operator*=(const Matrix& other);
  Matrix& operator*=(const double num);
  Matrix operator+(const Matrix& other);
  Matrix operator-(const Matrix& other);
  Matrix operator*(const Matrix& other);
  Matrix operator*(const double num);
  friend Matrix operator*(const double num, const Matrix& other);
  bool operator==(const Matrix& other);
  friend std::ostream& operator<<(std::ostream& out, const Matrix& other);
  bool EqMatrix(const Matrix& other);
  void SumMatrix(const Matrix& other);
  void SubMatrix(const Matrix& other);
  void MulNumber(const double num);
  void MulMatrix(const Matrix& other);
  Matrix GetMinorMatrix(int row, int col);
  double GetDeterminant();
  double Determinant();
  Matrix CalcComplements();
  Matrix InverseMatrix();
  Matrix Transpose();
};

#endif  // SRC__MATRIX_OOP_H_
