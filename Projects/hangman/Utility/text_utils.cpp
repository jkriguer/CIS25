#include "text_utils.h"

bool isAlpha(char ch) { //returns true if char is an alphabetical character
	return ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z')) ? true : false;
}

bool isAlpha(std::string str) { //returns true if string contains only alphabetical characters
	if (str == "") {
		return false; //catch edge case where empty strings aren't evaluated as nonalpha
	}
	for (char ch : str) {
		if (!isalpha(ch)) {
			return false;
		}
	}
	return true;
}

char toUpper(char ch) { //returns uppercase letter if input is lowercase letter
	return (ch >= 'a' && ch <= 'z') ? ch - ('a' - 'A') : ch;
}

char toLower(char ch) { //returns lowercase letter if input is uppercase letter
	return (ch >= 'A' && ch <= 'Z') ? ch + ('a' - 'A') : ch;
}

std::string lifeDisplay(int lives) {
	std::string asciiArt[]{
		".----.\n.|..|.\n.|..O.\n.|./|\\\n.|./.\\\n.|....\n.|....\n======\n", // .----. .----. .----. .----. .----. .----. .----.
		".----.\n.|..|.\n.|..O.\n.|./|\\\n.|...\\\n.|....\n.|....\n======\n", // .|..|. .|..|. .|..|. .|..|. .|..|. .|..|. .|..|.
		".----.\n.|..|.\n.|..O.\n.|./|\\\n.|....\n.|....\n.|....\n======\n",  // .|..O. .|..O. .|..O. .|..O. .|..O. .|..O. .|....
		".----.\n.|..|.\n.|..O.\n.|..|\\\n.|....\n.|....\n.|....\n======\n",  // .|./|\ .|./|\ .|./|\ .|..|\ .|..|. .|.... .|....
		".----.\n.|..|.\n.|..O.\n.|..|.\n.|....\n.|....\n.|....\n======\n",   // .|./.\ .|...\ .|.... .|.... .|.... .|.... .|....
		".----.\n.|..|.\n.|..O.\n.|....\n.|....\n.|....\n.|....\n======\n",   // .|.... .|.... .|.... .|.... .|.... .|.... .|....
		".----.\n.|..|.\n.|....\n.|....\n.|....\n.|....\n.|....\n======\n"    // .|.... .|.... .|.... .|.... .|.... .|.... .|....
	};
	if (lives > 6 || lives < 0) { //clamp if out of array bounds
		return ((lives > 6) ? asciiArt[6] : asciiArt[0]);
	}
	return asciiArt[lives];
}