#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "Utility/text_utils.h"
#include "Utility/hangman_utils.h"

int main() {
	using std::cout, std::string, std::vector;

	const int NUM_WORDS = 3; //2 words will be selected
	vector<string> wordList;
	int errorLevel = populateWordList(wordList); //initialize wordlist from file
	if (errorLevel != 0) { //terminate early if there were problems generating wordlist
		cout << "Error " << errorLevel << ", check the README for more information.\n";
		return errorLevel;
	}
	//prepare vars
	string words = pickFromVec(wordList, NUM_WORDS); //select word(s) from list
	string message = "Welcome! Guess a letter.";
	wordList.clear(); //wordlist can be freed to save memory
	int lives = 7;
	vector<char> guessedLetters;
	cout << "Debug: " << words << '\n';
	system("pause");
	//game start
	while (lives > 0 && lettersLeftToGuess(words, guessedLetters) > 0) { //run until word is guessed or man is hanged
		drawBoard(lives, message, words, guessedLetters); //draw game state
		char input = getValidLetter(guessedLetters); //get user input, trunc string if needed
		guessedLetters.push_back(input); //store newly guessed letter
		if (charInString(input, words)) { //guess was correct
			message = "Good guess!";
		}
		else {
			lives--;
			message = "That wasn't right.";
		}
	}
	drawBoard(lives, message, words, guessedLetters);//display final board

	return 0;
}