#include "FlyingActor.h" //header
#include "sam_utils.h" //getBearingMods

using namespace SAMUTIL;

FlyingActor::FlyingActor(const SharedBoard& board, int x, int y, std::string l, Faction f, int s, Bearing _bearing, bool fL) :
	base(board, x, y, l), faction(f), speed(s), bearing(_bearing), flyingLow(fL) {
	if (f == Faction::FRIENDLY) { //if contact is friendly
		this->factionConfidence = 1.0; //full confidence
	}
	else { //placeholder, will randomly determine later
		this->factionConfidence = 0.5; //otherwise random confidence
	}
}

FlyingActor::FlyingActor(const SharedBoard& board, int x, int y, Faction f, Bearing b) : base(board, x, y, "UFO") {
	Aircraft archetype = getArchetype(f);
	this->label = archetype.label;
	this->flyingLow = archetype.flyingLow;
	this->speed = archetype.speed;
}

std::string FlyingActor::toString() {
	return "FA NYI";
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
