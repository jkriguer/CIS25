#ifndef ACTOR_CLASS
#define ACTOR_CLASS

#include "sam_types.h" //types

class Actor {
protected:
	const SharedBoard board;
	int xCoord = 0;
	int yCoord = 0;
	std::string label = "Unnamed Actor";
	char contact;
public:
	Actor(const SharedBoard&, int, int, std::string);
	Actor(const SharedBoard&, int, int, std::string, char);
	char getContact();
	std::string toString();
	double distanceTo(std::shared_ptr<Actor>);
	virtual ~Actor() = default; //deconstructor for subclass(es?)
	virtual void move();
};

#endif // !ACTOR
