#include "matrix_utils.h"

const Matrix FAIL_MATRIX = Matrix(0, std::vector<double>(0)); //invalid 0x0 matrix that returns for catching errors

Matrix blankMatrix(int rows, int cols, double filler) { //create blank rows*cols matrix
	return Matrix(rows, std::vector<double>(cols, filler));
}

Matrix identityMatrix(int dim) { //create square matrix for multiplicative identity
	Matrix output = blankMatrix(dim, dim, 0.0);
	for (int i = 0; i < dim; i++) {
		output[i][i] = 1.0;
	}
	return output;
}

Matrix matrixMathAdd(Matrix matA, Matrix matB) {
	if (!canMatricesAdd(matA, matB)) { //terminate early if addition not possible
		return FAIL_MATRIX; //0x0 matrix, invalid
	}

	Matrix output = Matrix(matA.size(), std::vector<double>(matA[0].size()));
	for (int i = 0; i < matA.size(); i++) {
		for (int j = 0; j < matA[0].size(); j++) {
			output[i][j] = matA[i][j] + matB[i][j];
		}
	}

	return output;
}

bool isMatrixValid(Matrix mat) {
	if (mat.size() < 1) { //catch edge case where matrix row has 0 length
		return false;
	}
	for (int i = 1; i < mat.size(); i++) { //check each column against previous
		if (mat[i].size() != mat[i - 1].size()) { //matrix can't have cols of differing size
			return false;
		}
	}
	return true;
}

bool canMatricesAdd(Matrix matA, Matrix matB) {
	return (isMatrixValid(matA) && isMatrixValid(matB)) && //matrices must both be valid
		(matA.size() == matB.size()) && //matrix rows must match
		(matA[0].size() == matB[0].size()); //matrix cols must match
}

bool canMatricesMult(Matrix matA, Matrix matB) {
	return (isMatrixValid(matA) && isMatrixValid(matB)) && //matrices must both be valid
		(matA[0].size() == matB.size()); //matrix A cols must match matrix B rows
}