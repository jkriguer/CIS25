#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include "Customer.h"

using namespace std;

void printAll(vector<Customer> vec) {
	string name, bal;
	int nameWidth = 5, balWidth = 5; //arbitrary minimum column size
	for (int i = 0; i < vec.size(); i++) { //check if columns need resizing
		int newNameWidth = vec[i].getName(true).length() + vec[i].getName(false).length() + 4;
		int newBalWidth = to_string(vec[i].getBalance()).size() - 2;
		nameWidth = (newNameWidth > nameWidth) ? newNameWidth : nameWidth;
		balWidth = (newBalWidth > balWidth) ? newBalWidth : balWidth;
	}
	cout << setw(6) << left << "ID" << setw(nameWidth - 1) << "Name" << setw(balWidth) << "Balance ($)" << '\n';
	cout << string(5, '-') + ' ' + string(nameWidth - 2, '-') + ' ' + string(balWidth, '-') + '\n';
	for (int i = 0; i < vec.size(); i++) {
		cout << setw(5) << right << setfill('0') << vec[i].getID()
			<< setw(nameWidth) << left << setfill(' ') << ' ' + vec[i].getName(true) + ", " + vec[i].getName(false)
			<< setw(balWidth) << right << fixed << setprecision(2) << vec[i].getBalance() << '\n';
	}
}

int main() {
	srand(time(nullptr));
	vector<Customer> accountHolders = { Customer(), Customer("Bob", "Billy", 106), Customer("Smith", "Bob", 123456.78) };
	accountHolders.push_back(Customer("Schmoe", "Joe", 421.70, 17));
	accountHolders.push_back(Customer("Mark", "Anthony", 0.0, 5));
	cout << "5 predetermined entries added for demonstration purposes.\n";
	printAll(accountHolders);
	cout << "\nAdd more customers! Enter their last name, first name, balance in USD and ID#\n";
	cout << "Input a single . to stop.\n";
	string newF, newL;
	int newID;
	double newBal;
	while (true) {
		cin >> newL;
		if (newL == ".")
			break;
		cin >> newF >> newBal >> newID;
		accountHolders.push_back(Customer(newL, newF, newBal, newID));
	}
	cout << "Done entering.\n\n";
	printAll(accountHolders);

	return 0;
}

/*
* OUTPUT
5 predetermined entries added for demonstration purposes.
ID    Name          Balance ($)
----- ------------- -----------
02272 Doe, John            0.00
00106 Bob, Billy           0.00
06287 Smith, Bob      123456.78
00017 Schmoe, Joe        421.70
00005 Mark, Anthony        0.00

Add more customers! Enter their last name, first name, balance in USD and ID#
Input a single . to stop.
Washington George 17.76 1
Carter Jimmy 5.00 39
Gandhi Mahatma 6.0 1948
Irwin Steve 19.62 2006
.
Done entering.

ID    Name               Balance ($)
----- ------------------ -----------
02272 Doe, John                 0.00
00106 Bob, Billy                0.00
06287 Smith, Bob           123456.78
00017 Schmoe, Joe             421.70
00005 Mark, Anthony             0.00
00001 Washington, George       17.76
00039 Carter, Jimmy             5.00
01948 Gandhi, Mahatma           6.00
02006 Irwin, Steve             19.62
*/