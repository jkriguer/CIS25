#ifndef customer_structure
#define customer_structure
#include "Address.h"

struct Customer {
	int customerID;
	std::string customerName;
	Address customerAddress;
};

#endif
