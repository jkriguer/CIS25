#include <iostream>
#include <iomanip>
#include <string>
#include "Customer.h"

using namespace std;

int main() {
	srand(time(nullptr));
	Customer accountHolders[]{ 
		Customer("Bob", "Billy", 6),
		Customer("Smith", "Bob", 100.00), 
		Customer("Schmoe", "Joe", 421.70, 17), 
		Customer("Mark", "Anthony", 0.0, 5), 
		Customer()};
	
	return 0;
}