#include "../include/sam_io.h"
#include <fstream>
#include <filesystem>
#include <iostream> //debug

const char SAM::SAVE_VERSION = 10;

bool SAM::writeScenario(const std::string& file, const std::vector<char>& scenario) {
	std::filesystem::path path = std::filesystem::path(SCENARIOS_DIR) / file; //set path
	std::filesystem::create_directories(path.parent_path()); //makes scenarios folder in build dir as workaround
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
	std::cout << "Debug: scenario written to " << path << '\n';
	return true;
}

bool SAM::readScenario(const std::string& file, std::vector<char>& scenario) {
	std::filesystem::path path = std::filesystem::path(SCENARIOS_DIR) / file; //set path
	std::ifstream in(path, std::ios::binary); //handle opened
	if (!in.is_open()) {
		return false; //file couldn't be opened
	}
	char byte = 0;
	while (in.get(byte)) {
		scenario.push_back(byte); //read one char at a time
	}
	in.close(); //handle closed
	std::cout << "Debug: scenario read from " << path << '\n';
	return true;
}