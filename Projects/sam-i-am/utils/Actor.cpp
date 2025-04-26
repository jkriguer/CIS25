#include "Actor.h" //header
#include "sam_utils.h" //getContactNumber

//constructor
Actor::Actor(const SharedBoard& b, int x, int y, std::string l) :
	board(b), xCoord(x), yCoord(y), label(l) {
	this->contact = getNewContactNumber();
}
//setters and getters
int Actor::getContact() {
	return this->contact;
}
//other methods
std::string Actor::toString() {
	return label + " (" + std::to_string(xCoord) + ", " + std::to_string(yCoord) + ")";
}