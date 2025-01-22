// swapper.cpp: this program swaps two variables for git demonstration
// Jasper Kriguer 10886327

#include <iostream>

int main() {
	int x = 1, y = 2;
	std::cout << "X = " << x << ", Y = " << y << '\n';
	int temp = x;
	x = y;
	y = temp;
	std::cout << "X = " << x << ", Y = " << y << '\n';
}

/*
* OUTPUT
X = 1, Y = 2
X = 2, Y = 1

*/