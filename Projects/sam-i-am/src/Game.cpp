#include "../include/Game.h"
#include "../include/sam_utils.h"
#include "../include/sam_io.h"
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

SharedActor& SAM::Game::getCell(int x, int y) {
    return (board).at(y).at(x);
}

void SAM::Game::setCell(int x, int y, SharedActor a) {
    getCell(x, y) = std::move(a);
}

void SAM::Game::moveAllUnits(const std::vector<Coord>& units) {
    std::vector<Coord> enemy, friendly, neutral;
    for (const Coord& c : units) { //sort units by faction
        if (getCell(c.x, c.y)->getActorType() == ActorType::Mobile) {
            switch (getCell(c.x, c.y)->getFaction()) {
                case Enemy:
                    enemy.push_back(c);
                    break;
                case Friendly:
                    friendly.push_back(c);
                    break;
                case Neutral:
                    neutral.push_back(c);
                    break;
            }
        }
    }
    moveUnits(enemy);
    moveUnits(friendly);
    moveUnits(neutral);
}

void SAM::Game::moveUnits(const std::vector<Coord>& units) {
    for (const Coord& c : units) { //actually move units
        getCell(c.x, c.y)->move(*this);
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
    setCell(x, y, std::make_shared<Actor>(aT, label, c));
    getCell(x, y)->setActorCoords({x, y});
    return true; //success
}

bool SAM::Game::makeAndPlace(Faction f, AircraftParams role, Bearing b, int x, int y) {
    if (getCell(x, y)) { //fail if cell occupied
        return false;
    }
    setCell(x, y, std::make_shared<Actor>(f, role, b));
    getCell(x, y)->setActorCoords({x, y});
    return true; //success
}

Status SAM::Game::getStatus() {
    return this->status;
}

bool SAM::Game::loadScenario(const std::vector<char>& s) {
    if (s[0] != SAM::SAVE_VERSION || s[s.size() - 1] != -SAM::SAVE_VERSION) { //check validators 
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
        if (type == Player) {
            this->playerPos = Coord(x, y);
        }
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

void SAM::Game::log(std::string l) {
    logs.push_back(l);
}

bool SAM::Game::launchMissile(const SharedActor& tgt) {
    if (!tgt) { //fail if tgt absent/destroyed
        return false;
    }
    missiles.push_back({ tgt, this->DELAY, this->RANGE });
    logs.push_back("Launched on " + tgt->toString() + 
        ", impact in " + std::to_string(this->DELAY) + " turns.");
    return true;
}

void SAM::Game::tickMissiles() {
    for (int i = missiles.size() - 1; i >= 0; i--) { //work back to front
        Missile& m = missiles[i];
        SharedActor tgt = m.target.lock();
        if (!tgt) { //fail if tgt absent/destroyed
            logs.push_back("Missile lost guidance and was destroyed.");
            missiles.erase(missiles.begin() + i);
            continue; //next missile
        }

        if (--m.turnsToImpact != 0) { //tick down, check for impact
            continue; //next missile
        }

        Coord tgtC = tgt->getCoords();
        if (SAM::manhattan(playerPos, tgtC) < m.maxRange) { //if in range
            logs.push_back("Missile hit: " + tgt->toString() + " destroyed.");
            getCell(tgtC.x, tgtC.y).reset(); //destroyed
        }
        else { //target left range
            logs.push_back("Missile missed: " + tgt->toString() + " evaded.");
        }
        missiles.erase(missiles.begin() + i);
    }
}

std::vector<WeakActor> SAM::Game::getMobilePtrs() {
    std::vector<WeakActor> out;
    for (Coord c : getUnitList()) {
        SharedActor& cell = getCell(c.x, c.y);
        if (cell && cell->getActorType() == Mobile) {
            out.push_back(cell);
        }
    }
    return out;
}