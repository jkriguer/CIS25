#include "Date.h"
void Date::inputDate() {
	std::cout << "Enter the date's year: ";
	while (this->year < 1900 || this->year > 2100) {
		this->year = getNextInt();
	}
	std::cout << "Enter the date's month as an int (1 - 12): ";
	while (this->month < 1 || this->month > 12) {
		this->month = getNextInt();
	}
}

std::ostream& operator<<(std::ostream& os, const Date& date) {
	os << date.month << '/' << date.year;
	return os;
}