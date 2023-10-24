// tests.cpp
#include <gtest/gtest.h>

#include "matrix_oop.hpp"

TEST(TestMatrixConstructors, Empty) {
  Matrix A;
  EXPECT_EQ(A.GetRows(), 0);
  EXPECT_EQ(A.GetCols(), 0);
}

TEST(TestMatrixConstructors, TwoArgs1) {
  Matrix A(2, 3);
  EXPECT_EQ(A.GetRows(), 2);
  EXPECT_EQ(A.GetCols(), 3);
}

TEST(TestMatrixConstructors, TwoArgs2) {
  Matrix A(2, 3);
  EXPECT_EQ(A(0, 0), 0);
  EXPECT_EQ(A.GetRows(), 2);
  EXPECT_EQ(A.GetCols(), 3);
}

TEST(TestMatrixConstructors, TwoArgs3) {
  Matrix A(2, 3);
  EXPECT_THROW(A(3, 4), std::invalid_argument);
}

TEST(TestMatrixConstructors, TwoArgsException) {
  EXPECT_THROW(Matrix A(0, 0), std::logic_error);
}

TEST(TestMatrixConstructors, SetValueException) {
  Matrix A;
  EXPECT_THROW(A(0, 0, 0), std::invalid_argument);
}

TEST(TestMatrixConstructors, Copy) {
  Matrix A(4, 3);
  Matrix B = A;
  EXPECT_EQ(B.GetRows(), 4);
  EXPECT_EQ(B.GetCols(), 3);
}

TEST(TestMatrixConstructors, Move) {
  Matrix A(3, 2);
  Matrix B = std::move(A);
  EXPECT_EQ(B.GetRows(), 3);
  EXPECT_EQ(B.GetCols(), 2);
}

TEST(TestMatrixFunctions, EqMatrix1) {
  Matrix A(3, 2);
  Matrix B(3, 2);
  EXPECT_TRUE(A.EqMatrix(B));
}

TEST(TestMatrixFunctions, EqMatrix2) {
  Matrix A(3, 2);
  Matrix B(3, 2);
  B[0][0] = 1;
  EXPECT_FALSE(A.EqMatrix(B));
}

TEST(TestMatrixFunctions, EqMatrix3) {
  Matrix A(3, 2);
  Matrix B(4, 3);
  EXPECT_FALSE(A.EqMatrix(B));
}

TEST(TestMatrixFunctions, Transpose1) {
  Matrix A(2, 3);
  A[0][0] = 1;
  A[1][1] = 2;
  A[0][2] = 3;
  Matrix B;
  B = A.Transpose();
  EXPECT_EQ(B.GetCols(), 2);
  EXPECT_EQ(B.GetRows(), 3);
}

TEST(TestMatrixFunctions, Transpose2) {
  Matrix A(2, 3);
  A[0][0] = 1;
  A[1][1] = 2;
  A[0][2] = 3;
  Matrix B = A;
  B = B.Transpose();
  B = B.Transpose();
  EXPECT_TRUE(A.EqMatrix(B));
}

TEST(TestMatrixFunctions, SumMatrix1) {
  Matrix A(2, 3);
  A[0][0] = 1;
  A[1][1] = 2;
  A[0][2] = 3;
  Matrix B = A;
  A.SumMatrix(B);
  A.SubMatrix(B);
  EXPECT_TRUE(A.EqMatrix(B));
}

TEST(TestMatrixFunctions, SumMatrix2) {
  Matrix A(2, 3);
  A[0][0] = 1;
  A[1][1] = 2;
  A[0][2] = 3;
  Matrix B(3, 2);
  EXPECT_THROW(A.SumMatrix(B), std::logic_error);
}

TEST(TestMatrixFunctions, SubMatrix1) {
  Matrix A(2, 3);
  A[0][0] = 1;
  A[1][1] = 2;
  A[0][2] = 3;
  Matrix B(3, 2);
  EXPECT_THROW(A.SubMatrix(B), std::logic_error);
}

TEST(TestMatrixFunctions, MulMatrix1) {
  Matrix A(2, 3);
  A[0][0] = 1;
  A[1][1] = 2;
  A[0][2] = 3;
  A.MulNumber(2);
  EXPECT_EQ(A[0][0], 2);
  EXPECT_EQ(A[1][1], 4);
  EXPECT_EQ(A[0][2], 6);
}

TEST(TestMatrixFunctions, MulMatrix2) {
  Matrix A(2, 3);
  A[0][0] = 1;
  A[1][1] = 2;
  A[0][2] = 3;
  A.MulNumber(0);
  Matrix B(2, 3);
  EXPECT_TRUE(A.EqMatrix(B));
}

TEST(TestMatrixFunctions, MulMatrix3) {
  Matrix A(3, 2);
  A[0][0] = 1;
  A[0][1] = -1;
  A[1][0] = 4;
  A[1][1] = 2;
  A[2][0] = 3;
  A[2][1] = 5;

  Matrix B(2, 3);
  B[0][0] = 4;
  B[0][1] = -1;
  B[0][2] = 3;
  B[1][0] = 6;
  B[1][1] = 2;
  B[1][2] = -3;

  Matrix C(3, 3);
  C[0][0] = -2;
  C[0][1] = -3;
  C[0][2] = 6;
  C[1][0] = 28;
  C[1][1] = 0;
  C[1][2] = 6;
  C[2][0] = 42;
  C[2][1] = 7;
  C[2][2] = -6;

  A.MulMatrix(B);
  EXPECT_TRUE(A.EqMatrix(C));
}

TEST(TestMatrixFunctions, MulMatrix4) {
  Matrix A(3, 2);
  Matrix B(3, 3);
  EXPECT_THROW(A.MulMatrix(B), std::logic_error);
}

TEST(TestMatrixOperators, Sum) {
  Matrix A(2, 3);
  A[0][0] = 1;
  A[1][1] = 2;
  A[0][2] = 3;
  Matrix B(2, 3);
  B[0][0] = 2;
  B[1][1] = 4;
  B[0][2] = 6;
  Matrix C;
  C = A + A;
  EXPECT_TRUE(C.EqMatrix(B));
}

TEST(TestMatrixOperators, Sub) {
  Matrix A(2, 3);
  A[0][0] = 1;
  A[1][1] = 2;
  A[0][2] = 3;
  Matrix B(2, 3);
  EXPECT_TRUE(B.EqMatrix(A - A));
}

TEST(TestMatrixOperators, Mul1) {
  Matrix A(2, 3);
  A[0][0] = 1;
  A[1][1] = 2;
  A[0][2] = 3;
  Matrix B(2, 3);
  B[0][0] = 2;
  B[1][1] = 4;
  B[0][2] = 6;
  Matrix C;
  C = A * 2;
  EXPECT_TRUE(C.EqMatrix(B));
}

TEST(TestMatrixOperators, Mul2) {
  Matrix A(2, 3);
  A[0][0] = 1;
  A[1][1] = 2;
  A[0][2] = 3;
  Matrix B(2, 3);
  B[0][0] = 2;
  B[1][1] = 4;
  B[0][2] = 6;
  Matrix C;
  C = 2 * A;
  EXPECT_TRUE(C.EqMatrix(B));
}

TEST(TestMatrixOperators, Mul3) {
  Matrix A(3, 2);
  A[0][0] = 1;
  A[0][1] = -1;
  A[1][0] = 4;
  A[1][1] = 2;
  A[2][0] = 3;
  A[2][1] = 5;

  Matrix B(2, 3);
  B[0][0] = 4;
  B[0][1] = -1;
  B[0][2] = 3;
  B[1][0] = 6;
  B[1][1] = 2;
  B[1][2] = -3;

  Matrix C(3, 3);
  C[0][0] = -2;
  C[0][1] = -3;
  C[0][2] = 6;
  C[1][0] = 28;
  C[1][1] = 0;
  C[1][2] = 6;
  C[2][0] = 42;
  C[2][1] = 7;
  C[2][2] = -6;

  Matrix D = A * B;
  EXPECT_TRUE(D.EqMatrix(C));
}

TEST(TestMatrixOperators, Equ1) {
  Matrix A(3, 2);
  Matrix B(3, 2);
  EXPECT_TRUE(A == B);
}

TEST(TestMatrixOperators, Equ2) {
  Matrix A(3, 2);
  Matrix B(2, 3);
  EXPECT_FALSE(A == B);
}

TEST(TestMatrixOperators, Equ3) {
  Matrix A(3, 2);
  A(0, 0) = 1;
  A = A;
  EXPECT_EQ(A[0][0], 1);
}

TEST(TestMatrixOperators, PlusEqual) {
  Matrix A(3, 2);
  A[0][0] = 1;
  A[1][1] = 2;
  A[2][0] = 3;
  A += A;
  EXPECT_TRUE(A.EqMatrix(A));
}

TEST(TestMatrixOperators, MinusEqual) {
  Matrix A(3, 2);
  A[0][0] = 1;
  A[1][1] = 2;
  A[2][0] = 3;
  A -= A;
  EXPECT_TRUE(A.EqMatrix(A));
}

TEST(TestMatrixOperators, MulEqual) {
  Matrix A(3, 2);
  A[0][0] = 1;
  A[1][1] = 2;
  A[2][0] = 3;
  Matrix B;
  B = A * 2;
  A *= 2;
  EXPECT_TRUE(B.EqMatrix(A));
}

TEST(TestMatrixOperators, MulTwoMatrix) {
  Matrix A(3, 2);
  A[0][0] = 1;
  A[1][1] = 2;
  A[2][0] = 3;
  Matrix B(2, 3);
  B[0][0] = 2;
  B[1][1] = 4;
  B[0][2] = 6;
  Matrix C;
  C = A * B;
  EXPECT_TRUE(C.EqMatrix(A * B));
}

TEST(TestMatrixOperators, MulMatrix) {
  Matrix A(3, 2);
  A[0][0] = 1;
  A[1][1] = 2;
  A[2][0] = 3;
  Matrix B(2, 1);
  B[0][0] = 2;
  B[1][0] = 4;
  Matrix C(3, 1);
  C[0][0] = 2;
  C[1][0] = 8;
  C[2][0] = 6;
  A *= B;
  EXPECT_TRUE(A.EqMatrix(C));
}

TEST(TestMatrixOperators, MulMatrix2) {
  Matrix A(3, 2);
  A[0][0] = 1;
  A[1][1] = 2;
  A[2][0] = 3;
  Matrix B(2, 3);
  B[0][0] = 2;
  B[1][1] = 4;
  B[0][2] = 6;
  Matrix C(3, 3);
  C[0][0] = 2;
  C[0][2] = 6;
  C[1][1] = 8;
  C[2][0] = 6;
  C[2][2] = 18;
  A *= B;
  EXPECT_TRUE(A.EqMatrix(C));
}

TEST(TestMatrixFunctions, Determinant) {
  Matrix A(3, 3);
  A[0][0] = 1;
  A[1][1] = 2;
  A[2][2] = 3;
  EXPECT_EQ(A.Determinant(), 6);
}

TEST(TestMatrixFunctions, Determinant2) {
  Matrix A(2, 2);
  A[0][0] = 1;
  A[1][1] = 2;
  EXPECT_EQ(A.Determinant(), 2);
}

TEST(TestMatrixFunctions, Determinant3) {
  Matrix A(1, 1);
  A[0][0] = 1;
  EXPECT_EQ(A.Determinant(), 1);
}

TEST(TestMatrixFunctions, Determinant4) {
  Matrix A(1, 1);
  A[0][0] = 0;
  EXPECT_EQ(A.Determinant(), 0);
}

TEST(TestMatrixFunctions, Determinant5) {
  Matrix A;
  EXPECT_EQ(A.Determinant(), 0);
}

TEST(TestMatrixFunctions, Determinant6) {
  Matrix A(1, 2);
  EXPECT_THROW(A.Determinant(), std::logic_error);
}

TEST(TestMatrixFunctions, Determinant7) {
  Matrix A(3, 3);
  double determinant = 0;
  A(0, 0, 1.0);
  A(0, 1, 2.0);
  A(0, 2, 3.0);
  A(1, 0, 4.0);
  A(1, 1, 5.0);
  A(1, 2, 6.0);
  A(2, 0, 7.0);
  A(2, 1, 8.0);
  A(2, 2, 9.0);
  EXPECT_EQ(A.Determinant(), determinant);
}

TEST(TestMatrixFunctions, CalcComplementsError) {
  Matrix A(2, 3);
  EXPECT_THROW(A.CalcComplements(), std::logic_error);
}

TEST(TestMatrixFunctions, InverseMatrixError) {
  Matrix A(2, 3);
  EXPECT_THROW(A.InverseMatrix(), std::logic_error);
}

TEST(TestMatrixFunctions, CalcComplements) {
  Matrix A(3, 3), B(3, 3), C(3, 3);
  B(0, 0, 1);
  B(0, 1, 2);
  B(0, 2, 3);
  B(1, 0, 0);
  B(1, 1, 4);
  B(1, 2, 2);
  B(2, 0, 5);
  B(2, 1, 2);
  B(2, 2, 1);
  A(0, 0, 0);
  A(0, 1, 10);
  A(0, 2, -20);
  A(1, 0, 4);
  A(1, 1, -14);
  A(1, 2, 8);
  A(2, 0, -8);
  A(2, 1, -2);
  A(2, 2, 4);
  C = B.CalcComplements();
  EXPECT_TRUE(C == A);
}

TEST(TestMatrixFunctions, InverseMatrix) {
  Matrix A(3, 3), B(3, 3), C(3, 3);
  A(0, 0, 2);
  A(0, 1, 5);
  A(0, 2, 7);
  A(1, 0, 6);
  A(1, 1, 3);
  A(1, 2, 4);
  A(2, 0, 5);
  A(2, 1, -2);
  A(2, 2, -3);
  B(0, 0, 1);
  B(0, 1, -1);
  B(0, 2, 1);
  B(1, 0, -38);
  B(1, 1, 41);
  B(1, 2, -34);
  B(2, 0, 27);
  B(2, 1, -29);
  B(2, 2, 24);
  C = A.InverseMatrix();
  EXPECT_TRUE(C == B);
}

TEST(TestMatrixFunctions, InverseMatrix2) {
  Matrix A(1, 1);
  A(0, 0, 0.00000001);
  EXPECT_THROW(A.InverseMatrix(), std::logic_error);
}

TEST(TestMatrixFunctions, CalcComplements2) {
  Matrix A(1, 1), C;
  A(0, 0, 1);
  C = A.CalcComplements();
  EXPECT_TRUE(C == A);
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
