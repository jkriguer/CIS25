#ifndef matrix_io
#define matrix_io
#include "matrix_utils.h"
#include <fstream>

int saveMatrix(Matrix& mat, std::string filename = "untitled_matrix");
int loadMatrix(Matrix& mat, std::string filename = "untitled_matrix");

#endif