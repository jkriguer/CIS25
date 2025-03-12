#include "matrix_console.h"

void inputMatrix(Matrix& mat) {
	vector<double> in(mat.size() * mat[0].size());
	std::cout << "Enter " << in.size() << " elements: ";
	for (int i = 0; i < in.size(); i++) {
		std::cin >> in[i];
	}
	mat = makeMatrix(mat.size(), mat[0].size(), in);
}

void printMatrix(Matrix mat) {
	int width = 3; //arbitrary start width
	for (const auto& col : mat) { //first loop for spacing width
		for (double item : col) {
			int newWidth = std::format("{:g}", item).length() + 1; //convert to string and remove padding
			if (newWidth > width) { //store new width if wider than current widest
				width = newWidth;
			}
		}
	}
	for (const auto& col : mat) { //second loop for printing
		for (double item : col) {
			std::cout << std::setw(width) << std::left << std::format("{:g}", item);
		}
		std::cout << '\n';
	}
}