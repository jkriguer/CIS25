#ifndef HANGMAN_UTILS_H
#define HANGMAN_UTILS_H

#include "text_utils.h"
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <iomanip>

int populateWordList(std::vector<std::string>&);
void sortVecChars(std::vector<char>&);
std::string listVecChars(std::vector<char>);
bool charInVec(char, std::vector<char>);
std::string displayWords(std::string, std::vector<char>);
void drawBoard(int, std::string, std::string, std::vector<char>);
std::string pickFromVec(std::vector<std::string>, int = 2);
int lettersLeftToGuess(std::string, std::vector<char>);
char getValidLetter(std::vector<char>);
std::string pictogram(int, int);

#endif
