#include "../include/sam_io.h"
#include <fstream>
#include <filesystem>

const char SAM::SAVE_VERSION = 10;

bool SAM::writeScenario(const std::string& file, const std::vector<char>& scenario) {
	std::filesystem::path path = std::filesystem::path("scenarios") / file; //set path
	std::ofstream out(path, std::ios::binary); //handle opened
	if (!out.is_open()) {
		return false; //file couldn't be opened
	}
	for (char byte : scenario) {
		out.put(byte); //write one char at a time
		if (!out.good()) {
			throw std::runtime_error("Output file couldn't be written to.");
		}
	}
	out.close(); //handle closed
	return true;
}

bool SAM::readScenario(const std::string& file, std::vector<char>& scenario) {
	std::filesystem::path path = std::filesystem::path("scenarios") / file; //set path
	std::ifstream in(path, std::ios::binary); //handle opened
	if (!in.is_open()) {
		return false; //file couldn't be opened
	}
	char byte = 0;
	while (in.get(byte)) {
		scenario.push_back(byte); //read one char at a time
	}
	in.close(); //handle closed
	return true;
}