#ifndef SAM_TYPES
#define SAM_TYPES

#include <vector>
#include <memory>

class Actor; //forward dec

using Board = std::vector<std::vector<std::unique_ptr<Actor>>>; //saves so much space
using SharedBoard = std::shared_ptr<Board>;

enum Bearing { N, E, S, W, NW, NE, SE, SW };
enum Faction { NEUTRAL, HOSTILE, FRIENDLY, UNKNOWN };


#endif // !SAM_TYPES