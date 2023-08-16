#ifndef CANVAS_H
#define CANVAS_H

#include <QWidget>

#include "state.h"
#include "timeline.h"

class CanvasHelper;

class Canvas : public QWidget
{
    Q_OBJECT
public:
    Canvas(CanvasHelper *helper, QWidget *parent);

    void updateState(const State& newState);
    void updateTimeline(const Timeline& newTimeline);
protected:
    void paintEvent(QPaintEvent *event) override;
private:
    CanvasHelper *helper;
    int elapsed;
};

#endif // CANVAS_H
