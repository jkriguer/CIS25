#include <iostream>
#include "../include/sam_utils.h"
#include "../include/Actor.h"
#include "../include/Game.h"
#include "../include/sam_io.h"
#include "../include/scanner.h"



int main() {
	const std::vector<char> defaultScenario = { 
		10,//validator
		3, //static count
		2, 23, 18, //city 1
		0, 26, 22, //player
		2, 30, 18, //city 2
		5, //mobile count
		2, 1, 0, 26, 1, //friendly 1
		0, -1, 3, 49, 20, //neutral 1
		1, 1, 0, 16, 10, //hostile 1
		2, 1, 0, 25, 2, //friendly 2
		0, -1, 1, 10, 10, //neutral 2
		-10 //exit validator
	}; 

	//demonstrate save/loading of binaries
	if (!SAM::writeScenario("demo.bin", defaultScenario)) {
		throw std::runtime_error("write error");
	}
	std::vector<char> blob;
	if (!SAM::readScenario("demo.bin", blob)) {
		throw std::runtime_error("read error");
	}

	SAM::Game game;
	srand((unsigned int)time(nullptr)); //RNG seeded

	game.loadScenario(blob);
	//test UI
	std::string title = "Lorem ipsum dolor sit amet";
	std::string options = "consectetur adipiscing elit";
	SAM::printUI(title, game.drawBoard(), game.listContacts(game.getUnitList()), options);
	game.moveUnits(game.getUnitList());
	SAM::printUI(title, game.drawBoard(), game.listContacts(game.getUnitList()), options);
	return 0;
}