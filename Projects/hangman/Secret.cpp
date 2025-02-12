#include "Secret.h"

string Secret::lifeDisplay(int lives) { //seperate function purely for readability's sake
	std::vector<string> ascii{                                                    // 0      1      2      3      4      5      6
		".----.\n.|..|.\n.|..o.\n.|./|\\\n.|./.\\\n.|....\n.|....\n======\n", // .----. .----. .----. .----. .----. .----. .----.
		".----.\n.|..|.\n.|..o.\n.|./|\\\n.|...\\\n.|....\n.|....\n======\n", // .|..|. .|..|. .|..|. .|..|. .|..|. .|..|. .|..|.
		".----.\n.|..|.\n.|..o.\n.|./|\\\n.|....\n.|....\n.|....\n======\n",  // .|..o. .|..o. .|..o. .|..o. .|..o. .|..o. .|....
		".----.\n.|..|.\n.|..o.\n.|..|\\\n.|....\n.|....\n.|....\n======\n",  // .|./|\ .|./|\ .|./|\ .|..|\ .|..|. .|.... .|....
		".----.\n.|..|.\n.|..o.\n.|..|.\n.|....\n.|....\n.|....\n======\n",   // .|./.\ .|...\ .|.... .|.... .|.... .|.... .|....
		".----.\n.|..|.\n.|..o.\n.|....\n.|....\n.|....\n.|....\n======\n",   // .|.... .|.... .|.... .|.... .|.... .|.... .|....
		".----.\n.|..|.\n.|....\n.|....\n.|....\n.|....\n.|....\n======\n"    // .|.... .|.... .|.... .|.... .|.... .|.... .|....
	};                                                                        // ====== ====== ====== ====== ====== ====== ======
	return ascii.at(lives);
}


Secret::Secret() {
	setWord("foo");
	setLives(6);
}

Secret::Secret(std::vector<string> words) : Secret() {
	setWord(words.at(rand() % (words.size())));
}

int Secret::getLives() {
	return lives;
}

bool Secret::guess(char ch) {
	if (isGuessedLetter(ch)) {
		return -1; //error if already guessed char
	}
	int correct = 0;
	if (correct == 0) {
		modLives(-1);
	}
	return correct;
}

bool Secret::isGuessedLetter(char guessCh) {
	for (char ch : guessedLetters) {
		if (ch == guessCh) {
			return true;
		}
	}
	return false;
}

void Secret::setWord(string word) {
	wordTarget = word;
	wordDisplay = "";
	for (char ch : word) {
		wordDisplay += '_';
	}
}

void Secret::setLives(int newLives) {
	lives = newLives;
}

void Secret::modLives(int delta) {
	lives += delta;
}

string Secret::getWord(bool hidden) {
	return (hidden) ? wordTarget : wordDisplay;
}

void Secret::print() {
	using std::cout;
	//print lives
	cout << getLives() << " lives remain.\n";
	cout << lifeDisplay(getLives());
	//TODO print ascii hangman
	//print guess progress
	//print guessed letters
}

int Secret::getLetterQty(char) {
	return 0;
}