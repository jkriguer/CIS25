#ifndef SAM_UTILS
#define SAM_UTILS

#include <vector>
#include <string>
#include "sam_types.h" //types

char getNewContactNumber();
std::vector<std::string> drawBoard(const SharedBoard&);
void printUI(std::string, std::vector<std::string>, std::string);
std::pair<int, int> getBearingMods(Bearing);
std::vector<std::pair<int, int>> getUnitList(const SharedBoard&);
#endif // !SAM_UTILS
