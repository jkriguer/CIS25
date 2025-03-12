#include <iostream>
#include "util/matrix_utils.h" //functions for matrix logic and arithmetic
#include "util/matrix_console.h" //functions used for console output until GUI library chosen
#include "util/matrix_io.h" //functions used for loading/saving matrices as .csv
int main() {
    using std::cout;
    Matrix matrixA(identityMatrixAdd(2, 2)), matrixB = identityMatrixMult(2);
    cout << "Debug: Blank 2x2 Matrix\n";
    printMatrix(matrixA);
    srand(time(nullptr)); //seed PRNG
    for (auto& rows : matrixA) {
        for (double val : rows) {
            val = rand() % 100;
        }
    }
    cout << "Debug: Modified 2x2 Matrix\n";
    printMatrix(matrixA);
    cout << "Debug: identity of previous matrix (should be unchanged)\n";
    printMatrix(matrixMathMult(matrixA, matrixB));
    inputMatrix(matrixA);
    cout << "Debug: identity of previous matrix (should be unchanged)\n";
    printMatrix(matrixMathMult(matrixA, matrixB));
}
