#include "Movie.h"

void Movie::inputMovie() {
	std::cout << "Enter the movie title: ";
	this->title = getNextLine();
	std::cout << "Enter release year: ";
	this->release.inputDate();
	std::cout << "Enter aggregated review score (from 0.0 to 5.0): ";
	while (this->review < 0.0 || this->review > 5.0) {
		this->review = getNextDouble();
	}
}

std::ostream& operator<<(std::ostream& os, const Movie& movie) {
	os << movie.title + " (" << movie.release <<  "), " + std::to_string(movie.review) + "/5";
	return os;
}