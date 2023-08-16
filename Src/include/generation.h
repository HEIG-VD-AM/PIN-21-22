#ifndef GENERATION_H
#define GENERATION_H

#include "timeline.h"
#include "constraints.h"
#include "robot.h"
#include "simulation.h"
#include <string>

#define TIME_INTERVAL (1./24)

namespace generation {
	/// Fonction de génération de timeline
	/// \param s l'état initial du jeu
	/// \param c les contraintes du jeu
	/// \return la timeline générée à partir des conditions initiales.
    Timeline generateTimeline(const State& s, const Constraints& c) {

        Timeline tl = Timeline();
        tl.states.emplace_back(s);
        State lastState = s;
		simulation::s_lastId = s.particles.size() - 1;
        size_t nParticles = s.particles.size();
        double currentTime = 0;
        while (nParticles != 0) {
            currentTime += TIME_INTERVAL;
            State newState;
            newState.worldOrigin = s.worldOrigin;
            newState.worldEnd = s.worldEnd;
            newState.time = currentTime;
            newState.isEmpty = false;
            newState.particles = lastState.particles;
            newState.robots = lastState.robots;
            bool createNewState = simulation::explodeParticles(newState, currentTime);

            if (createNewState) {
                tl.states.emplace_back(newState);
                lastState = newState;
                continue;
            }

            for (RobotInfo &r: newState.robots) {
                setNextPosition(r, TIME_INTERVAL);
            }
            std::vector<simulation::CollisionInfo> collisions = simulation::collisionTest(newState, lastState);
            for (simulation::CollisionInfo &collision: collisions) {
                if (!collisions.empty()) {
                    newState.time = collision.time;
                    if (collision.type == simulation::CollisionType::ROBOT) {
                        for (auto &r: newState.robots) {
                            if (r.id == collision.collidedObjectId) {
                                setNextPosition(r, collision.time - lastState.time);
                                r.leftSpeed = 0;
                                r.rightSpeed = 0;
                                collision.robot->leftSpeed = 0;
                                collision.robot->rightSpeed = 0;
                                break;
                            }
                        }
                    } else if (collision.type == simulation::CollisionType::PARTICLE) {
                        simulation::decontaminate(newState, *collision.robot, collision.collidedObjectId);
                    }
                }
            }
            tl.states.emplace_back(newState);
            lastState = newState;
			nParticles = lastState.particles.size();
        }
        return tl;
    }
}

#endif //GENERATION_H