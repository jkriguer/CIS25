#include "../include/Game.h"
#include "../include/sam_utils.h"
#include <iostream>

SAM::Game::Game() {
    board = Board(DIM_Y); //initialize board
    for (auto& row : board) { //avoid copying unique pointers this way
        row.resize(DIM_X);
    }
    status = Running; //start game
}

int SAM::Game::getWidth() {
    return DIM_X;
}
int SAM::Game::getHeight() {
    return DIM_Y;
}

bool SAM::Game::inBounds(int x, int y) {
    return x >= 0 && x < DIM_X && y >= 0 && y < DIM_Y;
}

std::vector<std::string> SAM::Game::drawBoard() {
    std::vector<std::string> output;
    int x = (board)[0].size();
    int y = (board).size();

    for (int i = y - 1; i >= 0; i--) {
        std::string line = "";
        line += (i + 1 < 10 ? " " : "") + std::to_string(i + 1) + ' ';
        for (int j = 0; j < x; j++) {
            if ((board)[i][j]) {
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

std::unique_ptr<Actor>& SAM::Game::getCell(int x, int y) {
    return (board).at(y).at(x);
}

void SAM::Game::setCell(int x, int y, std::unique_ptr<Actor> a) {
    getCell(x, y) = std::move(a);
}

void SAM::Game::moveUnits(const std::vector<Coord>& units) {
    for (const Coord& c : units) {
        if (getCell(c.x, c.y)->getActorType() == ActorType::Mobile) {
            getCell(c.x, c.y)->move(*this);
            std::cout << "Debug: moved unit at " << c.x << ", " << c.y << '\n';
        }
    }
}

std::vector<std::string> SAM::Game::listContacts(const std::vector<Coord>& units) {
    std::vector<std::string> output{ "Contacts:" };
    for (const Coord& c : units) {
        output.push_back(getCell(c.x, c.y)->toString());
    }
    return output;
}

std::vector<Coord> SAM::Game::getUnitList() {
    std::vector<Coord> output;
    for (int i = 0; i < DIM_X; i++) {
        for (int j = 0; j < DIM_Y; j++) {
            if (getCell(i, j)) {
                output.push_back({ i, j });
            }
        }
    }
    return output;
}

bool SAM::Game::makeAndPlace(ActorType aT, std::string label, char c, int x, int y) {
    if (getCell(x, y)) { //fail if cell occupied
        return false;
    }
    setCell(x, y, std::make_unique<Actor>(aT, label, c));
    getCell(x, y)->setActorCoords({x, y});
    return true; //success
}

bool SAM::Game::makeAndPlace(Faction f, AircraftParams role, Bearing b, int x, int y) {
    if (getCell(x, y)) { //fail if cell occupied
        return false;
    }
    setCell(x, y, std::make_unique<Actor>(f, role, b));
    getCell(x, y)->setActorCoords({x, y});
    return true; //success
}

Status SAM::Game::getStatus() {
    return this->status;
}

bool SAM::Game::loadScenario(const std::vector<char>& s) {
    if (s[0] != SAVE_VERSION || s[s.size() - 1] != -SAVE_VERSION) { //check validators 
        throw std::runtime_error("Illegal scenario: invalid validator(s)");
        return false;
    }
    int index = 0; //read head
    index++; //skip validator
    int fixedCount = s[index++]; //number of fixed actors
    int nextCity = 1; //city label iterator
    for (int i = 0; i < fixedCount; i++) {
        ActorType type = ActorType(s[index++]);
        int x = s[index++];
        int y = s[index++];
        std::string label = (type == Player) ? "Battery" : "City " + std::to_string(nextCity++);
        makeAndPlace(type, label, label[0], x, y);
    }
    if (nextCity == 1 || nextCity > fixedCount) { //if all fixed actors are cities or none of them are
        throw std::runtime_error("Illegal scenario: player or cities not placed");
    }
    int mobileCount = s[index++];
    for (int i = 0; i < mobileCount; i++) {
        Faction f = (Faction)s[index++];
        int archetype = s[index++]; //archetype lookup index
        Bearing b = (Bearing)s[index++];
        int x = s[index++];
        int y = s[index++];
        makeAndPlace(f, getArchetype(f, archetype), b, x, y);
    }
    return true;
}