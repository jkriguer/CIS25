#include "../include/sam_utils.h"
#include "../include/Actor.h"
#include <iostream> 
#include <unordered_map>

namespace SAM {

    const std::vector<char> defaultScenario {
    10,//validator
    3, //static count
    2, 23, 18, //city 1
    0, 26, 22, //player
    2, 30, 18, //city 2
    5, //mobile count
    2, 1, 0, 26, 1, //friendly 1
    0, -1, 3, 49, 20, //neutral 2
    1, 1, 0, 16, 10, //hostile 1
    2, 1, 0, 25, 2, //friendly 2
    0, -1, 1, 10, 10, //neutral 1
    -10 //exit validator
    };


    char getNewContactNumber() {
        static int count = 0;
        return '0' + (count++ % 10);
    }

    AircraftParams getArchetype(Faction f, int index) {
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



    void printUI(std::string titleState, std::vector<std::string> visualDisplay, std::vector<std::string> contacts, std::string options) {
        using std::cout;
        int contactsPrinted = 0;
        cout << titleState << '\n';
        for (int i = 0; i < visualDisplay.size(); i++) {
            cout << visualDisplay[i];
            switch (i) {
                case 0:
                    cout << "   N";
                    break;
                case 1:
                    cout << " W   E";
                    break;
                case 2:
                    cout << "   S";
                    break;
                case 3:
                    cout << "line 3 test";
                    break;
                case 4:
                    cout << options;
                    break;
                default:
                    if (i >= 7 && contactsPrinted < contacts.size()) { //start printing from line 7 on
                        cout << contacts.at(contactsPrinted++);
                    }
            }
            cout << '\n';
        }
    }

    Coord getBearingMods(Bearing b) { //conceals ugly switching logic
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

    std::string bearingToStr(Bearing b) {
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

    std::string factionToStr(Faction F) {
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

    void clearTerm() {
        printf("\033c"); //better than using defs to decide to system(clear)/system(cls)
    }
}