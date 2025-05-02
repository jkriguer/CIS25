#pragma once
#include <vector>
#include <memory>
#include <string>

class Actor; //forward dec

using Board = std::vector<std::vector<std::unique_ptr<Actor>>>;

enum Bearing { North, East, South, West, Northwest, Northeast, Southeast, Southwest };
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

struct Scenario {
	unsigned char validBegin;
	int x;
	int y;
	int cityCount;
	std::vector<int> cityData;
	int friendlyCount;
	std::vector<int> friendlyData;
	int enemyCount;
	std::vector<int> enemyData;
	int neutralCount;
	std::vector<int> neutralData;
	OptionalRules rules;
	unsigned char validEnd;
};