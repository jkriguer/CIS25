#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

void inputMatrix(int**, char);
void printMatrix(int**, char);
void addMatrices(bool = true);
void multMatrices();

int** matrixA = new int* [2]; //initialize rows
int** matrixB = new int* [2];
int** matrixC = new int* [2];

int main() {
    for (int i = 0; i < 2; i++) {
        matrixA[i] = new int[2]; //initialize columns
        matrixB[i] = new int[2];
        matrixC[i] = new int[2];
    }

    inputMatrix(matrixA, 'A'); //input matrices A and B
    inputMatrix(matrixB, 'B');
    printMatrix(matrixA, 'A'); //print matrix A and B
    printMatrix(matrixB, 'B');

    cout << "What operation should be done? ";
    bool exit = false;
    while (!exit) {
        char choice;
        cout << "Enter \"*\", \"+\", or \"-\": ";
        cin >> choice;
        switch (choice) {
            case '*': cout << "Multiplying...\n";
                multMatrices();
                exit++;
                break;
            case '+': cout << "Adding...\n";
                addMatrices();
                exit++;
                break;
            case '-': cout << "Subtracting...\n";
                addMatrices(false);
                exit++;
                break;
            default: cout << "Input not recognized. ";
        }
    }
    printMatrix(matrixC, 'C');
}

void printMatrix(int** matrix, char label) {
    cout << "Matrix " << label << endl;
    int counter = 0, width = 0;
    for (int i = 0; i < 2; i++) { //scale setw for matrix output
        for (int j = 0; j < 2; j++) {
            if (to_string(matrix[i][j]).length() > width)
                width = to_string(matrix[i][j]).length();
        }
    }
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            cout << setw(width + 1) << matrix[i][j];
        }
        cout << '\n';
    }
}

void inputMatrix(int** matrix, char label) {
    cout << "Matrix " << label << " has " << 2 << " rows and " << 2 << " columns.\nEnter the " << 2 * 2 << " elements: ";
    for (int j = 0; j < 2; j++) {
        for (int k = 0; k < 2; k++) {
            cin >> matrix[j][k];
        }
    }
}

void addMatrices(bool add) {
    int sign = (add) ? 1 : -1;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            matrixC[i][j] = matrixA[i][j] + (sign * matrixB[i][j]);
        }
    }
}


void multMatrices() {
    cout << "Multiplying..\n";
    matrixC[0][0] = matrixA[0][0] * matrixB[0][0] + matrixA[0][1] * matrixB[1][0];
    matrixC[0][1] = matrixA[0][0] * matrixB[0][1] + matrixA[0][1] * matrixB[1][1];
    matrixC[1][0] = matrixA[1][1] * matrixB[1][0] + matrixA[1][0] * matrixB[0][0];
    matrixC[1][1] = matrixA[1][1] * matrixB[1][1] + matrixA[1][0] * matrixB[0][1];
}