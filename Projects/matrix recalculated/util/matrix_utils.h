#ifndef matrix_utils
#define matrix_utils

#include <vector>
using Matrix = std::vector<std::vector<double>>;

Matrix blankMatrix(int, int, double = 0.0);
Matrix identityMatrix(int);
Matrix matrixMathAdd(Matrix, Matrix); //both matrices must have same dimensions
Matrix matrixMathSub(Matrix, Matrix); //both matrices must have same dimensions
Matrix matrixMathMult(Matrix, Matrix); //matrix A cols and matrix B rows must be equal

bool isMatrixValid(Matrix);
bool canMatricesAdd(Matrix, Matrix);
bool canMatricesMult(Matrix, Matrix);

#endif