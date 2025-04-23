#include "Actor.h" //header
#include "sam_utils.h" //getContactNumber

//constructors
//Actor::Actor() : board(nullptr) {}; //noarg
Actor::Actor(const SharedBoard& b, int _xCoord, int _yCoord, std::string _label) : board(b) { //args
	this->xCoord = _xCoord;
	this->yCoord = _yCoord;
	this->label = _label;
	this->contact = getContactNumber();
}