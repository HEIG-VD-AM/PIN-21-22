#ifndef STATE_H
#define STATE_H

#include <vector>

#include "../thirdparty/nlohmann.h"
#include "particle.h"
#include "robot.h"
#include "position.h"

struct State {
   double time;
   Position worldOrigin;
   Position worldEnd;
   std::vector<RobotInfo> robots;
   std::vector<ParticleInfo> particles;
   NLOHMANN_DEFINE_TYPE_INTRUSIVE(State, time, worldOrigin, worldEnd, robots, particles);
   bool isEmpty = true;
};

#endif // STATE_H
