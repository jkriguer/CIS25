#pragma once
#include "../include/sam_types.h"
#include "../include/Actor.h"
#include <memory>

namespace SAM {

	class Game {
	private:
		const char SAVE_VERSION = static_cast<char>(10); //save version
		const int DIM_X = 50; //board width
		const int DIM_Y = 30; //board height
		Board board;
		Status status{ Running };
		OptionalRules rules { true, false, true };
	public:
		Game();
		std::vector<std::string> drawBoard();
		Status getStatus();
		std::unique_ptr<Actor>& getCell(int, int);
		void setCell(int, int, std::unique_ptr<Actor>);
		void moveUnits(const std::vector<Coord>&);
		std::vector<std::string> listContacts(const std::vector<Coord>&);
		bool inBounds(int, int);
		int getWidth();
		int getHeight();
		std::vector<Coord> getUnitList();
		bool makeAndPlace(ActorType, std::string, char, int, int);
		bool makeAndPlace(Faction, AircraftParams, Bearing, int, int);
		bool loadScenario(const std::vector<char>&);
	};

}