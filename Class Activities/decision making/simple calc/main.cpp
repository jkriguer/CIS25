#include <iostream>

using namespace std;

int main() {
	double operand1 = 0.0, operand2 = 0.0;
	cout << "Enter both operands: ";
	cin >> operand1 >> operand2;
	char operation;
	bool repeat = true;
	while (repeat) {
		cout << "Enter the operation to perform: (+ - * /): ";
		cin >> operation;
		switch (operation) {
			case '-':
				operand2 = -operand2;
			case '+':
				cout << operand1 + operand2 << '\n';
				repeat = false;
				break;
			case '*':
				cout << operand1 * operand2 << '\n';
				repeat = false;
				break;
			case '/':
				if (operand2 != 0)
					cout << operand1 / operand2 << '\n';
				else
					cout << "Undefined\n";
				repeat = false;
				break;
			default:
				cout << '"' << operation << "\" is not recognized. ";
		}
	}


	return 0;
}

/*
* OUTPUT
Enter both operands: 64 8
Enter the operation to perform: (+ - * /): k
"k" is not recognized. Enter the operation to perform: (+ - * /): /
8

*/