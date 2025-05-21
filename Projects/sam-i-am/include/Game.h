#pragma once
#include "../include/sam_types.h"
#include "../include/StaticActor.h"
#include "../include/MovingActor.h"
#include <memory>

namespace SAM {
	class Game {
	private:
		Board board;
		Status status{ Running };
		std::vector<std::string> logs;
		Coord playerPos{ 0, 0 }; //cached SAM position
		int cityCount = 0; //for tracking destruction
	public:
		const int DIM_X = 48; //board width
		const int DIM_Y = 30; //board height
		const int RANGE = 16; //missile range
		Game();

		std::vector<std::string> drawBoard();
		bool inBounds(Coord);

		ActorPtr& getCell(Coord);
		void setCell(Coord, ActorPtr);

		void moveAllUnits(const std::vector<Coord>&);
		void moveUnits(const std::vector<Coord>&);

		std::vector<Coord> getUnitList();
		bool makeAndPlace(std::string, char, Coord);
		bool makeAndPlace(Faction, AircraftParams, Bearing, Coord);
		bool loadScenario(const std::vector<char>&);


		std::vector<std::string> listContacts(const std::vector<Coord>&);

		bool launchMissile(Coord);
		bool identify(Coord);


		void setStatus(Status);
		Status getStatus();
		Coord getPlayerPos();
		int getCityCount();
		std::vector<std::string> getLogs();
		std::string getLastLog();
		void log(std::string);

		std::vector<Coord> sortByDistance(const std::vector<Coord>&, Coord) const;
	};
}