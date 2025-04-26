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
	FlyingActor(const SharedBoard&, int, int, std::string, Faction, int, Bearing, bool); //every single arg
	std::string toString();
	bool isClosing(int, int);
	void move();
};
#endif 
