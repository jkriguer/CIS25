#include "Actor.h"
#include "sam_utils.h"

using namespace SAM;

//constructors
Actor::Actor(ActorType aT, std::string l, char c) {
	this->mapIcon = c;
	this->label = l;
}

Actor::Actor(AircraftParams a, Bearing b) : Actor(ActorType::Mobile, "UFO", '?') {
	this->mapIcon = getNewContactNumber();
	this->label = a.label;
	this->flyingLow = a.flyingLow;
	this->speed = a.speed;
	this->bearing = b;
}
//setters and getters
char Actor::getMapIcon() {
	return this->mapIcon;
}

bool Actor::setCoords(int x, int y) {
	//TODO check for collision and return false
	this->x = x;
	this->y = y;
	return true;
}
Faction Actor::getFaction() {
	return this->faction;
}
ActorType Actor::getActorType() {
	return this->actorType;
}
std::pair<int, int> Actor::getCoords() {
	
	return std::pair<int, int>(this->x, this->y);
}
//other methods
std::string Actor::toString() {
	return label + " (" + std::to_string(this->x) + ", " + std::to_string(this->y) + ")";
}

void Actor::move() {
	int xNew, yNew;
	auto [xMod, yMod] = getBearingMods(this->bearing); //goodbye switch blob!

	xNew = this->x + (xMod * this->speed);
	yNew = this->y + (yMod * this->speed);

	//TODO check for boundaries
	//TODO also check destination is empty
	setCell(xNew, yNew, std::move(getCell(this->x, this->y)));//actually move
	this->x = xNew;
	this->y = yNew;
}