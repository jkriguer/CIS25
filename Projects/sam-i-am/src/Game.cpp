#include "../include/Game.h"
#include "../include/sam_utils.h"
#include "../include/sam_io.h"
#include <iostream>

SAM::Game::Game() {
	board = Board(SAM::MAX_Y); //initialize board
	for (auto& row : board) { //avoid copying unique pointers this way
		row.resize(SAM::MAX_X);
	}
	status = Running; //start game
}

bool SAM::Game::inBounds(Coord c) {
	return c.x >= 0 && c.x < SAM::MAX_X && c.y >= 0 && c.y < SAM::MAX_Y;
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
				line += getCell({ j, i })->getMapIcon();
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

ActorPtr& SAM::Game::getCell(Coord c) {
	return (board).at(c.y).at(c.x);
}

void SAM::Game::setCell(Coord c, ActorPtr a) {
	getCell(c) = std::move(a);
}

void SAM::Game::moveAllUnits(const std::vector<Coord>& units) {
	std::vector<Coord> enemy, friendly, neutral;
	for (const Coord& c : units) { //sort units by faction
		if (dynamic_cast<MovingActor*>(getCell(c).get())) {
			switch (getCell(c)->getFaction()) {
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
		getCell(c)->move(*this);
	}
}

std::vector<std::string> SAM::Game::listContacts(const std::vector<Coord>& units) {
	std::vector<std::string> output{ "  Name       BRG RNG ALT SPD" };
	for (const Coord& c : units) {
		if (dynamic_cast<MovingActor*>(getCell(c).get())) {
			output.push_back(getCell(c)->toString(this->playerPos, true));
		}
	}
	return output;
}

std::vector<Coord> SAM::Game::getUnitList() {
	std::vector<Coord> output;
	for (int i = 0; i < SAM::MAX_X; i++) {
		for (int j = 0; j < SAM::MAX_Y; j++) {
			if (getCell({ i, j })) {
				output.push_back({ i, j });
			}
		}
	}
	return output;
}

bool SAM::Game::placeActor(ActorPtr a, Coord c) {
	if (getCell(c)) { //fail if cell occupied
		return false;
	}
	if (dynamic_cast<City*>(a.get())) {
		cityCount++;
	}
	if (dynamic_cast<Battery*>(a.get())) {
		playerPos = c;
	}
	setCell(c, std::move(a));
	getCell(c)->setCoords(c);
	return true; //success
}

bool SAM::Game::makeAndPlaceCity(Coord c) {
	static int count = 0;
	auto city = std::make_unique<City>();
	//modify city label if desired
	return placeActor(std::move(city), c);
}

bool SAM::Game::makeAndPlaceBattery(Coord c) {
	return placeActor(std::make_unique<Battery>(), c);
}

bool SAM::Game::makeAndPlaceMoving(Faction f, AircraftParams role, Bearing b, Coord c) {
	static int count = 0;
	auto moving = std::make_unique<MovingActor>(f, role, b);
	return placeActor(std::move(moving), c);
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
	int batteryCount = 0;
	int cityCount = 0;
	for (int i = 0; i < fixedCount; i++) {
		bool isCity = s[index++];
		int x = s[index++];
		int y = s[index++];
		if (isCity) {
			makeAndPlaceCity({ x, y });
			cityCount++;
		}
		else {
			makeAndPlaceBattery({ x, y });
			this->playerPos = { x, y };
			batteryCount++;
		}
	}
	if (cityCount < 1 || batteryCount != 1) { //if all fixed actors are cities or none of them are
		throw std::runtime_error("Illegal scenario: player or cities not placed");
	}
	int mobileCount = s[index++];
	for (int i = 0; i < mobileCount; i++) {
		Faction f = (Faction)s[index++];
		int archetype = s[index++]; //archetype lookup index
		Bearing b = (Bearing)s[index++];
		int x = s[index++];
		int y = s[index++];
		makeAndPlaceMoving(f, getArchetype(f, archetype), b, { x, y });
	}
	return true;
}

void SAM::Game::log(std::string l) {
	logs.push_back(l);
}

std::vector<Coord> SAM::Game::sortByDistance(const std::vector<Coord>& in, Coord from) const {
	auto out = in;
	for (int i = 1; i < out.size(); i++) {
		auto current = out[i];
		int dist = SAM::manhattan(from, current);
		int j = i;
		while (j > 0 && SAM::manhattan(from, out[j - 1]) > dist) {
			out[j] = out[j - 1];
			j--;
		}
		out[j] = current;
	}
	return out;
}

bool SAM::Game::launchMissile(Coord tgtC) {
	auto& tgt = getCell(tgtC);
	if (!tgt) { //fail if tgt absent/destroyed
		return false;
	}
	int dist = SAM::manhattan(playerPos, tgtC);
	if (dist <= RANGE) {
		logs.push_back("Missile launched at " + tgt->toString(playerPos, false) + " - Hit!");
		getCell(tgtC).reset();
		return true;
	}
	logs.push_back("Missile launched at " + tgt->toString(playerPos, false) + " - Missed.");
	return false;
}

bool SAM::Game::identify(Coord tgtC) {
	auto& tgt = getCell(tgtC);
	if (!tgt || tgt->isIdentified) {
		return false;
	}
	tgt->isIdentified = true;
	log("ID complete on " + tgt->toString(playerPos, false));
	return true;
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

void SAM::Game::setStatus(Status s) {
	this->status = s;
}

