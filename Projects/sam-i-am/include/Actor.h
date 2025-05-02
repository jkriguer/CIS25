#pragma once
#include "sam_types.h" //types

namespace SAM {
	class Game; //forward dec
}

class Actor {
protected:
	ActorType actorType;
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
	Actor(ActorType, std::string, char); //stationary
	Actor(AircraftParams, Bearing); //mobile
	char getMapIcon();
	bool setCoords(int, int);
	std::pair<int, int> getCoords();
	Faction getFaction();
	ActorType getActorType();
	std::string toString();
	double distanceTo(std::shared_ptr<Actor>);
	void move(SAM::Game&);
	virtual ~Actor();
};
