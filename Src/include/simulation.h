#ifndef SIMULATION_H
#define SIMULATION_H

#include "particle.h"
#include "constraints.h"
#include "robot.h"
#include "state.h"
#include "position.h"

#include <numeric>
#include <array>
#include <cmath>

namespace simulation {
	static int s_lastId = 0;
	double EPSILON = 0.1;//std::numeric_limits<double>::epsilon();

    enum CollisionType {
        ROBOT, PARTICLE
    };

    struct CollisionInfo {
        double time;
        bool collided;
        CollisionType type;
        RobotInfo* robot;
        int collidedObjectId;
    };

	/// Récupère le prochain identifiant de particule
	/// \return le prochaine identifiant de particule
	int getNextParticleId() {
		return ++s_lastId;
	}

	/// Fonction de décontamination : vérifie l'angle de décontamination
	/// si la condition est respectée, mange la particucle.
	/// \param s l'état du jeu actuel
	/// \param robot le robot qui doit manger une particule
	/// \param particleId l'identifiant de la partie qui doit être mangée si possible
	void decontaminate(State& s, RobotInfo& robot, int particleId) {
		ParticleInfo particle;
		size_t index;

		for (size_t i = 0; i < s.particles.size(); ++i) {
			if (s.particles[i].id == particleId) {
				particle = s.particles[i];
				index = i;
			}
		}

		double dy = robot.position.y - particle.position.y;
		double dx = robot.position.x - particle.position.x;
		double angle = 180 - atan2(dy, dx) * (180 / M_PI);
		if (fabs(robot.captureAngle) >= fabs(angle - robot.angle) + EPSILON) {
			robot.score += s.particles[index].radius * s.particles[index].radius * M_PI;
			s.particles.erase(s.particles.begin() + index);
		} else {
            robot.leftSpeed = robot.rightSpeed = 0;
        }
	}

	/// Désintègration d'une particule en 4 sous particules
	/// \param info la particule à désintégrer
	/// \return un tableau des 4 particules enfants créées.
	std::array<ParticleInfo, 4> disintegrate(const ParticleInfo& info) {
		double radius = (2. * info.radius) / (1. + M_SQRT2);
		ParticleInfo p1 = {
				.id = getNextParticleId(),
				.position = {
						info.position.x - radius / 2,
						info.position.y - radius / 2,
				},
				.radius = radius / 2
		};
		ParticleInfo p2 = {
				.id = getNextParticleId(),
				.position = {
						info.position.x - radius / 2,
						info.position.y + radius / 2
				},
				.radius = radius / 2
		};
		ParticleInfo p3 = {
				.id = getNextParticleId(),
				.position = {
						info.position.x + radius / 2,
						info.position.y - radius / 2
				},
				.radius = radius / 2
		};
		ParticleInfo p4 = {
				.id = getNextParticleId(),
				.position = {
						info.position.x + radius / 2,
						info.position.y + radius / 2
				},
				.radius = radius / 2
		};
		return std::array<ParticleInfo, 4>{p1, p2, p3, p4};
	}

	/// Vérifie si au temps time des particules doivent être désintégrées.
	/// \param s l'état du jeu actuel
	/// \param time le temps actuel
	/// \return si l'état du jeu a changé.
	bool explodeParticles(State& s, double time) {
		std::vector<ParticleInfo> particles;
		bool createNewState = false;
		for (const auto& p: s.particles) {
			if (time > p.explosionTimes[0][0]) {
				createNewState = true;
				if (p.explosionTimes.size() > 1) {
					auto newParticles = disintegrate(p);
					for (int i = 0; i < p.explosionTimes[1].size(); ++i) {
						newParticles[i].explosionTimes = std::vector<std::vector<double>>();
						newParticles[i].explosionTimes.emplace_back(std::vector<double>());
						newParticles[i].explosionTimes.at(0).push_back(p.explosionTimes[1][i]);
					}

					if (p.explosionTimes.size() > 2) {
						for (auto& np: newParticles) {
							np.explosionTimes.emplace_back(std::vector<double>());
						}

						for (int i = 0, j = 0; i < p.explosionTimes[2].size(); ++i) {
							if (i > 0 && (i) % 4 == 0) ++j;
							newParticles[j].explosionTimes.at(1).push_back(p.explosionTimes[2][i]);
						}
					}

					for (const auto& np: newParticles) {
						particles.push_back(np);
					}
				}
			} else {
				particles.push_back(p);
			}
		}

		s.particles = particles;
		return createNewState;
	}


	/// Calcule la distance euclidienne entre deux positions selon la formule
	/// \f[
	///		\delta(p_1, p_2) = \sqrt{(x_1 - x_2)^2 + (y_1 - y_2)^2}
	/// \f]
	/// \param p1
	/// \param p2
	/// \return la distance entre les deux positions
    double euclideanDistance(const Position& p1, const Position& p2) {
        return std::sqrt(std::pow(p1.x - p2.x, 2) + std::pow(p1.y - p2.y, 2));
    }

	/// Calcule le temps où a lieu une collisions entre un robot et un objet générique
	/// de la scène, pour autant qu'elle est lieu.
	/// \tparam T le type de l'objet de la scène passée.
	/// \param time le temps auquel on doit chercher un peu avant et un peu après pour trouver le temps exact
	/// \param r le robot
	/// \param sceneObj  l'objet de la scène
	/// \param isInCollision est-ce que les objets sont déjà en collision au temps passé
	/// \return le temps de la collision si elle à eu lieu, -1 autrement.
    template<typename T>
    double collisionTime(double time, const RobotInfo& r, const T& sceneObj, bool isInCollision = false) {
        if(time < std::numeric_limits<float>::epsilon()) {

            return -1;
        }

        Position position = getNextPosition(r, time);
        double distance = euclideanDistance(position, sceneObj.position);
        double radius = r.radius + sceneObj.radius;
        if (distance >= radius - EPSILON && distance <= radius + EPSILON) {
            return time; // collision at this moment
        } else if (distance < radius - EPSILON) {
            return collisionTime(time / 2, r, sceneObj, true);
        } else if (distance > radius + EPSILON && isInCollision) {
            return collisionTime(time * 1.5, r, sceneObj, true);
        }  else {
            return -1;
        }
    }

	/// Test si une collision à eu lieu entre l'ancien et le nouveau state.
	/// \param newState l'ancien state
	/// \param oldState le nouveau state
	/// \return une structure CollisionInfo, donnant toutes les informations sur la potentielle collision
    std::vector<CollisionInfo> collisionTest(State& newState, const State& oldState) {
        std::vector<CollisionInfo> collisions;

        size_t nbRobots = newState.robots.size();
        size_t nbParticles = newState.particles.size();
        double time = newState.time - oldState.time;
        for (size_t i = 0; i < nbRobots; i++) {
            for (size_t j = i + 1; j < nbRobots; j++) {
                double collideTime = collisionTime(time, oldState.robots[i], oldState.robots[j]);
                if (collideTime != -1) {
                    collisions.emplace_back((CollisionInfo) {
                            .time = newState.time + collideTime,
                            .collided = true,
                            .type = ROBOT,
                            .robot = &newState.robots[i],
                            .collidedObjectId = newState.robots[j].id
                    });
                } else {
                    continue;
                }
            }
            for (size_t j = 0; j < nbParticles; j++) {
                double collideTime = collisionTime(time, oldState.robots[i], oldState.particles[j]);
                if (collideTime != -1) {
                    collisions.emplace_back((CollisionInfo) {
                            .time = newState.time + collideTime,
                            .collided = true,
                            .type = PARTICLE,
                            .robot = &newState.robots[i],
                            .collidedObjectId = newState.particles[j].id
                    });
                } else {
                    continue;
                }
            }
        }
        return collisions;
    }
}
#endif //SIMULATION_H
