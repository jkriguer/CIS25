#include <iostream>
#include "utils/sam_utils.h"
#include "utils/Actor.h"
#include "utils/scanner.h"

using namespace SAMUTIL;

int main() {

	const int X_MAX = 40; //board X size
	const int Y_MAX = 60; //board y size

	SAM missileArchetypes[]{ //"character select"
	SAM("SA-2", 16, 1),
	SAM("SA-3", 10, 0),
	SAM("SA-4", 20, 3)
	}; 

	SharedBoard gameBoard = std::make_shared<Board>(Y_MAX);
	for (auto& row : *gameBoard) { //avoid copying unique pointers this way
		row.resize(X_MAX);
	}

	srand((int)time(nullptr)); //RNG seeded

	//place player and 2 cities
	makeAndPlace(Player, gameBoard, "Battery", 'B', 16, 22);
	makeAndPlace(City, gameBoard, "City 1", 'C', 13, 18);
	makeAndPlace(City, gameBoard, "City 2", 'C', 20, 24);

	//place 2 friendlies
	makeAndPlace(gameBoard, getArchetype(Friendly, 1), South, 26, 1);
	makeAndPlace(gameBoard, getArchetype(Friendly, 1), South, 25, 2);

	//place 2 neutrals
	makeAndPlace(gameBoard, getArchetype(Neutral), East, 10, 10);
	makeAndPlace(gameBoard, getArchetype(Neutral), Northeast, 20, 20);


	printUI("Test title", drawBoard(gameBoard), "Test options");
	std::cout << (*gameBoard)[1][26]->toString();
	(*gameBoard)[1][1]->move();
	printUI("Test title", drawBoard(gameBoard), "Test options");
	std::cout << (*gameBoard)[Y_MAX / 2][X_MAX / 2]->toString() << '\n';
	std::cout << (*gameBoard)[1][1]->toString() << '\n';

	return 0;
}