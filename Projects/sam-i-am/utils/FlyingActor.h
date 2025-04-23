#ifndef FLYING_ACTOR_CLASS
#define FLYING_ACTOR_CLASS

#include <iostream>
#include <string>
#include "Actor.h"
#include "sam_types.h"

class FlyingActor : public Actor {
private:
	typedef Actor base; //*super* cool!
	Faction faction;
	double factionConfidence; //from 0.0 (unidentified) to 1.0 (fully identified)
	int speed; //in tiles per turn
	Bearing bearing;
	bool flyingLow;
public:
	FlyingActor();
	//constructors
	//FlyingActor(std::string _label, Faction _faction, double _factionConfidence, int _speed, Bearing _bearing, bool _flyingLow);
	//setters and getters
	
	////other methods
	//bool isHot();
	//std::string readBRAA();
	//std::string toString();
};

//std::ostream& operator<<(std::ostream&, const FlyingObject&);

#endif 
