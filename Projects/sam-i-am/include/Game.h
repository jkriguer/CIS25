#pragma once
#include "../include/sam_types.h"
#include "../include/Actor.h"
#include <memory>

namespace SAM {

	class Game {
	private:
		const unsigned char SAVE_VERSION = 1U; //save version
		const int DIM_X = 50; //board width
		const int DIM_Y = 30; //board height
		Board board;
		Status status{ Running };
		OptionalRules rules { true, false, true };

	public:
		Game();
		Game(Scenario);
		std::vector<std::string> drawBoard();
		Status getStatus();
		std::unique_ptr<Actor>& getCell(int, int);
		void setCell(int, int, std::unique_ptr<Actor>);
		void moveUnits(std::vector<std::pair<int, int>>);
		std::vector<std::string> listContacts(std::vector<std::pair<int, int>>);
		bool inBounds(int, int);
		int getWidth();
		int getHeight();
		std::vector<std::pair<int, int>> getUnitList();
		bool makeAndPlace(ActorType, std::string, char, int, int);
		bool makeAndPlace(AircraftParams, Bearing, int, int);

	};

}