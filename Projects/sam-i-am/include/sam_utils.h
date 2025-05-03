#pragma once
#include "../include/sam_types.h" //types

namespace SAM {
	char getNewContactNumber();
	AircraftParams getArchetype(Faction, int = -1);
	void printUI(const std::string&, const std::vector<std::string>&, const std::vector<std::string>&, const std::string&);
	Coord getBearingMods(Bearing);
	std::string bearingToStr(Bearing);
	std::string factionToStr(Faction);
	void clearTerm();
	int manhattan(Coord, Coord);
	std::string coordToStr(Coord);
}