#include <iostream>
#include "util/matrix_utils.h"

void inputMatrix(Matrix&);

int main() {
    Matrix matrixA(2, vector<double>(2, 0.0)), matrixB = identityMatrixMult(2);
    printMatrix(matrixA);
    matrixA[0][0] = 10000;
    matrixA[0][1] = 2;
    matrixA[1][0] = 3;
    matrixA[1][1] = 4;
    printMatrix(matrixA);
    printMatrix(matrixMathMult(matrixA, matrixB));
    inputMatrix(matrixA);
    printMatrix(matrixMathMult(matrixA, matrixB));
}

void inputMatrix(Matrix& mat) {
    vector<double> in(mat.size() * mat[0].size());
    std::cout << "Enter " << in.size() << " elements: ";
    for (int i = 0; i < in.size(); i++) {
        std::cin >> in[i];
    }
    mat = makeMatrix(mat.size(), mat[0].size(), in);
}