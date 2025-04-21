#ifndef FLYING_ACTOR_CLASS
#define FLYING_ACTOR_CLASS

#include <iostream>
#include <string>
#include "Actor.h"

enum class Bearing { N = 8, E = 6, S = 2, W = 4, NW = 7, NE = 9, SE = 3, SW = 1 };


class FlyingActor : public Actor {
private:
	typedef Actor base; //*super* cool!
	std::string label; //the contact number/any needed info for listing the contact
	Faction factionActual;
	Faction factionDisplay = Faction::UNKNOWN;
	double factionConfidence; //from 0.0 (unidentified) to 1.0 (fully identified)
	int speed; //in tiles per turn
	Bearing bearing;
	bool flyingLow;
public:
	//constructors
	FlyingActor(std::string _label, Faction _faction, double _factionConfidence, int _speed, Bearing _bearing, bool _flyingLow);
	//setters and getters
	
	//other methods
	bool isHot();
	std::string readBRAA();
	std::string toString();
};

//std::ostream& operator<<(std::ostream&, const FlyingObject&);

#endif 
