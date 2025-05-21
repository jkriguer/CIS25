#pragma once
#include <vector>
#include <string>

namespace SAM {
	extern const char SAVE_VERSION;
	extern const int MAX_X, MAX_Y;
	bool writeScenario(const std::string&, const std::vector<char>&);
	bool readScenario(const std::string&, std::vector<char>&);
	bool writeLogs(const std::string&, const std::vector<std::string>&);
}