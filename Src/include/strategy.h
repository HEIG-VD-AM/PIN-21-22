#ifndef STRATEGY_H
#define STRATEGY_H

#include "constraints.h"
#include "robot.h"
#include "particle.h"
#include "utility.h"

#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>

namespace strategy {

    void goTowardParticle(const Constraints& c, const int time, RobotInfo& robot) {

        if(time % (int) c.CommandTimeInterval) {
            robot.rightSpeed = robot.leftSpeed = c.maxForwardSpeed;
        }
    }

    void rotateTowardParticle(const Constraints& c, const int time, RobotInfo& robot, const ParticleInfo& particle) {

        if(time % (int) c.CommandTimeInterval) {

            double dy = robot.position.y - particle.position.y;
            double dx = robot.position.x - particle.position.x;
            double angle = 180 - atan2(dy, dx) * (180 / M_PI);
            double speed = fmin(c.maxForwardSpeed, c.maxBackwardSpeed);

            if (utility::wrapAngle(robot.angle + 180.0) >= angle) {
                robot.rightSpeed = speed;
                robot.leftSpeed = -speed;
            } else {
                robot.rightSpeed = -speed;
                robot.leftSpeed = speed;
            }
        }
    }

    double euclideanDistance(const Position& p1, const Position& p2) {
        return std::sqrt(std::pow(p1.x - p2.x, 2) + std::pow(p1.y - p2.y, 2));
    }

    ParticleInfo robotSelectParticle(const RobotInfo& robot, std::vector<ParticleInfo> particles) {

        std::vector<double> scorePerDistance;

        for(ParticleInfo& particle : particles) {
            scorePerDistance.push_back((particle.radius * particle.radius * M_PI) / euclideanDistance(robot.position, particle.position));
        }
        std::vector<std::pair<double, ParticleInfo>> pairs;

        for(size_t i = 0; i < scorePerDistance.size(); ++i) {
            pairs.push_back(std::make_pair(scorePerDistance[i], particles[i]));
        }

        std::sort(pairs.begin(), pairs.end(), std::greater<double>());

        for(size_t i = 0; i < pairs.size(); ++i) {

            if(pairs.at(i).second.isTargeted) {
                return pairs.at(i).second;
            }
        }

        return pairs.at(0).second;
    }
}

#endif STRATEGY_H
