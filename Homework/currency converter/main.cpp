#include <iostream>
#include <iomanip>

using namespace std;

int main() {
	//JPY, USD, EUR, GBP
	//rates as of 2025-FEB-01
	const double RATES_JPY[]{ 0.0, 0.0064, 0.0062, 0.0052 };
	const double RATES_USD[]{ 155.21, 0.0, 0.97, 0.81 };
	const double RATES_EUR[]{ 160.83, 1.04, 0.0, 0.84 };
	const double RATES_GBP[]{ 192.41, 1.24, 1.2, 0.0 };
	double exchangeFee = 0.0; //no default fee

	srand(time(nullptr));
	if (rand() % 2 == 0) {
		cout << "It's your lucky day! For the next exchange, enjoy a 3% discount!\n";
		exchangeFee = -0.03;
	}


	string srcCurrency, dstCurrency;
	const double* CURRENCY = nullptr;
	cout << "Enter the input currency. ";
	while (CURRENCY == nullptr) { //menu for source currency
		cout << "Valid selections: (J)PY, (U)SD, (E)UR, or (G)BP: ";
		char input;
		cin >> input;
		switch (input) {
			case 'j': case 'J':
				CURRENCY = RATES_JPY;
				srcCurrency = "JPY";
				break;
			case 'u': case 'U':
				CURRENCY = RATES_USD;
				srcCurrency = "USD";
				break;
			case 'e': case 'E':
				CURRENCY = RATES_EUR;
				srcCurrency = "EUR";
				break;
			case 'g': case 'G':
				CURRENCY = RATES_GBP;
				srcCurrency = "GBP";
				break;
			default:
				cout << "Input not recognized. ";
		}
	}
	cout << srcCurrency << " selected as input!\n";

	cout << "Enter the output currency. ";
	int currencyIndex = -1;
	while (currencyIndex == -1) { //menu for destination currency
		cout << "Valid selections: (J)PY, (U)SD, (E)UR, or (G)BP: ";
		char input;
		cin >> input;
		switch (input) {
			case 'j': case 'J':
				currencyIndex = 0;
				dstCurrency = "JPY";
				break;
			case 'u': case 'U':
				currencyIndex = 1;
				dstCurrency = "USD";
				break;
			case 'e': case 'E':
				currencyIndex = 2;
				dstCurrency = "EUR";
				break;
			case 'g': case 'G':
				currencyIndex = 3;
				dstCurrency = "GBP";
				break;
			default:
				cout << "Input not recognized. ";
		}
	}
	cout << dstCurrency << " selected as output!\n";

	if (CURRENCY[currencyIndex] == 0.0) { //stop if src and dst are the same
		cout << "You can't have the same currency for input and output. Terminating...\n";
		return -1;
	}

	cout << "1 " << srcCurrency << " : " << CURRENCY[currencyIndex] * (1.0 - exchangeFee) << ' ' << dstCurrency << '\n';
	cout << "How many " << srcCurrency << " do you want to exchange for " << dstCurrency << "? ";
	double currencyToExchange;
	cin >> currencyToExchange;
	cout << fixed << setprecision(2) << currencyToExchange << ' ' << srcCurrency << " exchanged for " << 
		fixed << setprecision(2) << CURRENCY[currencyIndex] * (1.0 - exchangeFee) * currencyToExchange << ' ' << dstCurrency << " successfully.\n";

	return 0;
}

/*
* OUTPUT
Enter the input currency. Valid selections: (J)PY, (U)SD, (E)UR, or (G)BP: u
USD selected as input!
Enter the output currency. Valid selections: (J)PY, (U)SD, (E)UR, or (G)BP: j
JPY selected as output!
1 USD : 155.21 JPY
How many USD do you want to exchange for JPY? 100
100.00 USD exchanged for 15521.00 JPY successfully.

* OUTPUT
It's your lucky day! For the next exchange, enjoy a 3% discount!
Enter the input currency. Valid selections: (J)PY, (U)SD, (E)UR, or (G)BP: u
USD selected as input!
Enter the output currency. Valid selections: (J)PY, (U)SD, (E)UR, or (G)BP: j
JPY selected as output!
1 USD : 159.866 JPY
How many USD do you want to exchange for JPY? 100
100.00 USD exchanged for 15986.63 JPY successfully.

*/