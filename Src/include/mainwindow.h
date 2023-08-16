#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <cmath>

#include "canvashelper.h"
#include "canvas.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
	QTimer *timerFrameRate;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    static size_t s_i;
	const double FPS = 24.0;
private slots:
    void on_actionQuit_triggered();

    void on_actionOpen_state_triggered();

    void on_actionOpen_timeline_triggered();

    void on_actionSave_state_triggered();

    void on_pushButton_clicked();

    void refreshTime();

	void Tick();

    void on_pushButton_2_clicked();

    void on_spx_speed_valueChanged(int arg1);

    void setScore(const State& newState);

    void on_spx_time_valueChanged(double arg1);

private:
    Ui::MainWindow *ui;
    CanvasHelper helper;
	double oldSpeed;
	bool interp = false;
	bool forceNoInterp = false;
    Canvas *canvas;
    void resizeEvent(QResizeEvent *event);
};
#endif // MAINWINDOW_H
