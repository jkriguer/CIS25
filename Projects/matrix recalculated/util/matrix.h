#pragma once
#include <vector>
#include <memory>

using std::unique_ptr, std::vector;

class Matrix {
private:
	int rows;
	int cols;
	unique_ptr<vector<vector<int>>> contents; //wtf
public:
	//constructors
	Matrix(); //2*2 identity
	Matrix(int); //x*x identity
	Matrix(int, int); //x*y identity
	Matrix(int, int, vector<int>); //input vec must be x*y elements long
	Matrix(vector<vector<int>>); //matrix size determined by vec dimensions
	//setters and getters
	void setRows(int);
	void setCols(int);
};