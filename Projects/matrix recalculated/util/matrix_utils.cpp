#include "matrix_utils.h"

const Matrix FAIL_MATRIX = Matrix(0, std::vector<double>(0)); //invalid 0x0 matrix that returns for catching errors

Matrix blankMatrix(int rows, int cols, double filler) { //create blank rows*cols matrix
	return Matrix(rows, std::vector<double>(cols, filler));
}

Matrix identityMatrixAdd(int x, int y){
	return blankMatrix(x, y, 0.0);
}

Matrix identityMatrixMult(int dim) { //create square matrix for multiplicative identity
	Matrix output = blankMatrix(dim, dim, 0.0);
	for (int i = 0; i < dim; i++) {
		output[i][i] = 1.0;
	}
	return output;
}

Matrix inverseMatrixAdd(Matrix mat) { //create additive inverse of matrix
	for (auto& i : mat) {
		for (auto& j : i) {
			j = -j;
		}
	}
	return mat;
}

Matrix inverseMatrixMult(Matrix) { //create multiplicative inverse of matrix
	return FAIL_MATRIX;
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

Matrix matrixMathMult(Matrix matA, Matrix matB) { //hardcoded 2x2 only
	if (!canMatricesMult(matA, matB)) { //return early if invalid
		return FAIL_MATRIX;
	}
	Matrix out = Matrix(matA.size(), std::vector<double>(matB[0].size()));
	out[0][0] = matA[0][0] * matB[0][0] + matA[0][1] * matB[1][0];
	out[0][1] = matA[0][0] * matB[0][1] + matA[0][1] * matB[1][1];
	out[1][0] = matA[1][1] * matB[1][0] + matA[1][0] * matB[0][0];
	out[1][1] = matA[1][1] * matB[1][1] + matA[1][0] * matB[0][1];
	return out;
}

Matrix makeMatrix(int rows, int cols, std::vector<double> vec) {
	if (vec.size() != rows * cols) { //confirm that vector contains exactly enough elements for new matrix
		return FAIL_MATRIX; //return 0x0 invalid
	}
	Matrix output = blankMatrix(rows, cols);
	int vecIndex = 0;
	for (int i = 0; i < rows; i++) { //populate output matrix row by row
		for (int j = 0; j < cols; j++) {
			output[i][j] = vec[vecIndex++];
		}
	}
	return output;
}

bool isMatrixValid(Matrix mat) {
	if (mat.empty()) { //catch empty matrix
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
	if (!isMatrixValid(matA) || !isMatrixValid(matB)) { //avoid segfault by checking possible emptiness separately
		return false;
	}
	return (matA.size() == matB.size()) && //matrix rows must match
		(matA[0].size() == matB[0].size()); //matrix cols must match
}

bool canMatricesMult(Matrix matA, Matrix matB) {
	if (!isMatrixValid(matA) || !isMatrixValid(matB)) { //avoid segfault by checking possible emptiness separately
		return false;
	}
	return (matA[0].size() == matB.size()); //matrix A cols must match matrix B rows
}