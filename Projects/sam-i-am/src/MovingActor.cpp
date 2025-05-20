#include "../include/MovingActor.h"
#include "../include/sam_utils.h"
#include "../include/Game.h"
#include <sstream>
#include <iomanip>

SAM::MovingActor::MovingActor(Faction f, const AircraftParams& ap, Bearing b) {
	actorType = Mobile;
	faction = f;
	label = ap.label;
	flyingLow = ap.flyingLow;
	speed = ap.speed;
	bearing = b;
	attacks = ap.attacks;
	identified = (f == Friendly) ? 0 : 1;
}


void SAM::MovingActor::move(SAM::Game& g) {
	Coord step = SAM::getBearingMods(bearing);
	int xStep = position.x + step.x * speed;
	int yStep = position.y + step.y * speed;

	if (!g.inBounds(xStep, yStep)) { //if actor leaves map 
		g.log(this->toString(position, false) + " left the map.");
		g.getCell(position.x, position.y).reset(); //destroy it
		return;
	}
	g.setCell(xStep, yStep, std::move(g.getCell(position.x, position.y))); //actually move
	g.getCell(position.x, position.y).reset(); //erase last location
	setCoords({ xStep, yStep });
}

bool SAM::MovingActor::isMobile() const {
	return true;
}

std::string SAM::MovingActor::toString(Coord c, bool printBRAS) const {
	using std::left, std::setw;
	std::ostringstream out;
	std::string displayLabel = ((this->identified != 0) ? "Aircraft " : this->label + ' ') + this->mapIcon;
	std::string displayAlt = (flyingLow) ? "LOW" : "HI";
	out << setw(13) << left << displayLabel; //name
	if (printBRAS) {
		out << setw(4) << left << SAM::bearingToStr(bearing) << //bearing
			setw(4) << left << SAM::manhattan(position, c) << //range
			setw(4) << left << displayAlt << setw(4) << left << this->speed; //alt and speed
	}
	return out.str();
}

int SAM::MovingActor::getID() {
	return identified;
}

bool SAM::MovingActor::tickID() {
	if (identified <= 0) {
		return false;
	}
	identified--;
	return true;
}

