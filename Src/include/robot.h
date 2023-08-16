#ifndef ROBOT_H
#define ROBOT_H

#include "../thirdparty/nlohmann.h"
#include "position.h"
#include "particle.h"

struct RobotInfo {
   int id;              // unique identifier
   Position position;   // (x,y) coordinates of the robot in the world (in pixels)
   double radius;       // radius of the circular robot. (pixels)
   double angle;        // direction in which the robot moves. [0,360[ in degrees. 0 = 3 o'clock, 90 = noon
   double captureAngle; // c.f. décontamination
   double leftSpeed;    // linear speed of the leftmost part of the robot in pixels/sec
   double rightSpeed;   // linear speed of the rightmost part of the robot in pixels/sec
   double score;        // c.f. décontamination
   bool isEmpty;        // optional
   NLOHMANN_DEFINE_TYPE_INTRUSIVE(RobotInfo, id, position, radius, angle, captureAngle, leftSpeed, rightSpeed, score);
};

void setNextPosition(RobotInfo& robot, double deltaTime);
Position getNextPosition(const RobotInfo &robot, double deltaTime);
#endif // ROBOT_H
