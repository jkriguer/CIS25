#include "../include/StaticActor.h"
#include "../include/sam_utils.h"

SAM::StaticActor::StaticActor(std::string l, char c) {
	this->label = l;
	this->mapIcon = c;
}

void SAM::StaticActor::move(SAM::Game& g) {} //no op

std::string SAM::StaticActor::toString(Coord c, bool b) const {
	return this->label + ' ' + SAM::coordToStr(this->position);
}