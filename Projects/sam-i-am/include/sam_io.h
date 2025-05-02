#pragma once
#include <vector>
#include <string>

namespace SAM {
	extern const char SAVE_VERSION;
	bool writeScenario(const std::string&, const std::vector<char>&);
	bool readScenario(const std::string&, std::vector<char>&);
}