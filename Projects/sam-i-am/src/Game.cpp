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
    std::vector<std::string> output{ "  Name       BRG RNG ALT SPD" };
    for (const Coord& c : units) {
        if (getCell(c.x, c.y)->getActorType() == Mobile) {
            output.push_back(getCell(c.x, c.y)->toString(this->playerPos, true));
        }
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
    if (aT == City) {
        this->cityCount++;
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
    int dist = SAM::manhattan(this->playerPos, tgt->getCoords());
    if (dist <= this->RANGE) {
        logs.push_back("Missile launched at " + tgt->toString(playerPos) + " - Hit!");
        Coord c = tgt->getCoords();
        getCell(c.x, c.y).reset();
        return true;
    }
    logs.push_back("Missile launched at " + tgt->toString(playerPos) + " - evaded.");
    return false;
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

bool SAM::Game::identify(const SharedActor& tgt) {
    if (!tgt) {
        return false;
    }
    bool out = tgt->tickID();
    if (!out) {
        return false;
    }
    if (tgt->getID() == 0) {
        log("ID complete on " + tgt->toString(playerPos));
    }
    else {
        log(std::to_string(tgt->getID()) + " turn(s) until " + tgt->toString(playerPos) + " identified.");
    }
    return true;
}

std::vector<SharedActor> SAM::Game::getUnidentified() {
    std::vector<SharedActor> out;
    for (WeakActor w : getMobilePtrs()) {
        auto s = w.lock();
        if (!s) {
             continue;
        }
        out.push_back(s);
    }
    return out;
}

Coord SAM::Game::getPlayerPos() {
    return this->playerPos;
}

std::vector<std::string> SAM::Game::getLogs() {
    return this->logs;
}

std::string SAM::Game::getLastLog() {
    return this->logs.empty() ? "" : this->logs.back();
}

int SAM::Game::getCityCount() {
    return this->cityCount;
}

int SAM::Game::getRange() {
    return this->RANGE;
}

void SAM::Game::setStatus(Status s) {
    this->status = s;
}
