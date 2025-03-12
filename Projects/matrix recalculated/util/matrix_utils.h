#ifndef matrix_utils
#define matrix_utils
#include <vector>

using std::vector;
using Matrix = vector<vector<double>>;
const Matrix FAIL_MATRIX(0, vector<double>(0)); //invalid 0x0 matrix that returns for catching errors

Matrix identityMatrixAdd(int, int);
Matrix identityMatrixAdd(Matrix);
Matrix identityMatrixMult(int);
Matrix inverseMatrixAdd(Matrix);
Matrix makeMatrix(int, int, vector<double>); //vec must contain x*y elements

Matrix matrixMathAdd(Matrix, Matrix); //both matrices must have same dimensions
Matrix matrixMathSub(Matrix, Matrix); //both matrices must have same dimensions
Matrix matrixMathMult(Matrix, Matrix); //matrix A cols and matrix B rows must be equal

bool isMatrixValid(Matrix);
bool canMatricesAdd(Matrix, Matrix);
bool canMatricesMult(Matrix, Matrix);
#endif