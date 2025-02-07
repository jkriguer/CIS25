#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "Secret.h"

using std::cout;
using std::cin;

int checkChar(string, char);
void printBoard(string);
int createWordList(vector<string>);

int main() {
	vector<string> words;
	if (createWordList(words) == -1) { //terminate if wordlist couldn't be opened
		return -1;
	}
	if (words.size() == 0) { //terminate if wordlist was empty or couldn't be read
		return -2;
	}
	for (string str : words) //debug print wordlist
		cout << str << ' ';
	srand((unsigned)time(nullptr));
	/*Secret word(words);
	cout << word.getWord() << '\n';
	for (char ch = 'a'; ch <= 'z'; ch++) {
		if (checkChar(word.getWord(), ch) > 0) {
			cout << ch << checkChar(word.getWord(), ch) << ' ';
		}
	}*/
	return 0;
}

int checkChar(string word, char input) { //rename, returns number of correct chars
	int numberCorrect = 0;
	for (char ch : word) {
		if (ch == input) {
			numberCorrect++;
		}
	}
	return numberCorrect;
}

int createWordList(vector<string> vec) { //generate word list vector from file
	std::ifstream inputFile;
	string inputWord;
	inputFile.open("wordlist.txt"); //file handle opened
	if (!inputFile.is_open()) { //error if file can't be opened
		return -1;
	}
	while (std::getline(inputFile, inputWord)) {
		inputFile >> inputWord;
		vec.push_back(inputWord);
	}
	inputFile.close(); //file handle closed
	return 0;
}
