#pragma once
#include <string>
#include <vector>

using std::string;
using std::vector;

class Secret {
private:
	string wordTarget;
	string wordDisplay;
	int lives;
	vector<char> guessedLetters;
public:
	Secret();
	Secret(vector<string>);
	int getLives();
	int guess(char);
	void setWord(string);
	void setLives(int);
	void modLives(int);
	string getWord(bool = true);
};

