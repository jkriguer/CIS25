#include <iostream>

using namespace std;

int main() {
	string password;
	bool numbers, specials;
	cout << "This program will request passwords until an acceptable one is entered. ";
	do {
		cout << "Enter password to evaluate: ";
		cin >> password;
		numbers = false;
		specials = false;
		for (char ch : password) {
			if ((ch >= 33 && ch <= 47) || (ch >= 123 && ch <= 126)) //printable ascii special characters
				specials++;
			if (ch >= 48 && ch <= 57) //ascii numbers
				numbers++;
		}
	} while (password.length() < 8 || !numbers || !specials);
	cout << "Password \"" << password << "\" meets all requirements!\n";

	return 0;
}