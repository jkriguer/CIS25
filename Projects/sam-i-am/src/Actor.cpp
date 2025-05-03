#include "../include/Actor.h"
#include "../include/sam_utils.h"
#include "../include/Game.h"
#include <iostream> //debug
#include <sstream>
#include <iomanip>


//constructors
Actor::Actor(ActorType aT, std::string l, char c) {
	this->actorType = aT;
	this->mapIcon = c;
	this->label = l;
}

Actor::Actor(Faction f, AircraftParams a, Bearing b) : Actor(ActorType::Mobile, "UFO", '?') {
	this->faction = f;
	this->mapIcon = SAM::getNewContactNumber();
	this->label = a.label;
	this->flyingLow = a.flyingLow;
	this->speed = a.speed;
	this->bearing = b;
	this->attacks = a.attacks;
	this->identified = (f == Friendly) ? 0 : 2;
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
std::string Actor::toString(Coord p, bool printBRAS) {
	using std::left, std::setw;
	if (this->actorType != Mobile) {
		return this->label + " " + SAM::coordToStr(this->getCoords());
	}
	std::ostringstream out;
	std::string displayLabel = ((this->identified != 0) ? "Aircraft " : this->label + ' ') +
		getMapIcon();
	std::string displayAlt = (flyingLow) ? "LOW" : "HI";
	out << setw(13) << left << displayLabel; //name
	if (printBRAS) {
			out << setw(4) << left << SAM::bearingToStr(this->bearing) << //bearing
			setw(4) << left << SAM::manhattan(getCoords(), p) << //range
			setw(4) << left << displayAlt << setw(4) << left << this->speed; //alt and speed
	}
	return out.str();
}

void Actor::move(SAM::Game& g) {
	Coord step = SAM::getBearingMods(this->bearing); //goodbye switch blob!

	int xStep = this->x + (step.x * this->speed);
	int yStep = this->y + (step.y * this->speed);

	if (!g.inBounds(xStep, yStep)) { //if actor leaves map 
		g.log("Actor left the map. Add more detail.");
		g.getCell(this->x, this->y).reset(); //destroy it
		return;
	}

	//TODO also check destination is empty
	g.setCell(xStep, yStep, std::move(g.getCell(this->x, this->y)));//actually move
	g.getCell(this->x, this->y).reset(); //erase last location
	setActorCoords(Coord(xStep, yStep)); //update internal coords
}


bool Actor::isBlocked(SAM::Game& g, Coord dst) {
	if (!g.getCell(dst.x, dst.y)) {
		return false; //can't be blocked if there's nothing to block
	}
	switch (this->getFaction()) {
		case Enemy:
			return g.getCell(dst.x, dst.y)->getFaction() == Enemy || //avoid fellow enemies
				(g.getCell(dst.x, dst.y)->getFaction() == Neutral && //avoid neutrals
					g.getCell(dst.x, dst.y)->getActorType() != City); //as long as they're mobs
		case Friendly:
			return g.getCell(dst.x, dst.y)->getFaction() != Enemy; //avoid anything that isn't enemy
		default:
			return true; //avoid interactions regardless
	}
}

bool Actor::isValidTarget(SAM::Game& g, Coord dst) {
	if (g.getCell(dst.x, dst.y)->getFaction() == Enemy) { //if actor is enemy
		return g.getCell(dst.x, dst.y)->getActorType() == City; //clobber city
	}
	if (g.getCell(dst.x, dst.y)->getFaction() == Friendly) { //if actor is friendly
		return g.getCell(dst.x, dst.y)->getFaction() == Enemy; //clobber enemy
	}
	return false; //clobber nothing otherwise
}

int Actor::getID() {
	return this->identified;
}

bool Actor::tickID() {
	if (identified <= 0) {
		return false; //already IDed
	}
	identified--;
	return true; //lowered ID req by 1
}