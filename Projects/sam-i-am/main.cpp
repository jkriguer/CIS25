#include <iostream>
#include "utils/sam_utils.h"
#include "utils/Actor.h"

int main() {
	const int X_MAX = 20; //board X size
	const int Y_MAX = 20; //board y size

	SharedBoard gameBoard = std::make_shared<Board>(Y_MAX);
	for (auto& row : *gameBoard) {
		row.resize(X_MAX);
	}

	auto player = std::make_unique<Actor>(gameBoard, X_MAX/2, Y_MAX/2, "Battery");
	(*gameBoard)[Y_MAX / 2][X_MAX / 2] = std::move(player);
	printBoard(gameBoard);

	return 0;
}