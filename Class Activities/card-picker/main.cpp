#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <string>

using namespace std;

string getCard() { //picks a random card
	string rank, suit;
	short roll = rand() % 52;
	switch (roll % 13) {
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
			rank = to_string((roll % 13) + 1);
			break;
	}
	switch (roll / 13) {
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


void printCard(int width, int player, string card) {
	string cardOwner = "Player ";
	if (player == 0)
		cardOwner = "Dealer";
	else
		cardOwner += to_string(player);
	cout << string(width, '*') << "\n\n"; //top border
	cout << setw(width / 2) << setfill('-') << left << cardOwner + "'s card ";
	cout << setw((width % 2 == 0) ? width / 2 : width / 2 + 1) << right << ' ' + card << '\n';
	cout << '\n' << string(width, '*') << '\n';
}

int main() {
	const int MAX_WIDTH = 40; //must be 40 for final submission
	long seed = time(nullptr);
	srand(seed);

	printCard(MAX_WIDTH, (rand() % 4), getCard());
}

/*
* OUTPUT
****************************************

Player 2's card ------------ 3 of Hearts

****************************************

*/