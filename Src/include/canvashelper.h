#ifndef CANVASHELPER_H
#define CANVASHELPER_H

#include <QWidget>
#include <QPen>
#include <QColor>

#include "state.h"
#include "timeline.h"

enum class ColorConstants {
    WORLD_BACKGROUND,
    PARTICLE,
    PARTICULE_OUTLINE,
    ROBOT_BACKGROUND,
    ROBOT_CAPTURE,
    CIRCLE_OUTLINE,

};

class CanvasHelper
{
public:
    CanvasHelper();
public:
    // Paint function called every frame
    void paint(QPainter *painter, QPaintEvent *event);
    void drawParticles(QPainter *painter, const std::vector<ParticleInfo>& particles);
    void drawRobots(QPainter *painter, const std::vector<RobotInfo>& robots);
	static void updatePositions(State& s, double dt);
    static QColor getColor(ColorConstants clr);
    State currentState;
    Timeline currentTimeline;
	double currentTime;
	bool interp;
    qreal scaleFactor;
private:
    QBrush particleBrush;
    QBrush robotBrush;
    QBrush background;
    QBrush captureBrush;
    QBrush circleBrush;
    QPen basePen;
    QFont textFont;
    QPen textPen;
};

#endif // CANVASHELPER_H
