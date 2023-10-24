#include "matrix_oop.hpp"

Matrix::Matrix() {
  rows_ = 0;
  cols_ = 0;
  matrix_ = nullptr;
}

void Matrix::AllocateMemory() {
#if ALLOC_METHOD == 1
  //  выделение памяти двумя операциями new
  matrix_ = new double*[rows_]();
  matrix_[0] = new double[rows_ * cols_]();
  for (int i = 1; i != rows_; i++) {
    matrix_[i] = matrix_[i - 1] + cols_;
  }
#else
  //  выделение памяти (n+1) раз
  matrix_ = new double*[rows_]();
  for (int i = 0; i < rows_; i++) {
    matrix_[i] = new double[cols_]();
  }
#endif  // ALLOC_METHOD
}

void Matrix::FreeMemory() {
#if ALLOC_METHOD == 1
  if (matrix_ && matrix_[0]) {
    delete[] matrix_[0];
    delete[] matrix_;
  }
#else
  for (int i = 0; i < rows_; i++) {
    if (matrix_[i]) delete[] matrix_[i];
  }
  if (matrix_) delete[] matrix_;
#endif  // ALLOC_METHOD
}

Matrix::Matrix(int rows, int cols) {
  if (rows < 1 || cols < 1) {
    throw std::logic_error("Invalid matrix size");
  }
  rows_ = rows;
  cols_ = cols;
  AllocateMemory();
}

Matrix::Matrix(const Matrix& other) {
  rows_ = other.rows_;
  cols_ = other.cols_;
  AllocateMemory();
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = other.matrix_[i][j];
    }
  }
}

Matrix::Matrix(Matrix&& other) {
  matrix_ = other.matrix_;
  rows_ = other.rows_;
  cols_ = other.cols_;
  other.matrix_ = nullptr;
  other.cols_ = 0;
  other.rows_ = 0;
}

Matrix::~Matrix() {
  FreeMemory();
  matrix_ = nullptr;
  rows_ = 0;
  cols_ = 0;
}

int Matrix::GetCols() const { return cols_; }

int Matrix::GetRows() const { return rows_; }

double& Matrix::GetValue(int row, int col) {
  if (row >= rows_ || col >= cols_ || row < 0 || col < 0)
    throw std::invalid_argument("Wrong get value of rows/columns");
  return matrix_[row][col];
}

void Matrix::SetValue(int row, int col, double val) {
  if (row >= rows_ || col >= cols_)
    throw std::invalid_argument("Wrong set value of rows/columns");
  matrix_[row][col] = val;
}

double* Matrix::operator[](int i) {
  if (i >= rows_ || i < 0) throw std::invalid_argument("Wrong value of row");
  return matrix_[i];
}

double& Matrix::operator()(int row, int col) { return GetValue(row, col); }

void Matrix::operator()(int row, int col, double val) {
  return SetValue(row, col, val);
}

Matrix& Matrix::operator=(const Matrix& other) {
  if (this != &other) {
    FreeMemory();
    rows_ = other.rows_;
    cols_ = other.cols_;
    AllocateMemory();
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < cols_; j++) {
        matrix_[i][j] = other.matrix_[i][j];
      }
    }
  }
  return *this;
}

Matrix& Matrix::operator+=(const Matrix& other) {
  SumMatrix(other);
  return *this;
}

Matrix& Matrix::operator-=(const Matrix& other) {
  SubMatrix(other);
  return *this;
}

Matrix& Matrix::operator*=(const Matrix& other) {
  MulMatrix(other);
  return *this;
}

Matrix& Matrix::operator*=(const double num) {
  MulNumber(num);
  return *this;
}

Matrix Matrix::operator+(const Matrix& other) {
  Matrix result = *this;
  result.SumMatrix(other);
  return result;
}

Matrix Matrix::operator-(const Matrix& other) {
  Matrix result = *this;
  result.SubMatrix(other);
  return result;
}

Matrix Matrix::operator*(const Matrix& other) {
  Matrix result = *this;
  result.MulMatrix(other);
  return result;
}

Matrix Matrix::operator*(const double num) {
  Matrix result = *this;
  result.MulNumber(num);
  return result;
}

Matrix operator*(const double num, const Matrix& other) {
  Matrix result = other;
  result.MulNumber(num);
  return result;
}

bool Matrix::operator==(const Matrix& other) { return EqMatrix(other); }

Matrix Matrix::Transpose() {
  Matrix result(GetCols(), GetRows());
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      result[j][i] = matrix_[i][j];
    }
  }
  return result;
}

bool Matrix::EqMatrix(const Matrix& other) {
  if (other.rows_ != rows_ || other.cols_ != cols_) {
    return false;
  }

  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      double res = matrix_[i][j] - other.matrix_[i][j];
      if (std::fabs(res) >= _EPSILON) {
        return false;
      }
    }
  }
  return true;
}

void Matrix::SumMatrix(const Matrix& other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::logic_error("Different matrix size");
  }

  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] += other.matrix_[i][j];
    }
  }
}

void Matrix::SubMatrix(const Matrix& other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::logic_error("Different matrix size");
  }

  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] -= other.matrix_[i][j];
    }
  }
}

void Matrix::MulNumber(const double num) {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] *= num;
    }
  }
}

void Matrix::MulMatrix(const Matrix& other) {
  if (cols_ != other.rows_) {
    throw std::logic_error("Matrix not matched!");
  }

  Matrix result(rows_, other.cols_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < other.cols_; j++) {
      for (int k = 0; k < cols_; k++) {
        result.matrix_[i][j] += matrix_[i][k] * other.matrix_[k][j];
      }
    }
  }
  *this = Matrix(std::move(result));
}

double Matrix::GetDeterminant() {
  double determinant = 0.0;

  if (rows_ == 1) {
    return matrix_[0][0];
  } else {
    for (int i = 0; i < rows_; i++) {
      Matrix minor_matrix = GetMinorMatrix(0, i);
      if (i % 2 == 0) {
        determinant += matrix_[0][i] * minor_matrix.GetDeterminant();
      } else {
        determinant -= matrix_[0][i] * minor_matrix.GetDeterminant();
      }
    }
  }

  return determinant;
}

Matrix Matrix::GetMinorMatrix(int row, int col) {
  Matrix result{rows_ - 1, cols_ - 1};
  int p_i = 0, p_j = 0;
  for (int i = 0; i < result.GetRows(); i++) {
    if (i == row) p_i = 1;
    p_j = 0;
    for (int j = 0; j < result.GetCols(); j++) {
      if (j == col) p_j = 1;
      result.matrix_[i][j] = matrix_[i + p_i][j + p_j];
    }
  }
  return result;
}

double Matrix::Determinant() {
  if (rows_ != cols_) {
    throw std::logic_error("Matrix not square!");
  }
  return GetDeterminant();
}

Matrix Matrix::CalcComplements() {
  if (rows_ != cols_) {
    throw std::logic_error("Matrix not square!");
  }

  Matrix result{rows_, cols_};

  if (rows_ == 1) {
    result.matrix_[0][0] = matrix_[0][0];
  } else {
    for (int i = 0; i < result.GetRows(); ++i) {
      for (int j = 0; j < result.GetCols(); ++j) {
        Matrix minor_matrix = GetMinorMatrix(i, j);
        double det = minor_matrix.GetDeterminant();
        if ((i + j) % 2 != 0) det *= -1;
        result(i, j) = det;
      }
    }
  }

  return result;
}

Matrix Matrix::InverseMatrix() {
  if (rows_ != cols_) {
    throw std::logic_error("Matrix not square!");
  }

  double det = Determinant();

  if (std::fabs(det) < _EPSILON) {
    throw std::logic_error("Cant inverse matrix!");
  }

  return Transpose().CalcComplements() * (1.0 / det);
}

#ifdef DEBUG
std::ostream& operator<<(std::ostream& out, const Matrix& other) {
  for (int i = 0; i < other.rows_; i++) {
    for (int j = 0; j < other.cols_; j++) {
      out << other.matrix_[i][j] << " ";
    }
    out << std::endl;
  }
  out << std::endl;
  return out;
}
#endif  // DEBUG
