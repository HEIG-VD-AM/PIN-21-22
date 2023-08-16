#ifndef POSITION_H
#define POSITION_H

#include "../thirdparty/nlohmann.h"

struct Position {
    double x; // horizontal coordinate
    double y; // vertical coordinate
    NLOHMANN_DEFINE_TYPE_INTRUSIVE(Position, x ,y);
};

#endif // POSITION_H
