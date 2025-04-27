#ifndef SAM_TYPES
#define SAM_TYPES

#include <vector>
#include <memory>
#include <string>

class Actor; //forward dec
class FlyingActor; //forward dec

using Board = std::vector<std::vector<std::unique_ptr<Actor>>>; //saves so much space
using SharedBoard = std::shared_ptr<Board>;

enum Bearing { N, E, S, W, NW, NE, SE, SW };
enum Faction { NEUTRAL, HOSTILE, FRIENDLY };

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