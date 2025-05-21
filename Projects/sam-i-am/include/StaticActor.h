#pragma once
#include "Actor.h"
namespace SAM {
	class StaticActor : public Actor {
	private:
		typedef Actor base;
	public:
		explicit StaticActor(std::string, char);
		void move(SAM::Game&) override;
		std::string toString(Coord, bool) const override;
	};
}