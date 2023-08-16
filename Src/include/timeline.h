#ifndef TIMELINE_H
#define TIMELINE_H

#include <vector>

#include "state.h"

struct Timeline {
   std::vector<State> states;
   NLOHMANN_DEFINE_TYPE_INTRUSIVE(Timeline, states);
   bool isEmpty;
};



#endif // TIMELINE_H
