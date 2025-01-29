#include <iostream>

using namespace std;

int main() { //evaluates grade based on user input
	cout << "Enter grade: ";
	int score;
	cin >> score;

	if (score >= 90)
		cout << "Excellent!\n";
	else if (score >= 70)
		cout << "Good.\n";
	else if (score >= 60)
		cout << "Pass.\n";
	else
		cout << "Fail.\n";
	return 0;
}

/*
* OUTPUT
Enter grade: 73
Good.
*/