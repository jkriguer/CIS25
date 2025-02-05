#include "Secret.h"

Secret::Secret() {
	setWord("secretword");
	setLives(100);
}
Secret::Secret(vector<string> words) : Secret() {
	setWord(words.at(rand() % (words.size())));
}
int Secret::getLives() {
	return lives;
}
int Secret::guess(char ch) {
	int correct = 0;
	for (char vecCh : wordTarget) {
		if (vecCh == ch) {
			correct++;
		}
	}
	return correct;
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