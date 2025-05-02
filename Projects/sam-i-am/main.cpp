#include <iostream>
#include "../include/sam_utils.h"
#include "../include/Actor.h"
#include "../include/Game.h"
#include "../include/sam_io.h"
#include "../include/scanner.h"

int main() {
	const std::vector<char> scenario = {
	10, //validator
	3, //static count
	0, 26, 22, //player
	2, 23, 18, //city 1
	2, 30, 18, //city 2
	8, //mobile count
	2, 0, 7, 27, 10, //fighter kills interdictor turn 2
	1, 1, 2, 11, 18, //interdictor kills city 1 turn 3
	1, 0, 4, 30, 28, //bomber kills city 2 turn 5
	1, 0, 4, 23, 28, //bomber kills city 1 turn 5
	1, 1, 6, 46, 18, //interdictor kills city 2 turn 4
	1, 3, 0, 32, 12, //command
	0, 1, 6, 31, 19, //cropduster
	0, 2, 3, 15, 28, //concorde
	-10 //exit validator
	};
	if (!SAM::writeScenario("demo2.bin", scenario)) {
		throw std::runtime_error("write error");
	}
	std::vector<char> blob;
	if (!SAM::readScenario("demo2.bin", blob)) { //load saved scenario binary
		throw std::runtime_error("read error");
	}

	SAM::Game game;
	srand((unsigned int)time(nullptr)); //RNG seeded

	game.loadScenario(blob);
	//test UI
	std::string title = "Lorem ipsum dolor sit amet";
	std::string options = "consectetur adipiscing elit";
	SAM::printUI(title, game.drawBoard(), game.listContacts(game.getUnitList()), options);
	for (int i = 0; i < 3; i++) {
		game.moveAllUnits(game.getUnitList());
		SAM::printUI(title, game.drawBoard(), game.listContacts(game.getUnitList()), options);
}
	return 0;
}