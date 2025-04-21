#include "FlyingActor.h"

//constructors
FlyingActor::FlyingActor(std::string _label, Faction _faction, double _factionConfidence, int _speed, Bearing _bearing, bool _flyingLow) 
{
	this->label = _label;
	this->factionActual = _faction;
}

//other methods
bool FlyingActor::isHot() { //returns true if flying towards player
	return true; //NYI
}

std::string FlyingActor::toString() {
	//return "Label: " + getLabel() +
	//	"\nBRAA: " + readBRAA();
	return "NYI";
}

std::string FlyingActor::readBRAA() {
	return "Bearing: NYI";
}

//std::ostream& operator<<(std::ostream& os, const FlyingObject& fo) { //NYI
//	os << fo.toString();
//	return os;
//}