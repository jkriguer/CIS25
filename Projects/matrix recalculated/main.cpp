#include <iostream>
#include "util/matrix_utils.h"
#include "util/matrix_console.h" //functions used for console output until GUI library chosen

int main() {
    using std::cout;
    Matrix matrixA(identityMatrixAdd(2, 2)), matrixB = identityMatrixMult(2);
    cout << "Debug: Blank 2x2 Matrix\n";
    printMatrix(matrixA);
    srand(time(nullptr)); //seed PRNG
    for (auto& col : matrixA) {
        for (double val : col) {
            val = rand() % 100;
        }
    }
    cout << "Debug: Modified 2x2 Matrix";
    printMatrix(matrixA);
    printMatrix(matrixMathMult(matrixA, matrixB));
    inputMatrix(matrixA);
    printMatrix(matrixMathMult(matrixA, matrixB));
}
