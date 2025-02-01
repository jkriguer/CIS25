#include "Customer.h"

Customer::Customer() {
	setName("Doe", true);
	setName("John", false);
	setBalance(0.0);
	setID(rand() % 10000);
}

Customer::Customer(string lname, string fname) : Customer() {
	setName(lname, true);
	setName(fname, false);
}

Customer::Customer(string lname, string fname, int newID) : Customer(lname, fname) {
	setID(newID);
}

Customer::Customer(string lname, string fname, double balance) : Customer(lname, fname) {
	setBalance(balance);
}

Customer::Customer(string lname, string fname, double balance, int newID) : Customer(lname, fname) {
	setBalance(balance);
	setID(newID);
}

void Customer::setName(string name, bool isSurname) {
	if (isSurname)
		nameLast = name;
	else
		nameFirst = name;
}

string Customer::getName(bool isSurname) {
	return (isSurname) ? nameLast : nameFirst;
}

void Customer::setBalance(double balance) {
	custBalance = balance;
}

void Customer::modBalance(double delta) {
	custBalance += delta;
}

double Customer::getBalance() {
	return custBalance;
}

void Customer::setID(int newID) {
	customerID = newID;
}

int Customer::getID() {
	return customerID;
}

void Customer::print() { //placeholder, use other func with pointers
	return;
}
