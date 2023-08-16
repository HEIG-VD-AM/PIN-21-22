#include <QTimer>
#include <QPainter>
#include <iostream>

#include "include/canvas.h"
#include "include/canvashelper.h"
#include "include/mainwindow.h"

Canvas::Canvas(CanvasHelper *helper, QWidget *parent)
    : QWidget(parent), helper(helper)
{
    // sentinel value: -1 means there is no active state
    helper->currentState = { .time = -1, .worldOrigin = {0, 0}, .worldEnd = {0, 0}, .robots = {}, .particles = {}};
    helper->currentTimeline = {.states = {{.time = -1, .worldOrigin = {0, 0}, .worldEnd = {0, 0}, .robots = {}, .particles = {}}}};
}

void Canvas::updateState(const State& newState) {
    this->helper->currentState = newState;
    int worldHeight = helper->currentState.worldEnd.y - helper->currentState.worldOrigin.y;
    int worldWidth = helper->currentState.worldEnd.x - helper->currentState.worldOrigin.x;
    int windowHeight = ((MainWindow*)parentWidget())->size().height() - 100;
    int windowWidth = ((MainWindow*)parentWidget())->size().width() - 5;
    int sideLength = fmax(200,fmin(windowHeight, windowWidth));
    helper->scaleFactor = fmin((qreal) sideLength / worldHeight, (qreal)sideLength / worldWidth);
    resize(sideLength, sideLength);
    update();
}

void Canvas::updateTimeline(const Timeline& newTimeline) {
    this->helper->currentTimeline = newTimeline;
    updateState(newTimeline.states[0]);
}

void Canvas::paintEvent(QPaintEvent *event) {
    QPainter painter;
    painter.begin(this);
    painter.setRenderHint(QPainter::Antialiasing);
    helper->paint(&painter, event);
    painter.end();
}
