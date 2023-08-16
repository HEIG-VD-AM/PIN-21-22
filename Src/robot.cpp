#include "include/robot.h"
#include "include/position.h"
#include "include/utility.h"
#include <cmath>

void setNextPosition(RobotInfo& robot, double deltaTime) {

	double angleRobot = robot.angle * M_PI / 180;

	if (robot.leftSpeed == robot.rightSpeed) {
		Position deltaPos = {
				robot.leftSpeed * deltaTime * cos(angleRobot),
				robot.leftSpeed * deltaTime * sin(angleRobot)
		};

		robot.position.x += deltaPos.x;
		robot.position.y += deltaPos.y;
	} else if (robot.leftSpeed == -robot.rightSpeed) {
		double omega = (robot.leftSpeed - robot.rightSpeed) / (2 * robot.radius);
		robot.angle = (angleRobot + omega * deltaTime) * 180 / M_PI;
		robot.angle = utility::wrapAngle(robot.angle);
	} else {
		double R = robot.radius * (robot.leftSpeed + robot.rightSpeed) / (robot.leftSpeed - robot.rightSpeed);
		double omega = (robot.leftSpeed - robot.rightSpeed) / (2 * robot.radius);
		Position dt = {R * cos(angleRobot), R * sin(angleRobot)};
		Position dr = {R * -sin(angleRobot), R * cos(angleRobot)};
		robot.position.x += dt.x * sin(omega * deltaTime) + dr.x * (1 - cos(omega * deltaTime));
		robot.position.y += dt.y * sin(omega * deltaTime) + dr.y * (1 - cos(omega * deltaTime));
        robot.angle = (angleRobot + omega * deltaTime) * 180 / M_PI;
        robot.angle = utility::wrapAngle(robot.angle);
	}
 }

Position getNextPosition(const RobotInfo &robot, double deltaTime) {
    RobotInfo robotCopy = robot;
    setNextPosition(robotCopy, deltaTime);
    return robotCopy.position;
}