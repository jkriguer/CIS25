#ifndef SAM_UTILS
#define SAM_UTILS

#include <vector>
#include <string>
#include "sam_types.h" //types

int getNewContactNumber();
std::vector<std::string> drawBoard(const SharedBoard& board);
void printUI(std::string, std::vector<std::string>, std::string);

#endif // !SAM_UTILS
