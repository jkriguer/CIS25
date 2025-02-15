#include "hangman_utils.h"

int populateWordList(std::vector<std::string>& vec) { //generate word list vector from file
	std::ifstream inputFile;
	std::string inputWord;
	inputFile.open("wordlist.txt"); //file handle opened
	if (!inputFile.is_open()) { //error if file can't be opened
		return -10;
	}
	int invalidWordCount = 0;
	while (std::getline(inputFile, inputWord)) {
		if (isAlpha(inputWord)) { //store only words that are alpha only
			vec.push_back(inputWord);
		}
		else {
			invalidWordCount++; //count number of invalid words
		}
	}
	std::cout << "Debug: " << vec.size() << " words added.\n";
	inputFile.close(); //file handle closed
	if (vec.size() <= 1) {
		return  (-11 - vec.size()); //-11 if empty, -12 if only one word
	}
	if (invalidWordCount > 0) {
		std::cout << "Warning: " << invalidWordCount << " word(s) invalid. You might still be able to play.\n";
	}
	return 0;
}

std::string lifeDisplay(int lives) {
	std::string asciiArt[]{                                                   //   0      1      2      3      4      5      6
		".----.\n.|..|.\n.|..O.\n.|./|\\\n.|./.\\\n.|....\n.|....\n======\n", // .----. .----. .----. .----. .----. .----. .----.
		".----.\n.|..|.\n.|..O.\n.|./|\\\n.|...\\\n.|....\n.|....\n======\n", // .|..|. .|..|. .|..|. .|..|. .|..|. .|..|. .|..|.
		".----.\n.|..|.\n.|..O.\n.|./|\\\n.|....\n.|....\n.|....\n======\n",  // .|..O. .|..O. .|..O. .|..O. .|..O. .|..O. .|....
		".----.\n.|..|.\n.|..O.\n.|..|\\\n.|....\n.|....\n.|....\n======\n",  // .|./|\ .|./|\ .|./|\ .|..|\ .|..|. .|.... .|....
		".----.\n.|..|.\n.|..O.\n.|..|.\n.|....\n.|....\n.|....\n======\n",   // .|./.\ .|...\ .|.... .|.... .|.... .|.... .|....
		".----.\n.|..|.\n.|..O.\n.|....\n.|....\n.|....\n.|....\n======\n",   // .|.... .|.... .|.... .|.... .|.... .|.... .|....
		".----.\n.|..|.\n.|....\n.|....\n.|....\n.|....\n.|....\n======\n"    // .|.... .|.... .|.... .|.... .|.... .|.... .|....
	};
	if (lives > 6 || lives < 0) { //clamp if lives out of array bounds
		return ((lives > 6) ? asciiArt[6] : asciiArt[0]);
	}
	return asciiArt[lives];
}

void sortVecChars(std::vector<char>& vec) {
	for (int i = 1; i < vec.size(); i++) { //hooray for merge sort!
		char ch = vec.at(i);
		int j = i - 1;
		while (j >= 0 && vec.at(j) > ch) {
			vec.at(j + 1) = vec.at(j);
			j--;
		}
		vec.at(j + 1) = ch;
	}
}

std::string listVecChars(std::vector<char> vec) {
	std::string output = "";
	for (int i = 0; i < vec.size(); i++) {
		output += vec.at(i);
		if (i < vec.size() - 1) {
			output += ", ";
		}
	}
	return output;
}

bool charInVec(char ch, std::vector<char> vec) {
	for (int i = 0; i < vec.size(); i++) {
		if (ch == vec.at(i)) {
			return true;
		}
	}
	return false;
}

std::string displayWords(std::string words, std::vector<char> guessed) {
	std::string output = "";
	for (int i = 0; i < words.length(); i++) {
		if (words[i] == ' ') { //linebreak on space between words
			output += '\n';
		}
		else if (charInVec(words[i], guessed)) { //print letter if guessed
			output += words[i];
		}
		else { // print underscore if not guessed yet
			output += '_';
		}
	}
	return output;
}

void drawBoard(int lives, std::string words, std::vector<char> guessed) {
	using std::cout;

	clear(); //clear terminal
	cout << lifeDisplay(lives) << '\n'; //ascii art of hangman
	cout << displayWords(words, guessed) << '\n'; //show guessed letters
}

std::string pickFromVec(std::vector<std::string> vec, int numWords) {
	std::string output;
	srand((unsigned)time(nullptr)); //PRNG seeded
	for (int i = 0; i < numWords; i++) {
		int roll = rand() % vec.size();
		output += vec.at(roll); //pop rolled word into string
		vec.erase(vec.begin() + roll);
		if (i < numWords - 1) { //use spaces to delineate words
			output += ' ';
		}
	}
	return output;
}