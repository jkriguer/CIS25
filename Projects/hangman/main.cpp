#include <iostream>
#include <string>
#include <vector>
#include "Secret.h"

using namespace std;

vector<string> words{ "lorem", "ipsum", "dolor", "sit", "amet", "foo", "bar", "baz"};

int checkChar(string, char);
void printBoard(string);

int main() {
	srand((unsigned)time(nullptr));
	Secret word(words);
	cout << word.getWord() << '\n';
	for (char ch = 'a'; ch <= 'z'; ch++) {
		if (checkChar(word.getWord(), ch) > 0) {
			cout << ch << checkChar(word.getWord(), ch) << ' ';
		}
	}
	return 0;
}

void printBoard(string guessed) {
	for (char c : guessed) {
		cout << c << ' ';
	}
	cout << '\n';
}

int checkChar(string word, char input) {
	int numberCorrect = 0;
	for (char ch : word)
		if (ch == input)
			numberCorrect++;
	return numberCorrect;
}