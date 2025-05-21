#pragma once
#include "Actor.h"
namespace SAM {
	class StaticActor : public Actor {
	private:
		typedef Actor base;
	public:
		StaticActor(std::string, char);
		void move(SAM::Game&) override;
		bool isMobile() const override;
		std::string toString(Coord, bool) const override;
	};
}