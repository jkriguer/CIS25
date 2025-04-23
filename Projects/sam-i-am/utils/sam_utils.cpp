#include "sam_utils.h" //header

#include <iostream> //cout
#include <iomanip> //UI formatting
#include "Actor.h"

int getNewContactNumber() {
	static int count = 0;
	return count++;
}

std::vector<std::string> drawBoard(const SharedBoard& board) {
    std::vector<std::string> output;
    for (const auto& row : *board) {
        std::string line = "";
        for (const auto& cell : row) {
            if (cell) {
                line += std::to_string(cell->getContact());
            }
            else {
                line+= '.';
            }
            line+= ' ';
        }
        output.push_back(line);
    }
    return output;
}

void printUI(std::string titleState, std::vector<std::string> visualDisplay, std::string options) {
    using std::cout;
    cout << titleState << '\n';
    for (int i = 0; i < visualDisplay.size(); i++) {
        cout << visualDisplay[i];
        switch (i) {
            case 0: 
                cout << "line 0 test";
                break;
            case 3: 
                cout << "line 3 test";
                break;
            case 4:
                cout << options;
        }
        cout << '\n';
    }
}