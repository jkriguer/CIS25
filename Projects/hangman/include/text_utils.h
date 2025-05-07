#ifndef TEXT_UTILS_H
#define TEXT_UTILS_H

#include <string>
#include <vector>

bool isAlpha(char);
bool isAlpha(std::string);
char toUpper(char);
std::string toUpper(std::string);
char toLower(char);
std::string toLower(std::string);
void clear();
std::string listChars(std::vector<char>);
bool charInString(char, std::string);

#endif