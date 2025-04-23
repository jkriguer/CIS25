#ifndef SAM_TYPES
#define SAM_TYPES

#include <vector>
#include <memory>

class Actor; //forward dec

using Board = std::vector<std::vector<std::unique_ptr<Actor>>>; //saves so much space
using SharedBoard = std::shared_ptr<Board>;

enum class Bearing { N = 8, E = 6, S = 2, W = 4, NW = 7, NE = 9, SE = 3, SW = 1 }; //numpad
enum class Faction { NEUTRAL, HOSTILE, FRIENDLY, UNKNOWN };


#endif // !SAM_TYPES