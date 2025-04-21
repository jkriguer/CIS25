#include <iostream>
#include <vector>
#include "utils/FlyingActor.h"

class Grid{};

int main() {
	//std::vector<std::vector<Grid>>;
	FlyingActor test("test", Faction::FRIENDLY, 1.0, 5, Bearing::S, true);
	std::cout << test.toString() << '\n';
}