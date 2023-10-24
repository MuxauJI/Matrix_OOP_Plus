#include "matrix_oop.hpp"

int main() {
  using namespace std;
  Matrix A(3, 3);
  A(0, 0) = 1;
  cout << A;
  A = A;
  cout << A;

  return 0;
}