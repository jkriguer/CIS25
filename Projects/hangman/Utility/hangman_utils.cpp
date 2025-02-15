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
		if (words[i] == ' ') { //larger space on space between words
			output += "   ";
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

void drawBoard(int lives, std::string message, std::string words, std::vector<char> guessed) {
	using std::cout;

	clear(); //clear terminal
	for (int i = 0; i <= 7; i++) {
		cout << std::setw(30) << std::left << pictogram(i, lives);
		switch (i) {//individual line behaviors
			case 1://print feedback to user
				cout << message;
				break;
			case 3://print guess progress
				cout << displayWords(words, guessed);
				break;
			case 5://print guessed letters
				if (guessed.size() > 0) {
					sortVecChars(guessed);
					cout << "Already guessed letters: " << listChars(guessed);
				}
				break;
			case 7://print lives remaining (maybe)
				cout << "Lives remaining: " << lives - 1;
		}
		cout << '\n';
	}
	cout << "\n\n";
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

char getValidLetter(std::vector<char> guessed) {
	using std::cout;
	std::string input;
	while (true) {
		cout << "Enter a letter: ";
		std::getline(std::cin, input);
		if (!input.empty()) { //check if input was provided
			if (isAlpha(input[0])) {
				//cout << "Input: " << toLower(input[0]);
				if (charInVec(input[0], guessed)) {
					cout << "You already entered " << toLower(input[0]) << "!\n";
					continue;
				}
				return toLower(input[0]);
			}
		}
		cout << "That wasn't valid. ";
	}
}

int lettersLeftToGuess(std::string words, std::vector<char> guessed) {
	std::vector<char> unique;
	for (char ch : words) { //make a vec of all unique letters in str
		if (isAlpha(ch) && !charInVec(ch, unique)){
			unique.push_back(ch);
		}
	}
	int correctLetters = 0;
	for (int i = 0; i < unique.size(); i++) {
		for (int j = 0; j < guessed.size(); j++) {
			if (unique.at(i) == guessed.at(j)) {
				correctLetters++;
				break;
			}
		}
	}
	return unique.size() - correctLetters;
}

std::string pictogram(int line, int lives) { //just trust me that it works. it could theoretically be deduped but...
	if (lives > 7 || lives < 0) { 
		lives = (lives < 0) ? 0 : 7; //clamp if either var is out of bounds
	}
	if (line > 7 || line < 0) {
		line = (line < 0) ? 0 : 7;
	}
	std::string ascii[] { //horrific ascii art blob, genuinely inscrutable
		"  .========.", "  || /", "  ||/", "  ||", "  ||", "  ||", "=========-----====", "||              ||", 
		"  .========.", "  || /    _|_", "  ||/    (o_o)", "  ||", "  ||", "  ||", "=========-----====", "||              ||", 
		"  .========.", "  || /    _|_", "  ||/    (o_o)", "  ||      | |", "  ||      |_|", "  ||", "=========-----====", "||              ||", 
		"  .========.", "  || /    _|_", "  ||/    (o_o)", "  ||     /| |", "  ||    ^ |_|", "  ||", "=========-----====", "||              ||", 
		"  .========.", "  || /    _|_", "  ||/    (o_o)", "  ||     /| |\\", "  ||    ^ |_| ^", "  ||", "=========-----====", "||              ||", 
		"  .========.", "  || /    _|_", "  ||/    (o_o)", "  ||     /| |\\", "  ||    ^ |_| ^", "  ||      /", "=========-----====", "||              ||", 
		"  .========.", "  || /    _|_", "  ||/    (o_o)", "  ||     /| |\\", "  ||    ^ |_| ^", "  ||      / \\", "=========-----====", "||              ||", 
		"  .========.", "  || /     |", "  ||/     _|_", "  ||     (x_x)", "  ||     /| |\\", "  ||    ^ |_| ^", "========= / \\ ====", "||              ||"
	};
	return ascii[((7 - lives) * 8) + line];
}