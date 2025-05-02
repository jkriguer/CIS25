#include <iostream>
#include "../include/sam_utils.h"
#include "../include/Actor.h"
#include "../include/Game.h"
#include "../include/sam_io.h"
#include "../include/scanner.h"



int main() {
	std::vector<char> blob;
	if (!SAM::readScenario("demo.bin", blob)) { //load saved scenario binary
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