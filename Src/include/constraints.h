#ifndef CONSTRAINTS_H
#define CONSTRAINTS_H

#include "../thirdparty/nlohmann.h"

struct Constraints {
	double CommandTimeInterval;
	double maxBackwardSpeed;
	double maxForwardSpeed;
	NLOHMANN_DEFINE_TYPE_INTRUSIVE(Constraints, CommandTimeInterval, maxBackwardSpeed, maxForwardSpeed);
};

#endif //CONSTRAINTS_H
