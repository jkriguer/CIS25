#include "Actor.h" //header
#include "sam_utils.h" //getNewContactNumber

using namespace SAMUTIL;

//constructors
Actor::Actor(ActorType aT, const SharedBoard& b, std::string l, char c) : board(b) {
	this->mapIcon = c;
	this->label = l;
}

Actor::Actor(const SharedBoard& board, Aircraft a, Bearing b) : Actor(ActorType::Mobile, board, "UFO", '?') {
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
//other methods
std::string Actor::toString() {
	return label + " (" + std::to_string(x) + ", " + std::to_string(y) + ")";
}



std::string Actor::toString(std::shared_ptr<Actor> player) {
	std::string output = "Track #" + std::to_string(getMapIcon()) + ", ";
	output += ((trackQuality >= 90) ? factionToStr(this->faction) : "Unknown") + ". ";
	output += "Bearing: " + ((trackQuality >= 25) ? bearingToStr(this->bearing) : "TBD") + ". ";
	output += "Range: " + ((trackQuality >= 50) ? std::to_string(this->distanceTo(player)) : "TBD") + ".";
	output += "Altitude: " + (trackQuality >= 70) ? (this->flyingLow ? "Low" : "High") : "TBD";
	return output;
}

double Actor::distanceTo(std::shared_ptr<Actor> a) {
	return pow((this->x - a->x), 2) + pow((this->y - a->x), 2);
}

void Actor::move() {
	int xNew, yNew;
	auto [xMod, yMod] = getBearingMods(this->bearing); //goodbye switch blob!

	xNew = this->x + (xMod * this->speed);
	yNew = this->y + (yMod * this->speed);

	//TODO check for boundaries
	//TODO also check destination is empty

	(*board)[xNew][yNew] = std::move((*board)[this->x][this->y]); //actually move
	this->x = xNew;
	this->y = yNew;
}