#include "sam_utils.h" //header

#include <iostream> //cout
#include <iomanip> //UI formatting
#include <unordered_map> //aircraft roles
#include "Actor.h"

using namespace SAMUTIL;

char SAMUTIL::getNewContactNumber() {
    static int count = 0;
    return '0' + (count++ % 10);
}

Aircraft SAMUTIL::getArchetype(Faction f, int index = -1) {
    const int SPD_SLOW = 1, SPD_MED = 2, SPD_FAST = 4;
    const std::unordered_map<Faction, std::vector<Aircraft>> archetypes {
        { Faction::Friendly, {
            {"Fighter", SPD_FAST, true, true},
            {"Interceptor", SPD_FAST, false, true}
        }},
        { Faction::Enemy, {
            {"Bomber", SPD_MED, false, true},
            {"Interdictor", SPD_FAST, true, true},
            {"Attacker", SPD_SLOW, true, true},
            {"Command", SPD_MED, false}
        }},
        { Faction::Neutral, {
            {"Airliner", SPD_MED, false},
            {"Cropduster", SPD_SLOW, true},
            {"Concorde", SPD_FAST, false}
        }}
    };

    const auto& vec = archetypes.at(f);
    if (index >= vec.size()) { //clamp if index too large
        index = vec.size() - 1;
    }
    if (index < 0) { //negative index returns random
        index = rand() % vec.size();
    }
    return vec.at(index);
}

std::vector<std::string> SAMUTIL::drawBoard(const SharedBoard& board) {
    std::vector<std::string> output;
    int x = (*board).size() - 1;
    int y = (*board)[0].size() - 1;

    for (int i = y; i >= 0; i--) {
        std::string line = "";
        line += std::to_string(i % 10) + ' '; //debug
        for (int j = 0; j < x; j++) {
            if ((*board)[j][i]) {
                line += (*board)[j][i]->getContact();
            }
            else {
                line += '.';
            }
            line += ' ';
        }
        output.push_back(line);
    }
    std::string dbgX = "  ";
    for (int i = 0; i < x; i++) {
        dbgX += std::to_string(i % 10) + ' ';
    }
    output.push_back(dbgX);
    return output;
}

void SAMUTIL::printUI(std::string titleState, std::vector<std::string> visualDisplay, std::string options) {
    using std::cout;
    cout << titleState << '\n';
    for (int i = 0; i < visualDisplay.size(); i++) {
        cout << visualDisplay[i];
        switch (i) {
            case 0:
                cout << " <- N ";
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

std::pair<int, int> SAMUTIL::getBearingMods(Bearing b) { //conceals ugly switching logic
    switch (b) {
        case Bearing::North:
            return { 0, -1 };
        case Bearing::East:
            return { 1, 0 };
        case Bearing::South:
            return { 0, 1 };
        case Bearing::West:
            return { -1, 0 };
        case Bearing::Northwest:
            return { -1, -1 };
        case Bearing::Northeast:
            return { 1, -1 };
        case Bearing::Southeast:
            return { 1, 1 };
        case Bearing::Southwest:
            return { -1, 1 };
        default:
            return { 0, 0 };
    }
}

std::string SAMUTIL::bearingToStr(Bearing b) {
    switch (b) {
        case Bearing::North:
            return "N";
        case Bearing::East:
            return "E";
        case Bearing::South:
            return "S";
        case Bearing::West:
            return "W";
        case Bearing::Northwest:
            return "NW";
        case Bearing::Northeast:
            return "NE";
        case Bearing::Southeast:
            return "SE";
        case Bearing::Southwest:
            return "SW";
        default:
            return "??";
    }
}

std::string SAMUTIL::factionToStr(Faction F) {
    switch (F) {
        case Faction::Friendly:
            return "Friendly";
        case Faction::Enemy:
            return "Hostile";
        case Faction::Neutral:
            return "Neutral";
        default:
            return "???";
    }
}

std::vector<std::pair<int, int>> SAMUTIL::getUnitList(const SharedBoard&) {
    std::vector<std::pair<int, int>> output;
    //TODO iterate through and add coord pairs
    return output;
}

void SAMUTIL::clear() {
    printf("\033c"); //better than using defs to decide to system(clear)/system(cls)
}

// too much trouble to get working in this timeframe
//void makeAndPlaceActor(const SharedBoard& b, int x, int y, std::string l, char c) {
//    (*b)[x][y] = std::make_unique<Actor>(b, x, y, l, c);
//}
//
//void makeAndPlaceFlyingActor(SharedBoard& b, int x, int y, std::string l, Faction f, int s, Bearing B, bool fL) {
//    (*b)[y][x] = std::make_unique<FlyingActor>(b, x, y, l, f, s, B, fL);
//}