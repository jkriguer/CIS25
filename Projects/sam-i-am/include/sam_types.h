#pragma once
#include <vector>
#include <memory>
#include <string>

class Actor; //forward dec

using SharedActor = std::shared_ptr<Actor>;
using WeakActor = std::weak_ptr<Actor>;
using Board = std::vector<std::vector<SharedActor>>;

enum Bearing { North, Northeast, East, Southeast, South, Southwest, West, Northwest };
enum Faction { Neutral, Enemy, Friendly };
enum ActorType { Player, Mobile, City };
enum Status {Running, Lost, Win, Stalemate};


struct PlayerParams {
	std::string label;
	int range;
	int launchDelay;
};

struct AircraftParams {
	std::string label;
	int speed;
	bool flyingLow;
	bool attacks = false;
};

struct Coord {
	int x;
	int y;
};

struct Missile {
	std::weak_ptr<Actor> target;
	int turnsToImpact;
	int maxRange;
};