#ifndef SAM_TYPES
#define SAM_TYPES

#include <vector>
#include <memory>
#include <string>

class Actor; //forward dec

using Board = std::vector<std::vector<std::unique_ptr<Actor>>>; //saves so much space
using SharedBoard = std::shared_ptr<Board>;

enum Bearing { North, East, South, West, Northwest, Northeast, Southeast, Southwest };
enum Faction { Neutral, Enemy, Friendly };
enum ActorType { Player, Mobile, City };
enum TrackQuality { Perfect = 100, Good = 80, Decent = 50, Bad = 20}; //placeholder values

struct SAM {
	std::string label;
	int range;
	int launchDelay;
};

struct Aircraft {
	std::string label;
	int speed;
	bool flyingLow;
	bool attacks = false;
};




#endif // !SAM_TYPES