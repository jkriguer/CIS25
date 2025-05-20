#include <iostream>
#include <filesystem>
#include "../include/sam_utils.h"
#include "../include/Actor.h"
#include "../include/StaticActor.h"
#include "../include/MovingActor.h"
#include "../include/Game.h"
#include "../include/sam_io.h"
#include "../include/scanner.h"

int main() {
    std::string title = "SAM-I-AM v1";
    std::cout << title << "\nFor best results, maximise this terminal window.\n";
    std::vector<std::string> scenarioBinaries;
    for (const auto& file : std::filesystem::directory_iterator(SCENARIOS_DIR)) {
        if (file.path().extension() == ".bin") {
            scenarioBinaries.push_back(file.path().filename().string());
        }
    }
    if (scenarioBinaries.empty()) {
        throw std::runtime_error("No binaries found in scenarios directory.");
    }
    std::cout << "Select a scenario number from below:\n";
    int choice = 0;
    while (choice < 1 || choice > scenarioBinaries.size()) {
        for (int i = 0; i < scenarioBinaries.size(); i++) {
            std::cout << "[" << i + 1 << "] " << scenarioBinaries[i] << '\n';
        }
        choice = getNextInt();
    }

    std::vector<char> blob;
    if (!SAM::readScenario(scenarioBinaries[choice - 1], blob)) { //load saved scenario binary
        throw std::runtime_error("read error");
    }

    SAM::Game game;
    srand((unsigned int)time(nullptr)); //RNG seeded

    game.loadScenario(blob); //scenario loaded

    bool turnComplete = false; //has player taken their turn?
    while (game.getStatus() == Running) {
        if (turnComplete) {
            game.moveAllUnits(game.getUnitList()); //move units

            bool playerAlive = false;
            int cityCount = 0;
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
                    cityCount++;
                }
                if (cell->getFaction() == Enemy) {
                    anyEnemyAlive = true;
                }
            }
            if (!playerAlive || cityCount != game.getCityCount()) {
                game.setStatus(Lost);
            }
            else if (!anyEnemyAlive) {
                game.setStatus(Win);
            }
            turnComplete = false;
            if (game.getStatus() != Running) { //stop loop immediately if gameover
                break;
            }
        }

        std::vector<SharedActor> contacts, filtered;
        for (Coord c : game.getUnitList()) { //populate list of contacts
            auto& cell = game.getCell(c.x, c.y);
            if (cell) {
                contacts.push_back(cell);
            }
        }

        SAM::sortContactsByDistance(contacts, game.getPlayerPos()); //sort list of contacts
        SAM::printUI(title, game.drawBoard(), game.listContacts(game.getUnitList())); //draw UI
        if (!game.getLastLog().empty()) {
            std::cout << '\n' + game.getLastLog() + '\n';
        }
        std::cout << "\n[I]dentify   [S]hoot   [W]ait   [Q]uit\nEnter an action:  ";
        char input = std::tolower(getNextLineAlpha()[0]);

        //decision tree
        if (input == 'i') { //identify
            for (auto& contact : contacts) { //split off unidentified actors
                if (contact->getID() != 0 && contact->getActorType() == Mobile) {
                    filtered.push_back(contact);
                }
            }
            if (filtered.empty()) {
                std::cout << "Nothing to identify this turn.\n";
            }
            else {
                std::cout << "\nUnidentified contacts:\n";
                for (int i = 0; i < filtered.size(); i++) {
                    std::cout << " [" << i + 1 << "] " << filtered[i]->toString(game.getPlayerPos(), false) << '\n';
                }
                std::cout << "Pick a contact [#]: ";
                int choice = getNextInt();
                if (choice >= 1 && choice <= filtered.size()) {
                    game.identify(filtered[choice - 1]);
                    turnComplete = true;
                }
            }
        }
        else if (input == 's') { //shoot
            std::cout << "SAM effective range: " << game.RANGE << '\n';
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
                    std::cout << " [" << i + 1 << "] " << filtered[i]->toString(game.getPlayerPos(), false) << '\n';
                }
                std::cout << "Pick a contact [#]: ";
                int choice = getNextInt();
                if (choice >= 1 && choice <= filtered.size()) {
                    game.launchMissile(filtered[choice - 1]);
                    turnComplete = true;
                }
            }
        }
        else if (input == 'w') { //wait
            turnComplete = true;
        }
        else if (input == 'q') { //quit
            return 0;

        }
        else {
            std::cout << "Invalid choice\n";
            continue;
        }
    }
    SAM::printUI("GAME OVER!", game.drawBoard(), game.listContacts(game.getUnitList()));
    std::cout << ((game.getStatus() == Win) ? "You win!\n" : "You lose!\n");
    SAM::writeLogs("session.log", game.getLogs());
    return 0;
}