#include "../include/MovingActor.h"
#include "../include/sam_utils.h"
#include "../include/Game.h"
#include <sstream>
#include <iomanip>

SAM::MovingActor::MovingActor(Faction f, const AircraftParams& ap, Bearing b) {
	faction = f;
	label = ap.label;
	flyingLow = ap.flyingLow;
	speed = ap.speed;
	bearing = b;
	attacks = ap.attacks;
	isIdentified = (f == Friendly);

	static int count = 0;
	mapIcon = '0' + (count++) % 10;
}

void SAM::MovingActor::move(SAM::Game& g) {
	Coord step = position;
	Coord mods = getBearingMods(bearing);
	step.x += mods.x * speed;
	step.y += mods.y * speed;

	if (!g.inBounds(step)) { //if actor leaves map 
		g.log(this->toString(position, false) + " left the map.");
		g.getCell(position).reset(); //destroy it
		return;
	}
	g.setCell(step, std::move(g.getCell(position))); //actually move
	g.getCell(position).reset(); //erase last location
	setCoords(step);
}

std::string SAM::MovingActor::toString(Coord c, bool printBRAS) const {
	using std::left, std::setw;
	std::ostringstream out;
	std::string displayLabel = ((!isIdentified) ? "Aircraft " : this->label + ' ') + this->mapIcon;
	std::string displayAlt = (flyingLow) ? "LOW" : "HI";
	out << setw(13) << left << displayLabel; //name
	if (printBRAS) {
		out << setw(4) << left << SAM::bearingToStr(bearing) << //bearing
			setw(4) << left << SAM::manhattan(position, c) << //range
			setw(4) << left << displayAlt << setw(4) << left << this->speed; //alt and speed
	}
	return out.str();
}