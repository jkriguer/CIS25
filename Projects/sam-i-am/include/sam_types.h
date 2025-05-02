#pragma once
#include <vector>
#include <memory>
#include <string>

class Actor; //forward dec

using Board = std::vector<std::vector<std::unique_ptr<Actor>>>;

enum Bearing { North, Northeast, East, Southeast, South, Southwest, West, Northwest };
enum Faction { Neutral, Enemy, Friendly };
enum ActorType { Player, Mobile, City };
enum TrackQuality { Perfect = 100, Good = 75, Decent = 50, Bad = 25}; //placeholder values
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

struct OptionalRules {
	bool endOneCity; //game over if one city is destroyed
	bool endFriendlyKill; //game over if friendly unit killed
	bool endNeutralKill; //game over if neutral unit killed
};

struct Coord {
	int x;
	int y;
};