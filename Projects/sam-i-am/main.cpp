#include <iostream>
#include "utils/sam_utils.h"
#include "utils/Actor.h"
#include "utils/FlyingActor.h"
#include "utils/scanner.h"

using namespace SAMUTIL;

int main() {

	const int X_MAX = 30; //board X size
	const int Y_MAX = 50; //board y size

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

	//place player and city
	int playerX = X_MAX / 2 + (rand() % (X_MAX / 10) - (X_MAX / 5)); // 12~18?
	int playerY = Y_MAX / 2 + (rand() % (Y_MAX / 10) - (Y_MAX / 5)); // 22~27?
	(*gameBoard)[playerX][playerY] = std::make_unique<Actor>(gameBoard, playerX, playerY, "Battery", 'B');
	(*gameBoard)[playerX - 2][playerY - 2] = std::make_unique<Actor>(gameBoard, playerX - 3, playerY - 3, "City", 'C');

	//place 2 friendlies
	(*gameBoard)[1][26] = std::make_unique<FlyingActor>(gameBoard, 26, 1, getArchetype(Friendly, 1), South);
	(*gameBoard)[1][25] = std::make_unique<FlyingActor>(gameBoard, 25, 1, getArchetype(Friendly, 1), South);

	//place 2 neutrals
	//(*gameBoard)[15][]


	printUI("Test title", drawBoard(gameBoard), "Test options");
	std::cout << (*gameBoard)[1][26]->toString();
	(*gameBoard)[1][1]->move();
	printUI("Test title", drawBoard(gameBoard), "Test options");
	std::cout << (*gameBoard)[Y_MAX / 2][X_MAX / 2]->toString() << '\n';
	std::cout << (*gameBoard)[1][1]->toString() << '\n';

	return 0;
}