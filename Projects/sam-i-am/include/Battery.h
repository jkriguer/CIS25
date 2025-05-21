#pragma once
#include "StaticActor.h"


namespace SAM {
	class Battery : public StaticActor {
	public:
		explicit Battery() : StaticActor("Battery", 'B') {};
	};
}