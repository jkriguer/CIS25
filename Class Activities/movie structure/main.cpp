#include "util/scanner.h"
#include "util/Movie.h"
#include "util/Date.h"

int main() {
	Movie movie1, movie2;
	std::cout << "Input movie 1\n";
	movie1.inputMovie();
	std::cout << "Input movie 2\n";
	movie2.inputMovie();
	std::cout << "Output movie 1: " << movie1 << '\n';
	std::cout << "Output movie 2: " << movie2 << '\n';
	return 0;
}

/* OUTPUT
Input movie 1
Enter the movie title: Terminator
Enter release year: Enter the date's year: 1984
Enter the date's month as an int (1 - 12): 10
Enter aggregated review score (from 0.0 to 5.0): 4.05
Input movie 2
Enter the movie title: Terminator 2
Enter release year: Enter the date's year: 1991
Enter the date's month as an int (1 - 12): 7
Enter aggregated review score (from 0.0 to 5.0): 4.3
Output movie 1: Terminator (10/1984), 4.050000/5
Output movie 2: Terminator 2 (7/1991), 4.300000/5
*/