#ifndef FLYING_ACTOR_CLASS
#define FLYING_ACTOR_CLASS

#include "Actor.h"
#include "sam_types.h"

class FlyingActor : public Actor {
private:
	typedef Actor base; //*super* cool!
	Faction faction;
	double trackQuality; //from 0.0 (unidentified) to 1.0 (fully identified)
	int speed; //in tiles per turn
	Bearing bearing;
	bool flyingLow;
public:
	FlyingActor(const SharedBoard&, int, int, std::string, Faction, int, Bearing, bool); //every single arg
	FlyingActor(const SharedBoard&, int, int, Faction, Bearing);
	FlyingActor(const SharedBoard&, int, int, Aircraft, Bearing);
	std::string toString(std::shared_ptr<Actor>);
	void move();
};

#endif 
