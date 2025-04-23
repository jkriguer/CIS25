#include "Actor.h" //header
#include "sam_utils.h" //getContactNumber

//constructor
Actor::Actor(const SharedBoard& b, int _xCoord, int _yCoord, std::string _label) : board(b) { //args
	this->xCoord = _xCoord;
	this->yCoord = _yCoord;
	this->label = _label;
	this->contact = getNewContactNumber();
}
//setters and getters
int Actor::getContact() {
	return this->contact;
}