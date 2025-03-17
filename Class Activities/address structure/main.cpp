#include <iostream>
#include <string>
#include <vector>

#include "util/scanner.h" //library for validating user input

struct Address {
	std::string streetAddress = "123 Example Street";
	std::string city = "Example City";
	int zipCode = -1;

	std::string toString();
};

struct Customer {
	int customerID = -1;
	std::string customerName = "Unnammed Customer";
	Address customerAddress;
	std::string toString();
};

int main() {
	std::vector<Customer> customerList{
		Customer(155, "John Doe", Address("123 Telegraph Avenue", "Oakland", 54321)),
		Customer(255, "Jane Day", Address("456 Shattuck Avenue", "Berkeley", 12345)),
		Customer(355, "Jimmy John", Address("789 Main Street", "Springfield", 11111))
	};
	std::cout << "Enter a customer for testing the system.\n";
	Customer testCust;
	std::cout << "Enter the customer's ID: ";
	testCust.customerID = getNextInt();
	std::cout << "Enter the customer's full name: ";
	testCust.customerName = getNextLineAlpha();
	std::cout << "Enter the customer's street address: ";
	Address testAddr;
	testAddr.streetAddress = getNextLine();
	std::cout << "Enter the customer's city: ";
	testAddr.city = getNextLineAlpha();
	std::cout << "Enter the customer's ZIP code: ";
	testAddr.zipCode = getNextInt();
	testCust.customerAddress = testAddr;
	customerList.push_back(testCust);
	std::cout << "Customer added to list! Dumping list...\n";
	for (auto& cust : customerList) {
		std::cout << cust.toString() << '\n';
	}
	return 0;
}

std::string Address::toString() {
	return this->streetAddress + ", " + this->city + ", " + std::to_string(this->zipCode);
}

std::string Customer::toString() {
	return "ID: " + std::to_string(this->customerID) +
		", Name: " + this->customerName +
		", Address: " + this->customerAddress.toString();
}