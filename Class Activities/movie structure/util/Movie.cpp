#include "Movie.h"

void Movie::inputMovie() {
	std::cout << "Enter the movie title: ";
	this->title = getNextLine();
	std::cout << "Enter release year: ";
	while (this->release < 1900 || this->release > 2100) {
		this->release = getNextInt();
	}
	std::cout << "Enter aggregated review score (from 0.0 to 5.0): ";
	while (this->review < 0.0 || this->review > 5.0) {
		this->review = getNextDouble();
	}
}

std::ostream& operator<<(std::ostream& os, const Movie& movie) {
	os << movie.title + " (" + std::to_string(movie.release) + "), " + std::to_string(movie.review) + "/5";
	return os;
}