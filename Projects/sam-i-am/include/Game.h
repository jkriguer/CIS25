#pragma once
#include "../include/sam_types.h"
#include "../include/Actor.h"
#include <memory>

namespace SAM {
	class Game {
	private:
		const int DIM_X = 48; //board width
		const int DIM_Y = 30; //board height
		const int RANGE = 16; //missile range
		Board board;
		Status status{ Running };
		std::vector<std::string> logs;
		Coord playerPos; //cached SAM position
		int cityCount = 0; //for tracking destruction
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
		std::vector<WeakActor> getMobilePtrs();
		bool identify(const SharedActor&);
		std::vector<SharedActor> getUnidentified();
		Coord getPlayerPos();
		std::vector<std::string> getLogs();
		std::string getLastLog();
		int getCityCount();
		int getRange();
		void setStatus(Status);
	};
}