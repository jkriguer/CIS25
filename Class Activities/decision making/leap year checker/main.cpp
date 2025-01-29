#include <iostream>

using namespace std;

int isLeapYear(int);

int main() {
	cout << "Enter year: ";
	int year;
	cin >> year;
	cout << year << string(isLeapYear(year) ? " is " : " is NOT ") << "a leap year.\n";

	return 0;
}

int isLeapYear(int year) {
	if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
		return true;
	return false;
}

/*
* OUTPUT
Enter year: 2000
2000 is a leap year.

* OUTPUT
Enter year: 1900
1900 is NOT a leap year.

*/