#ifndef FLYING_OBJECT_CLASS
#define FLYING_OBJECT_CLASS

#include <iostream>
#include <string>

enum class Faction{NEUTRAL, HOSTILE, FRIENDLY, UNKNOWN};
enum class Bearing { N = 8, E = 6, S = 2, W = 4, NW = 7, NE = 9, SE = 3, SW = 1 };

class FlyingObject {
private:
	std::string label; //the contact number/any needed info for listing the contact
	Faction faction;
	double factionConfidence; //from 0.0 (unidentified) to 1.0 (fully identified)
	int speed; //in tiles per turn
	Bearing bearing;
	bool flyingLow;
public:
	//constructors
	FlyingObject();
	FlyingObject(std::string _label, Faction _faction, double _factionConfidence, int _speed, Bearing _bearing, bool _flyingLow);
	//setters and getters
	void setLabel(std::string _label);
	void setFaction(Faction _faction);
	void setFactionConfidence(double _factionConfidence);
	void setSpeed(int _speed);
	void setBearing(Bearing _bearing);
	void setFlyingLow(bool _flyingLow);
	std::string getLabel();
	Faction getFaction();
	double getFactionConfidence();
	int getSpeed();
	Bearing getBearing();
	bool getFlyingLow(); //isFlyingLow()?
	//other methods
	bool isHot();
	std::string readBRAA();
	std::string toString();
};

//std::ostream& operator<<(std::ostream&, const FlyingObject&);

#endif // !FLYING_OBJECT_CLASS
