#include <iostream>
#include "utils/sam_utils.h"
#include "utils/Actor.h"
#include "utils/Game.h"
#include "utils/scanner.h"



int main() {
	using namespace SAM;
	using std::cout;
	Game game;
	//Scenario defaultScenario(1U, 26, 22, 2, {23, 18, 30, 24}, 2, {26, 1, 2, 25, 2, 2}, ));

	srand((unsigned int)time(nullptr)); //RNG seeded
	//place player and 2 cities
	game.makeAndPlace(Player, "Battery", 'B', 26, 22);
	game.makeAndPlace(City, "City 1", 'C', 23, 18);
	game.makeAndPlace(City, "City 2", 'C', 30, 24);
	//place 2 friendlies
	game.makeAndPlace(getArchetype(Friendly, 1), South, 26, 1);
	game.makeAndPlace(getArchetype(Friendly, 1), South, 25, 2);
	//place 2 neutrals
	game.makeAndPlace(getArchetype(Neutral), East, 10, 10);
	game.makeAndPlace(getArchetype(Neutral), Northeast, 49, 20);
	//place 1 enemy
	game.makeAndPlace(getArchetype(Enemy, 1), West, 16, 10);
	//test UI
	std::string title = "Lorem ipsum dolor sit amet";
	std::string options = "consectetur adipiscing elit";
	printUI(title, game.drawBoard(), game.listContacts(game.getUnitList()), options);
	game.moveUnits(game.getUnitList());
	printUI(title, game.drawBoard(), game.listContacts(game.getUnitList()), options);
	return 0;
}