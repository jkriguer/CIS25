#include "Actor.h" //header
#include "sam_utils.h" //getNewContactNumber

using namespace SAMUTIL;

//constructors
Actor::Actor(const SharedBoard& b, int x, int y, std::string l) :
	Actor(b, x, y, l, getNewContactNumber()) {}

Actor::Actor(const SharedBoard& b, int x, int y, std::string l, char c) :
	board(b), xCoord(x), yCoord(y), label(l), contact(c) {}

//setters and getters
char Actor::getContact() {
	return this->contact;
}
//other methods
std::string Actor::toString() {
	return label + " (" + std::to_string(xCoord) + ", " + std::to_string(yCoord) + ")";
}

double Actor::distanceTo(std::shared_ptr<Actor> a) {
	return pow((this->xCoord - a->xCoord), 2) + pow((this->yCoord - a->xCoord), 2);
}

void Actor::move() {};