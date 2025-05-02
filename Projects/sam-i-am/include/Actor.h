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
	char mapIcon;
	Faction faction = Neutral;
	double trackQuality = 0.0; //from 0.0 (unidentified) to 1.0 (fully identified)
	int speed = 0; //in tiles per turn
	Bearing bearing = Bearing::North;
	bool flyingLow = true; //TODO modifies range to hit
	bool attacks = false; //does actor attack other actors?
public:
	Actor(ActorType, std::string, char); //stationary
	Actor(Faction, AircraftParams, Bearing); //mobile
	char getMapIcon();
	bool setActorCoords(Coord);
	Coord getCoords();
	Faction getFaction();
	ActorType getActorType();
	std::string toString();
	void move(SAM::Game&);
	virtual ~Actor();
	bool isBlocked(SAM::Game&, Coord);
	bool isValidTarget(SAM::Game&, Coord);

};
