#ifndef SAM_UTILS
#define SAM_UTILS

#include "sam_types.h" //types

namespace SAMUTIL {
	char getNewContactNumber();
	Aircraft getArchetype(Faction);
	std::vector<std::string> drawBoard(const SharedBoard&);
	void printUI(std::string, std::vector<std::string>, std::string);
	std::pair<int, int> getBearingMods(Bearing);
	std::string bearingToStr(Bearing);
	std::string factionToStr(Faction);
	std::vector<std::pair<int, int>> getUnitList(const SharedBoard&);
	void clear();
}

//void makeAndPlaceActor(const SharedBoard&, int, int, std::string, char);
//void makeAndPlaceFlyingActor(const SharedBoard&, int, int, std::string, Faction, int, Bearing, bool);

#endif // !SAM_UTILS