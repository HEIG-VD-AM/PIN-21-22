#ifndef PARTICLE_H
#define PARTICLE_H

#include <vector>

#include "../thirdparty/nlohmann.h"
#include "position.h"


struct ParticleInfo {
   int id;             // unique identifier
   Position position;  // (x,y) coordinates of the particle
   double radius;      // radius of the circular particle
   std::vector<std::vector<double>> explosionTimes;
   bool isTargeted;
   NLOHMANN_DEFINE_TYPE_INTRUSIVE(ParticleInfo, id, position, radius, explosionTimes);
};

#endif // PARTICLE_H
