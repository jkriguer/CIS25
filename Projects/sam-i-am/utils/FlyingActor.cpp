#include "FlyingActor.h" //header
#include "sam_utils.h" //getBearingMods

using namespace SAMUTIL;

FlyingActor::FlyingActor(const SharedBoard& board, int x, int y, std::string l, Faction f, int s, Bearing _bearing, bool fL) :
	base(board, x, y, l), faction(f), speed(s), bearing(_bearing), flyingLow(fL) {
	if (f == Faction::FRIENDLY) { //if contact is friendly
		this->trackQuality = 1.0; //full confidence
	}
	else { //placeholder, will randomly determine later
		this->trackQuality = 0.5; //otherwise random confidence
	}
}

FlyingActor::FlyingActor(const SharedBoard& board, int x, int y, Faction f, Bearing b) :
	FlyingActor(board, x, y, getArchetype(f), b) {
}
FlyingActor::FlyingActor(const SharedBoard& board, int x, int y, Aircraft a, Bearing b) : base(board, x, y, "UFO") {
	this->label = a.label;
	this->flyingLow = a.flyingLow;
	this->speed = a.speed;
}

std::string FlyingActor::toString(std::shared_ptr<Actor> player) {
	std::string output = "Track #" + std::to_string(getContact()) + ", ";
	output += ((trackQuality >= 90) ? factionToStr(this->faction) : "Unknown") + ". ";
	output += "Bearing: " + ((trackQuality >= 25) ? bearingToStr(this->bearing) : "TBD") + ". ";
	output += "Range: " + ((trackQuality >= 50) ? std::to_string(this->distanceTo(player)) : "TBD") + ".";
	output += "Altitude: " + (trackQuality >= 70) ? (this->flyingLow ? "Low" : "High") : "TBD";
	return output;
}

void FlyingActor::move() {
	int xNew, yNew;
	auto [xMod, yMod] = getBearingMods(this->bearing); //goodbye switch blob!

	xNew = this->xCoord + (xMod * this->speed);
	yNew = this->yCoord + (yMod * this->speed);

	//TODO check for boundaries
	//TODO also check destination is empty

	(*board)[xNew][yNew] = std::move((*board)[this->xCoord][this->yCoord]); //actually move
	this->xCoord = xNew;
	this->yCoord = yNew;
}
