#include <iostream>
#include "util/matrix_utils.h" //functions for matrix logic and arithmetic
#include "util/matrix_console.h" //functions used for console output until GUI library chosen
#include "util/matrix_io.h" //functions used for loading/saving matrices as .csv
int main() {
    using std::cout;
    Matrix matrixA(identityMatrixAdd(4, 4)), matrixB(identityMatrixMult(4));
    cout << "Debug: Blank 4x4 Matrix\n";
    printMatrix(matrixA);
    srand(time(nullptr)); //seed PRNG
    for (auto& rows : matrixA) { //randomly fill matrix
        for (double& val : rows) {
            val = rand() % 100;
        }
    }
    cout << "Debug: Modified 4x4 Matrix\n";
    printMatrix(matrixA);
    cout << "Debug: identity of previous matrix (should be unchanged)\n";
    printMatrix(matrixMathMult(matrixA, matrixB));
    //inputMatrix(matrixA);
    //cout << "Debug: identity of input matrix (should be unchanged from input)\n";
    //printMatrix(matrixMathMult(matrixA, matrixB));
    //cout << "Enter a filename to save this matrix as: ";
    //std::string input;
    //std::cin >> input;
    saveMatrix(matrixA, "MyMatrix");
}
