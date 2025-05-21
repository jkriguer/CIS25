#pragma once
#include "StaticActor.h"

namespace SAM {
	class City : public StaticActor {
	public:
		explicit City() : StaticActor("City", 'C') {};
	};
}