#include "matrix_io.h"


int saveMatrix(Matrix& mat, std::string filename) { //saves Matrix mat to filename.csv, returns errorlevel
    if (!isMatrixValid(mat)) {
        return -1; //error if invalid input
    }
    std::ofstream file(filename + ".csv"); //file handle opened
    if (!file) {
        return -2; //error if file handle couldn't be opened
    }
    for (const auto& row : mat) {
        for (int i = 0; i < row.size(); i++) {
            file << row[i]; //write element to file
            if (i < row.size() - 1) {
                file << ','; //write comma to file unless last element on line
            }
        }
        file << '\n';
    }
    file.close(); //file handle closed
    return 0; //no error
}

int loadMatrix(Matrix& mat, std::string filename) { //loads filename.csv into Matrix mat, returns errorlevel
    //TODO add handling for filename including ".csv" and remove it
    std::ifstream file(filename);
    if (!file) {
        return -2; //error if file handle couldn't be opened
    }
    int rows = 0, cols = 0;
    vector<double> contents;
    //TODO actually measure and save elements
    mat = makeMatrix(rows, cols, contents);
    file.close(); //file handle closed
    return 0; //no error
}