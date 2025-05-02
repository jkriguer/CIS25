#include "../include/Actor.h"
#include "../include/sam_utils.h"
#include "../include/Game.h"
#include <utility> //std::move
#include <iostream> //debug

using namespace SAM;

//constructors
Actor::Actor(ActorType aT, std::string l, char c) {
	this->actorType = aT;
	this->mapIcon = c;
	this->label = l;
}

Actor::Actor(Faction f, AircraftParams a, Bearing b) : Actor(ActorType::Mobile, "UFO", '?') {
	this->faction = f;
	this->mapIcon = getNewContactNumber();
	this->label = a.label;
	this->flyingLow = a.flyingLow;
	this->speed = a.speed;
	this->bearing = b;
	this->attacks = a.attacks;
}
//setters and getters
char Actor::getMapIcon() {
	return this->mapIcon;
}

bool Actor::setCoords(Coord c) {
	//TODO check for collision and return false
	this->x = c.x;
	this->y = c.y;
	return true;
}
Faction Actor::getFaction() {
	return this->faction;
}
ActorType Actor::getActorType() {
	return this->actorType;
}
Coord Actor::getCoords() {
	
	return { x, y };
}
//other methods
std::string Actor::toString() {
	return label + " (" + std::to_string(this->x) + ", " + std::to_string(this->y) + ")";
}

void Actor::move(SAM::Game& g) {
	auto [xMod, yMod] = getBearingMods(this->bearing); //goodbye switch blob!

	int xNew = this->x + (xMod * this->speed);
	int yNew = this->y + (yMod * this->speed);

	if (xNew < 0 || xNew >= g.getWidth() || yNew < 0 || yNew >= g.getHeight()) { //if actor leaves map 
		std::cout << "Debug: moved off map!\n";
		g.getCell(this->x, this->y).reset(); //destroy it
		return;
	}

	//TODO also check destination is empty
	g.setCell(xNew, yNew, std::move(g.getCell(this->x, this->y)));//actually move
	this->x = xNew;
	this->y = yNew;
}

Actor::~Actor() {
	std::cout << "Debug: destroyed!\n";
}