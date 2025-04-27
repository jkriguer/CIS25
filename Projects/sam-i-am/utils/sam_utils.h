#ifndef SAM_UTILS
#define SAM_UTILS

#include "sam_types.h" //types

namespace SAMUTIL {
	char getNewContactNumber();
	Aircraft getArchetype(Faction, int = -1);
	std::vector<std::string> drawBoard(const SharedBoard&);
	void printUI(std::string, std::vector<std::string>, std::string);
	std::pair<int, int> getBearingMods(Bearing);
	std::string bearingToStr(Bearing);
	std::string factionToStr(Faction);
	std::vector<std::pair<int, int>> getUnitList(const SharedBoard&);
	void clear();
	bool makeAndPlace(ActorType, const SharedBoard&, std::string, char, int, int);
	bool makeAndPlace(const SharedBoard&, Aircraft, Bearing, int, int);
}

#endif // !SAM_UTILS