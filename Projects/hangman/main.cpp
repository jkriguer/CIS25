#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "Secret.h"

int createWordList(std::vector<string>&);

int main() {
	using std::cout;
	using std::cin;

	std::vector<string> words;
	if (createWordList(words) == -1) { //terminate if wordlist.txt is inaccessible
		cout << "Error: wordlist file couldn't be accessed.\n";
		return -1;
	}
	if (words.size() == 0) { //terminate if wordlist opened but had no contents
		cout << "Error: wordlist file was empty.\n";
		return -2;
	}
	srand((unsigned)time(nullptr));


	Secret game(words);
	cout << game.getWord() << '\n';
	for (char ch = 'a'; ch <= 'z'; ch++) {
		if (game.guess) > 0) {
			cout << ch << checkChar(game.getWord(), ch) << ' ';
		}
	}

	return 0;
}

int createWordList(std::vector<string>& vec) { //generate word list vector from file
	std::ifstream inputFile;
	string inputWord;
	inputFile.open("wordlist.txt"); //file handle opened
	if (!inputFile.is_open()) { //error if file can't be opened
		return -1;
	}
	while (std::getline(inputFile, inputWord)) {
		vec.push_back(inputWord);
	}
	inputFile.close(); //file handle closed
	return 0;
}