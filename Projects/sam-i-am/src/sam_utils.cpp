#include "../include/sam_utils.h"
#include "../include/Actor.h"
#include <iostream> 
#include <unordered_map>

char SAM::getNewContactNumber() {
    static int count = 0;
    return '0' + (count++ % 10);
}

AircraftParams SAM::getArchetype(Faction f, int index) {
    const int SPD_SLOW = 1, SPD_MED = 2, SPD_FAST = 4;
    const std::unordered_map<Faction, std::vector<AircraftParams>> archetypes{
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



void SAM::printUI(const std::string& title, const std::vector<std::string>& mapRows, const std::vector<std::string>& contacts) {
    clearTerm(); //cls
    std::cout << title << '\n';

    int index = 0; //contacts index
    for (int i = 0; i < mapRows.size(); i++) {
        std::cout << mapRows[i];

        if (i == 0) {
            std::cout << "   N";
        }
        if (i == 1) {
            std::cout << " W   E";
        }
        if (i == 2) {
            std::cout << "   S";
        }
        if (i >= 5 && index < contacts.size()) {
            std::cout << contacts[index++];
        }
        std::cout << '\n';
    }
}


Coord SAM::getBearingMods(Bearing b) { //conceals ugly switching logic
    switch (b) {
        case Bearing::North:
            return { 0, 1 };
        case Bearing::East:
            return { 1, 0 };
        case Bearing::South:
            return { 0, -1 };
        case Bearing::West:
            return { -1, 0 };
        case Bearing::Northwest:
            return { -1, 1 };
        case Bearing::Northeast:
            return { 1, 1 };
        case Bearing::Southeast:
            return { 1, -1 };
        case Bearing::Southwest:
            return { -1, -1 };
        default:
            return { 0, 0 };
    }
}

std::string SAM::bearingToStr(Bearing b) {
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

std::string SAM::factionToStr(Faction F) {
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

void SAM::clearTerm() {
    printf("\033c"); //better than using defs to decide to system(clear)/system(cls)
}

int SAM::manhattan(Coord src, Coord dst) {
    return std::abs(src.x - dst.x) + std::abs(src.y - dst.y);
}

std::string SAM::coordToStr(Coord c) {
    return "(" + std::to_string(c.x + 1) + ", " + std::to_string(c.y + 1) + ")";
}

void SAM::sortContactsByDistance(std::vector<SharedActor>& vec, Coord c) { //insertion srots vec on manhattan distance
    for (int i = 1; i < vec.size(); i++) {
        auto current = vec[i];
        int currentDist = SAM::manhattan(c, current->getCoords());
        int j = i - 1;
        while (j >= 0 && SAM::manhattan(c, vec[j]->getCoords()) > currentDist) {
            vec[j + 1] = vec[j];
            j--;
        }
        vec[j + 1] = current;
    }
}