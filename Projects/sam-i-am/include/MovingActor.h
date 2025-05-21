#pragma once
#include "Actor.h"
namespace SAM {
	class MovingActor : public Actor {
	private:
		typedef Actor base;
	protected:
		int speed = 0; //max speed in tiles per turn
		Bearing bearing = North;
		bool flyingLow = true; //TODO modifies range to hit
		bool attacks = false; //does actor attack other actors?
	public:
		MovingActor(Faction, const AircraftParams&, Bearing);
		void move(SAM::Game&) override;
		bool isMobile() const override;
		std::string toString(Coord, bool) const override;
	};
}