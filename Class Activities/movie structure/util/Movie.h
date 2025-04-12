#ifndef movie_struct
#define movie_struct

#include <iostream>
#include "scanner.h"
#include "Date.h"

struct Movie {
	std::string title = "Untitled Movie";
	Date release;
	double review = -1.0;
	void inputMovie();
};

std::ostream& operator<<(std::ostream&, const Movie&);

#endif