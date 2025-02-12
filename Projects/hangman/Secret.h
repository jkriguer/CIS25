#pragma once
#include <string>
#include <vector>
#include <iostream>

using std::string;

class Secret {
private:
	string wordTarget;
	string wordDisplay;
	int lives;
	std::vector<char> guessedLetters;
	string lifeDisplay(int);
public:
	Secret();
	Secret(std::vector<string>);
	int getLives();
	bool guess(char);
	bool isGuessedLetter(char);
	void setWord(string);
	void setLives(int);
	void modLives(int);
	string getWord(bool = true);
	void print();
	int getLetterQty(char);
};

