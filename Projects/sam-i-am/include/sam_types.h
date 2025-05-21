#pragma once
#include <vector>
#include <memory>
#include <string>
namespace SAM {
	class Actor; //forward dec
}

using ActorPtr = std::unique_ptr<SAM::Actor>;
using Board = std::vector<std::vector<ActorPtr>>;

enum Bearing { North, Northeast, East, Southeast, South, Southwest, West, Northwest };
enum Faction { Neutral, Enemy, Friendly };
enum ActorType { Player, Mobile, City };
enum Status {Running, Lost, Win, Stalemate};

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