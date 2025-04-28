#pragma once
#include "sam_types.h" //types

namespace SAM {
	extern SharedBoard board;
	void initBoard(int, int);
	char getNewContactNumber();
	AircraftParams getArchetype(Faction, int = -1);
	std::vector<std::string> drawBoard();
	void printUI(std::string, std::vector<std::string>, std::vector<std::string>, std::string);
	std::pair<int, int> getBearingMods(Bearing);
	std::string bearingToStr(Bearing);
	std::string factionToStr(Faction);
	std::vector<std::pair<int, int>> getUnitList();
	void clear();
	bool makeAndPlace(ActorType, std::string, char, int, int);
	bool makeAndPlace(AircraftParams, Bearing, int, int);
	std::unique_ptr<Actor>& getCell(int, int);
	void setCell(int, int, std::unique_ptr<Actor>);
	void moveUnits(std::vector<std::pair<int, int>>);
	std::vector<std::string> listContacts(std::vector<std::pair<int, int>>);
}