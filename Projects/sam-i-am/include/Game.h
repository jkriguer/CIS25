#pragma once
#include "../include/sam_types.h"
#include "../include/Actor.h"
#include <memory>

namespace SAM {
	class Game {
	private:
		const int DIM_X = 50; //board width
		const int DIM_Y = 30; //board height
		const int DELAY = 1; //1 turn delay for missiles
		const int RANGE = 12; //missile range
		Board board;
		Status status{ Running };
		OptionalRules rules{ true, false, true };
		std::vector<std::string> logs;
		std::vector<Missile> missiles;
		Coord playerPos; //cached SAM position
	public:
		Game();
		std::vector<std::string> drawBoard();
		Status getStatus();
		SharedActor& getCell(int, int);
		void setCell(int, int, SharedActor);
		void moveAllUnits(const std::vector<Coord>&);
		void moveUnits(const std::vector<Coord>&);
		std::vector<std::string> listContacts(const std::vector<Coord>&);
		bool inBounds(int, int);
		int getWidth();
		int getHeight();
		std::vector<Coord> getUnitList();
		bool makeAndPlace(ActorType, std::string, char, int, int);
		bool makeAndPlace(Faction, AircraftParams, Bearing, int, int);
		bool loadScenario(const std::vector<char>&);
		void log(std::string);
		bool launchMissile(const SharedActor&);
		void tickMissiles();
		std::vector<WeakActor> getMobilePtrs();
	};
}