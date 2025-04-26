#include <iostream>
#include "utils/sam_utils.h"
#include "utils/Actor.h"
#include "utils/FlyingActor.h"

int main() {
	const int X_MAX = 40; //board X size
	const int Y_MAX = 30; //board y size

	SharedBoard gameBoard = std::make_shared<Board>(Y_MAX);
	for (auto& row : *gameBoard) {
		row.resize(X_MAX);
	}

	//testing
	auto test = std::make_unique<Actor>(gameBoard, 5, 5, "Battery");
	(*gameBoard)[Y_MAX / 2][X_MAX / 2] = std::move(test);
	test = std::make_unique<FlyingActor>(gameBoard, 1, 1, "Test", Faction::FRIENDLY, 5, Bearing::S, false);
	(*gameBoard)[1][1] = std::move(test);
	printUI("Test title", drawBoard(gameBoard), "Test options");
	(*gameBoard)[1][1]->move();
	printUI("Test title", drawBoard(gameBoard), "Test options");
	std::cout << (*gameBoard)[Y_MAX / 2][X_MAX / 2]->toString() << '\n';
	std::cout << (*gameBoard)[1][1]->toString() << '\n';

	return 0;
}