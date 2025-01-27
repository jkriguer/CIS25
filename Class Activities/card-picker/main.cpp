#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;

string getCard() { //picks a card of any suit from 1 to 6
	string output;
	short roll = rand() % 6;
	if (roll == 0)
		output = "Ace";
	else
		output = to_string(roll + 1);
	roll = rand() % 4;
	switch (roll) {
		case 0:
			output += " of Spades";
			break;
		case 1:
			output += " of Clubs";
			break;
		case 2:
			output += " of Hearts";
			break;
		case 3:
			output += " of Diamonds";
			break;
	}
	return output;
}

int main() {
	long seed = time(nullptr);
	srand(seed);

	for (int i = 0; i < 10; i++)
		cout << "Card " << i + 1 << ": " << getCard() << '\n';
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