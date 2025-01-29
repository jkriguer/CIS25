#include <iostream>

using namespace std;

int main() {
	cout << "Enter your age in years: ";
	int age;
	cin >> age;

	if (age < 12)
		cout << "Child\n";
	else if (age < 19)
		cout << "Teen\n";
	else if (age < 64)
		cout << "Adult\n";
	else
		cout << "Senior\n";
	return 0;
}

/*
* OUTPUT
Enter your age in years: 34
Adult

*/