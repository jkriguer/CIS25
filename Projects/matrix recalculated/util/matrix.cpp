#include "matrix.h"

Matrix::Matrix(int dim) { //x*x ident
	
}
Matrix::Matrix(int _rows, int _cols) { //x*y all zero

}
Matrix::Matrix(int _rows, int _cols, vector<int> vec) { //x*y matrix with vec elements
	if (vec.size() != _rows * _cols) { //terminate if vec doesn't match, maybe output an error?

	}
}
Matrix::Matrix(vector<vector<int>>) { //take an already perfectly good matrix

}
