#include "../include/Actor.h"
#include "../include/sam_utils.h"
#include "../include/Game.h"
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

bool Actor::setActorCoords(Coord c) {
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
	return Coord(x, y);
}
//other methods
std::string Actor::toString() {
	return label + " (" + std::to_string(this->x) + ", " + std::to_string(this->y) + ")";
}

void Actor::move(SAM::Game& g) {
	Coord step = getBearingMods(this->bearing); //goodbye switch blob!

	int xStep = this->x + (step.x * this->speed);
	int yStep = this->y + (step.y * this->speed);

	if (xStep < 0 || xStep >= g.getWidth() || yStep < 0 || yStep >= g.getHeight()) { //if actor leaves map 
		std::cout << "Debug: moved off map!\n";
		g.getCell(this->x, this->y).reset(); //destroy it
		return;
	}

	//TODO also check destination is empty
	g.setCell(xStep, yStep, std::move(g.getCell(this->x, this->y)));//actually move
	this->x = xStep;
	this->y = yStep;
}

Actor::~Actor() {
	std::cout << "Debug: destroyed!\n";
}