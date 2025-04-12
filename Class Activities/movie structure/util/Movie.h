#ifndef movie_struct
#define movie_struct

#include <iostream>
#include "scanner.h"

struct Movie {
	std::string title = "Untitled Movie";
	int release = 1899;
	double review = -1.0;
	void inputMovie();
};

std::ostream& operator<<(std::ostream&, const Movie&);

#endif