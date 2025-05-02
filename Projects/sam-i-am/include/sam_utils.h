#pragma once
#include "../include/sam_types.h" //types

namespace SAM {

	char getNewContactNumber();
	AircraftParams getArchetype(Faction, int = -1);
	void printUI(std::string, std::vector<std::string>, std::vector<std::string>, std::string);
	std::pair<int, int> getBearingMods(Bearing);
	std::string bearingToStr(Bearing);
	std::string factionToStr(Faction);
	void clearTerm();
}