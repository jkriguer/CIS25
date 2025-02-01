#pragma once
#include <string>

using std::string;

class Customer {
private:
	string nameLast;
	string nameFirst;
	double custBalance;
	int customerID;
public:
	Customer();
	Customer(string, string);
	Customer(string, string, int);
	Customer(string, string, double);
	Customer(string, string, double, int);
	void setName(string, bool);
	string getName(bool);
	void setBalance(double);
	void modBalance(double);
	double getBalance();
	void setID(int);
	int getID();
	void print();
};

