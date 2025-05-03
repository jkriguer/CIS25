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
        bool turn = true; //has player taken their turn?

        std::vector<SharedActor> contacts, filtered;
        for (Coord c : game.getUnitList()) { //populate list of contacts
            auto& cell = game.getCell(c.x, c.y);
            if (cell) {
                contacts.push_back(cell);
            }
        }

        SAM::sortContactsByDistance(contacts, game.getPlayerPos()); //sort list of contacts
        SAM::printUI(title, game.drawBoard(), game.listContacts(game.getUnitList())); //draw UI
        std::cout << "\n[I]dentify   [S]hoot   [Q]uit\nEnter an action:  ";
        char input = std::tolower(getNextLineAlpha()[0]);

        //decision tree
        if (input == 'i') { //identify
            for (auto& contact : contacts) { //split off unidentified actors
                if (contact->getID() > 0) {
                    filtered.push_back(contact);
                }
            }
            if (filtered.empty()) {
                std::cout << "Nothing to identify this turn.\n";
            }
            else {
                std::cout << "\nUnidentified contacts:\n";
                for (int i = 0; i < filtered.size(); i++) {
                    std::cout << " [" << i + 1 << "] " << contacts[i]->toString(game.getPlayerPos()) << '\n';
                }
                std::cout << "Pick a contact [#]: ";
                int choice = getNextInt();
                if (choice >= 1 && choice <= filtered.size()) {
                    game.identify(filtered[choice - 1]);
                    turn = true;
                }
            }
        }
        else if (input == 's') { //shoot
            for (auto& contact : contacts) { //split off mobiles
                if (contact->getActorType() == Mobile) {
                    filtered.push_back(contact);
                }
            }
            if (filtered.empty()) {
                std::cout << "No enemy contacts.\n";
            }
            else {
                std::cout << "\nEnemy contacts:\n";
                for (int i = 0; i < filtered.size(); i++) {
                    std::cout << " [" << i + 1 << "] " << filtered[i]->toString(game.getPlayerPos()) << '\n';
                }
                std::cout << "Pick a contact [#]: ";
                int choice = getNextInt();
                if (choice >= 1 && choice <= filtered.size()) {
                    game.launchMissile(filtered[choice - 1]);
                    turn = true;
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

        if (turn) { //check gamestate if player turn has ended
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
    }
	SAM::printUI("GAME OVER!", game.drawBoard(), game.listContacts(game.getUnitList()));
	std::cout << ((game.getStatus() == Win) ? "You win!\n" : "You lose!\n");
	SAM::writeLogs("session.log", game.getLogs());
	return 0;
}