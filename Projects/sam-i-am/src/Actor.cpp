#include "../include/Actor.h"

Coord SAM::Actor::getCoords() {
	return this->position;
}

void SAM::Actor::setCoords(Coord c) {
	this->position = c;
}

char SAM::Actor::getMapIcon() {
	return this->mapIcon;
}

Faction SAM::Actor::getFaction() {
	return this->faction;
}

ActorType SAM::Actor::getActorType() {
	return this->actorType;
}