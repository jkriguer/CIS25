#ifndef date_struct
#define date_struct
#include <iostream>
#include "scanner.h"

struct Date {
	int year = 1899;
	int month = 0;
	void inputDate();
};

std::ostream& operator<<(std::ostream&, const Date&);
#endif // !date_struct