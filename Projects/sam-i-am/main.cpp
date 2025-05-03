#include <iostream>
#include "../include/sam_utils.h"
#include "../include/Actor.h"
#include "../include/Game.h"
#include "../include/sam_io.h"
#include "../include/scanner.h"

int main() {
    const std::vector<char> scenario = { //placeholder to demonstrate save/load
        10, //validator
        3, //static count
        0, 26, 22, //player
        2, 23, 18, //city 1
        2, 30, 18, //city 2
        8, //mobile count
        2, 0, 7, 27, 10, //fighter kills interdictor turn 2
        1, 1, 2, 11, 18, //interdictor kills city 1 turn 3
        1, 0, 4, 30, 28, //bomber kills city 2 turn 5
        1, 0, 4, 23, 28, //bomber kills city 1 turn 5
        1, 1, 6, 46, 18, //interdictor kills city 2 turn 4
        1, 3, 0, 32, 12, //command
        0, 1, 6, 31, 19, //cropduster
        0, 2, 3, 15, 28, //concorde
        -10 //exit validator
    };
    const std::string filename = "demo2.bin";
    if (!SAM::writeScenario(filename, scenario)) { //save scenario to binary
        throw std::runtime_error("write error");
    }
    std::vector<char> blob;
    if (!SAM::readScenario(filename, blob)) { //load saved scenario binary
        throw std::runtime_error("read error");
    }

    SAM::Game game;
    srand((unsigned int)time(nullptr)); //RNG seeded

    game.loadScenario(blob); //scenario loaded

    std::string title = "SAM-I-AM v1";
    Status status = Running;

    while (status == Running) {
        std::string options = "[I]dentify   [S]hoot   [Q]uit";
        SAM::printUI(title, game.drawBoard(), game.listContacts(game.getUnitList()), options);
        std::cout << "\nAction? ";
        char input = std::tolower(getNextLineAlpha()[0]);
        //decision tree
        if (input == 'i') { //identify
            std::vector<SharedActor> unknowns = game.getUnidentified();
            if (unknowns.empty()) {
                std::cout << "Nothing to identify this turn.\n";
            }
            else {
                std::cout << "\nUnidentified contacts:\n";
                for (auto& a : unknowns) {
                    if (!a) {
                        continue;
                    }
                    std::cout << "  [" << a->getMapIcon() << "] " << a->toString(game.getPlayerPos()) << '\n';
                }
                std::cout << "Pick a contact: ";
                char icon = std::tolower(getNextLineAlpha()[0]);
                for (auto& a : unknowns)
                    if (a && std::tolower(a->getMapIcon()) == icon) {
                        game.identify(a);
                        break;
                    }
            }
        }
        else if (input == 's') { //shoot
            std::vector<SharedActor> targets;
            for (Coord c : game.getUnitList()) {
                auto& cell = game.getCell(c.x, c.y);
                if (cell && cell->getActorType() == Mobile) {
                    targets.push_back(cell);
                }
            }
            if (targets.empty()) {
                std::cout << "No enemy contacts.\n";
            }
            else {
                std::cout << "\nEnemy contacts:\n";
                for (auto& a : targets) {
                    std::cout << "  [" << a->getMapIcon() << "] " << a->toString(game.getPlayerPos()) << '\n';
                }
                std::cout << "Pick a target: ";
                char icon = std::tolower(getNextLineAlpha()[0]);
                for (auto& a : targets)
                    if (std::tolower(a->getMapIcon()) == icon) {
                        game.launchMissile(a);
                        break;
                    }
            }
        }
        else if (input == 'q') { //quit
            return 0;

        }
        else {
            std::cout << "Invalid choice\n";
            continue;
        }

        game.tickMissiles(); //move missiles
        game.moveAllUnits(game.getUnitList()); //move units

        //check gamestate
        bool playerAlive = false;
        bool anyCityAlive = false;
        bool anyEnemyAlive = false;
        for (Coord c : game.getUnitList()) {
            auto cell = game.getCell(c.x, c.y);
            if (!cell) {
                continue;
            }
            if (cell->getActorType() == Player) {
                playerAlive = true;
            }
            if (cell->getActorType() == City) {
                anyCityAlive = true;
            }
            if (cell->getFaction() == Enemy) {
                anyEnemyAlive = true;
            }
        }
        if (!playerAlive || !anyCityAlive) {
            status = Lost;
        }
        else if (!anyEnemyAlive) {
            status = Win;
        }
    }
	SAM::printUI("GAME OVER!", game.drawBoard(), game.listContacts(game.getUnitList()), "");
	std::cout << ((game.getStatus() == Win) ? "You win!\n" : "You lose!\n");
	SAM::writeLogs("session.log", game.getLogs());
	return 0;
}