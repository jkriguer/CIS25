#include "sam_utils.h" //header

#include <iostream> //cout
#include <iomanip> //UI formatting
#include "Actor.h"

char getNewContactNumber() {
	static int count = 0;
    return '0' + (count++ % 10);
}

std::vector<std::string> drawBoard(const SharedBoard& board) {
    std::vector<std::string> output;
    for (const auto& row : *board) {
        std::string line = "";
        for (const auto& cell : row) {
            if (cell) {
                line += cell->getContact();
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

std::pair<int, int> getBearingMods(Bearing b) { //conceals ugly switching logic
    switch (b) {
        case Bearing::N:
            return { 0, -1 };
        case Bearing::E:
            return { 1, 0 };
        case Bearing::S:
            return { 0, 1 };
        case Bearing::W:
            return { -1, 0 };
        case Bearing::NW:
            return { -1, -1 };
        case Bearing::NE:
            return { 1, -1 };
        case Bearing::SE:
            return { 1, 1 };
        case Bearing::SW:
            return { -1, 1 };
        default:
            return { 0, 0 };
    }
}

std::vector<std::pair<int, int>> getUnitList(const SharedBoard&) {
    std::vector<std::pair<int, int>> output;
    //TODO iterate through and add coord pairs
    return output;
}