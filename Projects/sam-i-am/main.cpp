#include <iostream>
#include "utils/sam_utils.h"
#include "utils/Actor.h"
#include "utils/scanner.h"

using namespace SAM;

int main() {
	const int X_MAX = 60; //board X size
	const int Y_MAX = 36; //board y size

	initBoard(X_MAX, Y_MAX);

	using std::cout;

	/*PlayerParams missileArchetypes[]{ //"character select"
		PlayerParams("SA-2", 16, 1),
		PlayerParams("SA-3", 10, 0),
		PlayerParams("SA-4", 20, 3)
	};*/

	srand((int)time(nullptr)); //RNG seeded
	//place player and 2 cities
	int playerX = 26, playerY = 22;
	makeAndPlace(Player, "Battery", 'B', playerX, playerY);
	makeAndPlace(City, "City 1", 'C', 23, 18);
	makeAndPlace(City, "City 2", 'C', 30, 24);
	//place 2 friendlies
	makeAndPlace(getArchetype(Friendly, 1), South, 26, 1);
	makeAndPlace(getArchetype(Friendly, 1), South, 25, 2);
	//place 2 neutrals
	makeAndPlace(getArchetype(Neutral), East, 10, 10);
	makeAndPlace(getArchetype(Neutral), Northeast, 50, 20);
	//place 1 enemy
	makeAndPlace(getArchetype(Enemy, 1), West, 16, 10);
	//test UI
	std::string title = "Lorem ipsum dolor sit amet";
	std::string options = "consectetur adipiscing elit";
	//printUI(title, drawBoard(gameBoard), listContacts(gameBoard, testCoord), options); //known good
	printUI(title, drawBoard(), listContacts(getUnitList()), options);
	moveUnits(getUnitList());
	printUI(title, drawBoard(), listContacts(getUnitList()), options);
	return 0;
}