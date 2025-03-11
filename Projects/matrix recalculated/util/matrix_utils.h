#ifndef matrix_utils
#define matrix_utils
#include <vector>
#include <algorithm>

using std::vector;
using Matrix = vector<vector<double>>;

Matrix identityMatrixAdd(Matrix);
Matrix identityMatrixMult(int);
Matrix inverseMatrixAdd(Matrix);
Matrix matrixMathAdd(Matrix, Matrix); //both matrices must have same dimensions
Matrix matrixMathSub(Matrix, Matrix); //both matrices must have same dimensions
Matrix matrixMathMult(Matrix, Matrix); //matrix A cols and matrix B rows must be equal

Matrix makeMatrix(int, int, vector<double>); //vec must contain x*y elements
bool isMatrixValid(Matrix);
bool canMatricesAdd(Matrix, Matrix);
bool canMatricesMult(Matrix, Matrix);

#endif