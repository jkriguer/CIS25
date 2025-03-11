#include <iostream>
#include <vector>
#include "util/matrix_utils.h"

void inputMatrix(Matrix);

int main() {
    Matrix matrixA(2, vector<double>(2, 0.0)), matrixB = identityMatrixMult(2);
    printMatrix(matrixA);
    matrixA[0][0] = 10000;
    matrixA[0][1] = 2;
    matrixA[1][0] = 3;
    matrixA[1][1] = 4;
    printMatrix(matrixA);
    printMatrix(matrixMathMult(matrixA, matrixB));
    printMatrix(inverseMatrixAdd(matrixA));
}

void inputMatrix(Matrix mat) {
    std::cout << "Enter " << mat.size() * mat[0].size() << " elements: ";
    for (int j = 0; j < mat.size(); j++) {
        for (int k = 0; k < mat[0].size(); k++) {
            std::cin >> mat[j][k];
        }
    }
}