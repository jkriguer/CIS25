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

Aircraft SAMUTIL::getArchetype(Faction f) {
    const int SPD_SLOW = 1, SPD_MED = 2, SPD_FAST = 4;
    const std::unordered_map<Faction, std::vector<Aircraft>> archetypes {
        { Faction::FRIENDLY, {
            {"Fighter", SPD_FAST, true, true},
            {"Interceptor", SPD_FAST, false, true}
        }},
        { Faction::HOSTILE, {
            {"Bomber", SPD_MED, false, true},
            {"Interdictor", SPD_FAST, true, true},
            {"Attacker", SPD_SLOW, true, true},
            {"Command", SPD_MED, false}
        }},
        { Faction::NEUTRAL, {
            {"Airliner", SPD_MED, false},
            {"Cropduster", SPD_SLOW, true},
            {"Concorde", SPD_FAST, false}
        }}
    };

    const auto& vec = archetypes.at(f);
    return vec.at(rand() % vec.size());
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

std::string SAMUTIL::bearingToStr(Bearing b) {
    switch (b) {
        case Bearing::N:
            return "N";
        case Bearing::E:
            return "E";
        case Bearing::S:
            return "S";
        case Bearing::W:
            return "W";
        case Bearing::NW:
            return "NW";
        case Bearing::NE:
            return "NE";
        case Bearing::SE:
            return "SE";
        case Bearing::SW:
            return "SW";
        default:
            return "??";
    }
}

std::string SAMUTIL::factionToStr(Faction F) {
    switch (F) {
        case Faction::FRIENDLY:
            return "Friendly";
        case Faction::HOSTILE:
            return "Hostile";
        case Faction::NEUTRAL:
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