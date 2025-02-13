#include <iostream>

using namespace std;

bool isPrime(int);

int main() {
	cout << "Enter an integer to evaluate: ";
	int input;
	cin >> input;
	input = (input < 0) ? -input : input;
	cout << input << string((isPrime(input)) ? " is prime!\n" : " is NOT prime!\n");
}

bool isPrime(int number) {
	int divisors = 0;
	for (int i = 1; i <= number; i++)
		if (number % i == 0)
			divisors++;
	return (divisors == 2) ? true : false;
}
