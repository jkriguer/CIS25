#include "sam_utils.h" 

#include <iostream> 
#include <unordered_map>
#include "Actor.h"

namespace SAM {

    SharedBoard board;

    void initBoard(int x, int y) {
        board = std::make_shared<Board>(y);
        for (auto& row : *board) { //avoid copying unique pointers this way
            row.resize(x);
        }
    }

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

    std::vector<std::string> drawBoard() {
        std::vector<std::string> output;
        int x = (*board)[0].size();
        int y = (*board).size();

        for (int i = y - 1; i >= 0; i--) {
            std::string line = "";
            line += (i + 1 < 10 ? " " : "") + std::to_string(i + 1) + ' ';
            for (int j = 0; j < x; j++) {
                if ((*board)[i][j]) {
                    line += getCell(j, i)->getMapIcon();
                }
                else {
                    line += '.';
                }
                line += ' ';
            }
            output.push_back(line);
        }
        std::string xAxisTen = "   ";
        std::string xAxisOne = "   ";
        for (int i = 1; i <= x; i++) {
            xAxisTen += std::to_string(i / 10) + ' ';
            xAxisOne += std::to_string(i % 10) + ' ';
        }
        output.push_back(xAxisTen);
        output.push_back(xAxisOne);
        return output;
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

    std::pair<int, int> getBearingMods(Bearing b) { //conceals ugly switching logic
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

    std::vector<std::pair<int, int>> getUnitList() {
        int x = (*board)[0].size();
        int y = (*board).size();

        std::vector<std::pair<int, int>> output;
        for (int i = 0; i < x; i++) {
            for (int j = 0; j < y; j++) {
                if (getCell(i, j)) {
                    output.push_back({ i, j });
                }
            }
        }
        return output;
    }

    bool makeAndPlace(ActorType aT, std::string label, char c, int x, int y) {
        if (getCell(x, y)) { //fail if cell occupied
            return false;
        }
        setCell(x, y, std::make_unique<Actor>(aT,label, c));
        getCell(x, y)->setCoords(x, y);
        return true; //success
    }

    bool makeAndPlace(AircraftParams role, Bearing b, int x, int y) {
        if (getCell(x, y)) { //fail if cell occupied
            return false;
        }
        setCell(x, y, std::make_unique<Actor>(role, b));
        getCell(x, y)->setCoords(x, y);
        return true; //success
    }

    void clear() {
        printf("\033c"); //better than using defs to decide to system(clear)/system(cls)
    }

    std::unique_ptr<Actor>& getCell(int x, int y) {
        return (*board)[y][x];
    }

    void setCell(int x, int y, std::unique_ptr<Actor> a) {
        getCell(x, y) = std::move(a);
    }

    void moveUnits(std::vector<std::pair<int, int>> units) {
        for (const auto& [x, y] : units) {
            if (getCell(x, y)->getActorType() == ActorType::Mobile) {
                getCell(x, y)->move();
                std::cout << "Debug: moved unit at " << x << ", " << y << '\n';
            }
        }
    }

    std::vector<std::string> listContacts(std::vector<std::pair<int, int>> units) {
        std::vector<std::string> output{ "Contacts:" };
        for (const auto& [x, y] : units) {
            output.push_back(getCell(x, y)->toString());
        }
        return output;
    }
}