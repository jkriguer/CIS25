#include "text_utils.h"

bool isAlpha(char ch) { //returns true if char is an alphabetical character
	return ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z')) ? true : false;
}

bool isAlpha(std::string str) { //returns true if string contains only alphabetical characters
	if (str == "") {
		return false; //catch edge case where empty strings aren't evaluated as nonalpha
	}
	for (char ch : str) {
		if (!isAlpha(ch)) {
			return false;
		}
	}
	return true;
}

char toUpper(char ch) { //returns uppercase letter if input is lowercase letter
	return (ch >= 'a' && ch <= 'z') ? ch - ('a' - 'A') : ch;
}

std::string toUpper(std::string str) {
	for (int i = 0; i < str.length(); i++) {
		str[i] = toUpper(str[i]);
	}
	return str;
}

char toLower(char ch) { //returns lowercase letter if input is uppercase letter
	return (ch >= 'A' && ch <= 'Z') ? ch + ('a' - 'A') : ch;
}

std::string toLower(std::string str) {
	for (int i = 0; i < str.length(); i++) {
		str[i] = toLower(str[i]);
	}
	return str;
}

void clear() {
	printf("\033c"); //better than using defs to decide to system(clear)/system(cls)
}