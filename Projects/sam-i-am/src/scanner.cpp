#include "../include/scanner.h"

int getNextInt() {
	using std::cin;
	int input;
	while (true) {
		cin >> input;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			//insert error message here
		}
		else {
			break;
		}
	}
	return input;
}

double getNextDouble() {
	using std::cin;
	double input;
	while (true) {
		cin >> input;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			//insert error message here
		}
		else {
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			break;
		}
	}
	return input;
}

std::string getNextLine() {
	using std::cin;
	std::string input;
	while (true) {
		std::getline(cin, input);
		if (input.empty()) {
			//insert error message here
		}
		else {
			break;
		}
	}
	return input;
}

std::string getNextLineAlpha() {
	using std::cin;
	std::string input;
	while (true) {
		std::getline(cin, input);
		bool isNumeric = std::all_of(input.begin(), input.end(), ::isdigit);
		if (input.empty() || isNumeric) {
			//insert error message here
		}
		else {
			break;
		}
	}
	return input;
}