#include <iostream>
#include <string>

#include "util/scanner.h" //library for validating user input

struct Address {
	std::string streetAddress;
	std::string city;
	int zipCode;
};

struct Customer {
	int customerID;
	std::string customerName;
	Address customerAddress;
};

int main() {

	return 0;
}