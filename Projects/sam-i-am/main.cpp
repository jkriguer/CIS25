#include <iostream>
#include "../include/sam_utils.h"
#include "../include/Actor.h"
#include "../include/Game.h"
#include "../include/scanner.h"



int main() {
	using std::cout;
	SAM::Game game;
	srand((unsigned int)time(nullptr)); //RNG seeded

	game.loadScenario(SAM::defaultScenario);
	//test UI
	std::string title = "Lorem ipsum dolor sit amet";
	std::string options = "consectetur adipiscing elit";
	printUI(title, game.drawBoard(), game.listContacts(game.getUnitList()), options);
	game.moveUnits(game.getUnitList());
	printUI(title, game.drawBoard(), game.listContacts(game.getUnitList()), options);
	return 0;
}