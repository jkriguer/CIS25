#ifndef ACTOR_CLASS
#define ACTOR_CLASS

#include "sam_types.h" //types
#include <string>


class Actor {
protected:
	const SharedBoard board;
	int xCoord = 0;
	int yCoord = 0;
	std::string label = "Unnamed Actor";
	int contact;
public:
	Actor(const SharedBoard&, int, int, std::string);
	virtual ~Actor() = default; //deconstructor for subclass(es?)
	int getContact();
};

#endif // !ACTOR
