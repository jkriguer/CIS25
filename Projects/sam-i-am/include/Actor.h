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
	int identified = 0; //turns until identified. 0 means fully IDed
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
	std::string toString(Coord);
	void move(SAM::Game&);
	bool isBlocked(SAM::Game&, Coord);
	bool isValidTarget(SAM::Game&, Coord);
	int getID();
	bool tickID();
	std::string getBRAS(Coord);
};
