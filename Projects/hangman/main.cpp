#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "Utility/text_utils.h"
#include "Utility/hangman_utils.h"

int main() {
	using std::cout, std::string, std::vector;

	const int NUM_WORDS = 2; //2 words will be selected
	vector<string> wordList;
	int errorLevel = populateWordList(wordList); //initialize wordlist from file
	if (errorLevel != 0) { //terminate early if there were problems generating wordlist
		cout << "Error " << errorLevel << ", check the README for more information.\n";
		return errorLevel;
	}

	//prepare vars
	string words = pickFromVec(wordList, NUM_WORDS); //select word(s) from list
	wordList.clear(); //wordlist can be freed to save memory
	int lives = 7;
	vector<char> guessedLetters;

	//game start
	while (lives > 0 && lettersLeftToGuess(words, guessedLetters) > 0) { //run until word is guessed or man is hanged
		drawBoard(lives, words, guessedLetters); //draw game state
		char input = getValidLetter(guessedLetters); //get user input, trunc string if needed
		guessedLetters.push_back(input); //store newly guessed letter
		if (!charInString(input, words)) { //guess was incorrect
			lives--;
		}
	}
	drawBoard(lives, words, guessedLetters);//display final board
	cout << "Game over!\n";
	cout << ((lives == 0) ? "The solution was \"" + words + "\"" : "You guessed all the words!") << '\n';
	cout << "You made " << guessedLetters.size() << " guesses.\n";
	return 0;
}