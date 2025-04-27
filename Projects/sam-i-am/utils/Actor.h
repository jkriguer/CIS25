#ifndef ACTOR_CLASS
#define ACTOR_CLASS

#include "sam_types.h" //types

class Actor {
protected:
	ActorType actorType;
	const SharedBoard board;
	int x = -1; //changed after construction
	int y = -1; //changed after construction
	std::string label = "Unnamed Actor";
	char mapIcon = '?';
	Faction faction;
	double trackQuality; //from 0.0 (unidentified) to 1.0 (fully identified)
	int speed = 0; //in tiles per turn
	Bearing bearing = Bearing::North;
	bool flyingLow = true;
public:
	Actor(ActorType, const SharedBoard&, std::string, char); //stationary
	Actor(const SharedBoard&, Aircraft, Bearing); //mobile
	char getMapIcon();
	bool setCoords(int, int);
	std::string toString();
	std::string toString(std::shared_ptr<Actor>);
	double distanceTo(std::shared_ptr<Actor>);
	void move();
};

#endif // !ACTOR
