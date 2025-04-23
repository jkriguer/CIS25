#include "sam_utils.h" //header

#include <iostream> //cout

int getContactNumber() {
	static int count = 0;
	return count++;
}

void printBoard(const SharedBoard& board) {
    for (const auto& row : *board) {
        for (const auto& cell : row) {
            if (cell) {
                std::cout << '*';
            }
            else {
                std::cout << '.';
            }
            std::cout << ' ';
        }
        std::cout << '\n';
    }
}