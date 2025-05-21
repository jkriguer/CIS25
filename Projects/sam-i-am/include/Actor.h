#pragma once
#include "sam_types.h" //types

namespace SAM {
	class Game; //forward dec

	class Actor {
	protected:
		Coord position{ -1, -1 };
		std::string label = "Unnamed";
		char mapIcon = '?';
		Faction faction = Neutral;
	public:
		virtual ~Actor() = default;
		virtual void move(SAM::Game&) = 0;
		virtual bool isMobile() const = 0;
		virtual std::string toString(Coord, bool) const = 0;

		bool isIdentified = true;

		Coord getCoords();
		void setCoords(Coord);
		char getMapIcon();
		Faction getFaction();
	};
}