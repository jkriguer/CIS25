#include "FlyingObject.h"

//constructors
FlyingObject::FlyingObject() : FlyingObject("Test Object", Faction::UNKNOWN, 0.0, 1, Bearing::S, false) {
}

FlyingObject::FlyingObject(std::string _label, Faction _faction, double _factionConfidence, int _speed, Bearing _bearing, bool _flyingLow) {
	setLabel(_label);
	setFaction(_faction);
	setFactionConfidence(_factionConfidence);
	setSpeed(_speed);
	setFlyingLow(_flyingLow);
}

//setters and getters
void FlyingObject::setLabel(std::string _label) {
	this->label = _label;
}
void FlyingObject::setFaction(Faction _faction) {
	this->faction = _faction;
}
void FlyingObject::setFactionConfidence(double _factionConfidence) {
	this->factionConfidence = _factionConfidence;
}
void FlyingObject::setSpeed(int _speed) {
	this->speed = speed;
}
void FlyingObject::setBearing(Bearing _bearing) {
	this->bearing = _bearing;
}
void FlyingObject::setFlyingLow(bool _flyingLow) {
	this->flyingLow = _flyingLow;
}
std::string FlyingObject::getLabel() {
	return this->label;
}
Faction FlyingObject::getFaction() {
	return this->faction;
}
double FlyingObject::getFactionConfidence() {
	return this->factionConfidence;
}
int FlyingObject::getSpeed() {
	return this->speed;
}
Bearing FlyingObject::getBearing() {
	return this->bearing;
}
bool FlyingObject::getFlyingLow() {
	return this->flyingLow;
}

//other methods
bool isHot() { //returns true if flying towards player
	return true; //NYI
}

std::string FlyingObject::toString() {
	return "Label: " + getLabel() +
		"\nBRAA: " + readBRAA();
}

std::string FlyingObject::readBRAA() {
	return "Bearing: NYI";
}

//std::ostream& operator<<(std::ostream& os, const FlyingObject& fo) { //NYI
//	os << fo.toString();
//	return os;
//}