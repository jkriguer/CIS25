#include "../include/Game.h"
#include <iostream>

SAM::Game::Game() {
    board = Board(DIM_Y); //initialize board
    for (auto& row : board) { //avoid copying unique pointers this way
        row.resize(DIM_X);
    }
    status = Running; //start game
}

SAM::Game::Game(Scenario) {
    //TODO
};

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

void SAM::Game::moveUnits(std::vector<std::pair<int, int>> units) {
    for (const auto& [x, y] : units) {
        if (getCell(x, y)->getActorType() == ActorType::Mobile) {
            getCell(x, y)->move(*this);
            std::cout << "Debug: moved unit at " << x << ", " << y << '\n';
        }
    }
}

std::vector<std::string> SAM::Game::listContacts(std::vector<std::pair<int, int>> units) {
    std::vector<std::string> output{ "Contacts:" };
    for (const auto& [x, y] : units) {
        output.push_back(getCell(x, y)->toString());
    }
    return output;
}

std::vector<std::pair<int, int>> SAM::Game::getUnitList() {
    std::vector<std::pair<int, int>> output;
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
    getCell(x, y)->setCoords(x, y);
    return true; //success
}

bool SAM::Game::makeAndPlace(AircraftParams role, Bearing b, int x, int y) {
    if (getCell(x, y)) { //fail if cell occupied
        return false;
    }
    setCell(x, y, std::make_unique<Actor>(role, b));
    getCell(x, y)->setCoords(x, y);
    return true; //success
}