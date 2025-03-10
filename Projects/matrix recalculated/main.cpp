#include <iostream>
#include <vector>
#include <iomanip>
#include <string>
#include "util/matrix_utils.h"

using namespace std;
void inputMatrix(Matrix);
void printMatrix(Matrix);

int main() {
    using Matrix = std::vector<std::vector<double>>;
    Matrix matrixA = blankMatrix(2, 2), matrixB = identityMatrixMult(2);
    printMatrix(matrixA);
    matrixA[0][0] = 1;
    matrixA[0][1] = 2;
    matrixA[1][0] = 3;
    matrixA[1][1] = 4;
    printMatrix(matrixA);
    printMatrix(matrixMathMult(matrixA, matrixB));
    printMatrix(inverseMatrixAdd(matrixA));
}

void printMatrix(Matrix mat) {
    cout << "Matrix (" << mat.size() << " rows, " << mat[0].size() << " cols)\n";
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            cout << setw(5) << mat[i][j];
        }
        cout << '\n';
    }
}

void inputMatrix(Matrix mat) {
    cout << "Enter " << mat.size() * mat[0].size() << " elements: ";
    for (int j = 0; j < mat.size(); j++) {
        for (int k = 0; k < mat[0].size(); k++) {
            cin >> mat[j][k];
        }
    }
}