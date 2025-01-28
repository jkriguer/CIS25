#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <string>

using namespace std;

string getCard() { //picks a card of any suit from 1 to 6
	string rank, suit;
	short roll = rand() % 13;
	switch (roll) {
		case 0:
			rank = "Ace";
			break;
		case 12:
			rank = "King";
			break;
		case 11:
			rank = "Queen";
			break;
		case 10:
			rank = "Jack";
			break;
		default:
			rank = to_string(roll + 1);
			break;
	}
	roll = rand() % 4;
	switch (roll) {
		case 0:
			suit = "Spades";
			break;
		case 1:
			suit = "Clubs";
			break;
		case 2:
			suit += "Hearts";
			break;
		case 3:
			suit = "Diamonds";
			break;
	}
	return rank + " of " + suit;
}

void printCard(int width, string card) {
	cout << string(width, '*') << "\n\n"; //top border
	cout << setw(width) << internal << card << '\n';
	cout << '\n' << string(width, '*') << '\n';
}

int main() {
	const int MAX_WIDTH = 40; //must be 40 for final submission
	long seed = time(nullptr);
	srand(seed);

	for (int i = 0; i < 2; i++)
		printCard(MAX_WIDTH, getCard());
}

/*
* OUTPUT
Card 1: 4 of Hearts
Card 2: 2 of Spades
Card 3: 4 of Spades
Card 4: 3 of Spades
Card 5: 3 of Diamonds
Card 6: 4 of Clubs
Card 7: 3 of Hearts
Card 8: 3 of Spades
Card 9: 5 of Diamonds
Card 10: 3 of Clubs

*/