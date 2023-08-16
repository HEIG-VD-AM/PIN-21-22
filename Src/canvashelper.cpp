#include <QPainter>
#include <QPaintEvent>
#include <QString>
#include <cmath>

#include "include/canvashelper.h"
#include "include/utility.h"
#include "include/robot.h"

QColor CanvasHelper::getColor(ColorConstants clr) {
    switch(clr) {
    case ColorConstants::WORLD_BACKGROUND:
        return QColor(190, 190, 190);
    case ColorConstants::PARTICLE:
        return QColor(255, 99, 100);
    case ColorConstants::PARTICULE_OUTLINE:
        return QColor(0, 0, 0);
    case ColorConstants::ROBOT_BACKGROUND:
        return QColor(255, 255, 255);
    case ColorConstants::ROBOT_CAPTURE:
        return QColor(160, 160, 160);
    case ColorConstants::CIRCLE_OUTLINE:
        return QColor(0, 0, 0);
    default:
        return QColor(255, 255, 255);
    }
}

CanvasHelper::CanvasHelper()
{
    background = QBrush(getColor(ColorConstants::WORLD_BACKGROUND));
    robotBrush = QBrush(getColor(ColorConstants::ROBOT_BACKGROUND));
    captureBrush = QBrush(getColor(ColorConstants::ROBOT_CAPTURE));
    particleBrush = QBrush(getColor(ColorConstants::PARTICLE));
    basePen = QPen(getColor(ColorConstants::CIRCLE_OUTLINE));
    basePen.setWidth(1);
    textPen = QPen(Qt::white);
    textFont.setPixelSize(50);
    scaleFactor = 1;
}

void CanvasHelper::drawParticles(QPainter *painter, const std::vector<ParticleInfo>& particles) {
    painter->setBrush(particleBrush);
    painter->setPen(basePen);
    for (const ParticleInfo& info: particles) {
        qreal radius = info.radius * scaleFactor;
        qreal posX = (info.position.x - currentState.worldOrigin.x) * scaleFactor;
        qreal posY = (info.position.y - currentState.worldOrigin.y) * scaleFactor;
        painter->drawEllipse(QPointF(posX, posY), radius, radius);

        // Text drawing
        QFont font = painter->font();
        if(info.id < 10){
            font.setPointSize(12 * fmax(scaleFactor, 0.5) * (0.05 * radius));
        }
        else{
            font.setPointSize(12 * fmax(scaleFactor, 0.5) * (0.04 * radius));
        }
        QFontMetrics fm (font);
        int textWide = fm.horizontalAdvance(QString::number(info.id));
        int textTall = fm.height();
        painter->setFont(font);
        painter->drawText(QRectF(posX - textWide / 2, posY - textTall / 2, textWide, textTall), QString::number(info.id));


    }
    painter->setBrush(Qt::NoBrush);
    painter->setPen(Qt::NoPen);
}

void CanvasHelper::updatePositions(State& s, double dt) {
	for (auto& r : s.robots) {
		setNextPosition(r, dt);
	}
}

void CanvasHelper::drawRobots(QPainter *painter, const std::vector<RobotInfo>& robots) {
    for (const RobotInfo& info: robots) {
        qreal radius = info.radius * scaleFactor;
        qreal posX = (info.position.x - currentState.worldOrigin.x) * scaleFactor;
        qreal posY = (info.position.y - currentState.worldOrigin.y) * scaleFactor;
        painter->setBrush(robotBrush);
        painter->setPen(basePen);
        painter->drawEllipse(QPointF(posX, posY), radius, radius);
        // Draw capture angle
        QRectF boundingBox(posX - radius, posY - radius, radius * 2, radius * 2);
        qreal startAng = utility::wrapAngle(360 - info.angle - info.captureAngle) * 16;
        qreal spanAng = 2 * info.captureAngle * 16;
        painter->setBrush(captureBrush);
        painter->drawPie(boundingBox, startAng, spanAng);
        // Draw direction circle
        painter->setBrush(robotBrush);
        painter->setPen(basePen);
        painter->drawEllipse(QPointF(posX + cos(info.angle * M_PI / 180) * radius * 0.6,
                 posY + sin(info.angle * M_PI / 180) * radius * 0.6), 3 * scaleFactor, 3 * scaleFactor);
        // Text drawing
        QFont font = painter->font();
        font.setPointSize(12 * fmax(scaleFactor, 0.5) * (0.05 * radius));
        QFontMetrics fm (font);
        int textWide = fm.horizontalAdvance(QString::number(info.id));
        int textTall = fm.height();
        painter->setFont(font);
        painter->drawText(QRectF(posX - textWide / 2, posY - textTall / 2, textWide, textTall), QString::number(info.id));
    }
    painter->setBrush(Qt::NoBrush);
    painter->setPen(Qt::NoPen);
}

// Paint Event called each frame
void CanvasHelper::paint(QPainter *painter, QPaintEvent *event) {
    if (currentState.time != -1) {
        // Background scene
        painter->fillRect(event->rect(), background);
        painter->save();
		if (interp) {
			State interpState = currentState;
			double dt = currentTime - currentState.time;
			interpState.time = currentTime;
			updatePositions(interpState, dt);
			drawParticles(painter, interpState.particles);
			drawRobots(painter, interpState.robots);
		} else {
        	drawParticles(painter, currentState.particles);
        	drawRobots(painter, currentState.robots);
		}
        painter->restore();
    }

}

