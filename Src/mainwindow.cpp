#include <QTimer>
#include <QFileDialog>
#include <QResizeEvent>
#include <cmath>
#include <string>
#include <sstream>

#include "include/mainwindow.h"
#include "ui_mainwindow.h"
#include "include/canvas.h"
#include "include/json.h"
#include "include/state.h"
#include "include/timeline.h"
#include "include/robot.h"

size_t MainWindow::s_i = 0;
const double MS_IN_SEC = 1000.0;

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
	ui->setupUi(this);
	// 2D canvas configuration
	canvas = new Canvas(&helper, this);
	canvas->setMinimumHeight(200);
	canvas->resize(0, 0);
	canvas->move(5, 70);
    this->layout()->addWidget(canvas);
	timerFrameRate = new QTimer(this);
	connect(timerFrameRate, &QTimer::timeout, this, &MainWindow::Tick);
}

void MainWindow::Tick() {
    refreshTime();
	if (forceNoInterp) {
		forceNoInterp = false;
		return;
	}
	helper.interp = (!helper.currentTimeline.states.empty() && helper.currentTimeline.states.size() > s_i + 1
					 && (ui->spx_time->value() > helper.currentState.time));
	if (helper.interp)
		update();
}

void MainWindow::resizeEvent(QResizeEvent* event) {
	if (helper.currentState.time == -1) return;
	QMainWindow::resizeEvent(event);
	int worldHeight = helper.currentState.worldEnd.y - helper.currentState.worldOrigin.y;
	int worldWidth = helper.currentState.worldEnd.x - helper.currentState.worldOrigin.x;
	int windowHeight = event->size().height() - 100;
	int windowWidth = event->size().width() - 5;
	int sideLength = fmax(200, fmin(windowHeight, windowWidth));
	helper.scaleFactor = fmin((qreal) sideLength / worldHeight, (qreal) sideLength / worldWidth);
	canvas->resize(sideLength, sideLength);
	canvas->update();
}


MainWindow::~MainWindow() {
	delete ui;
}


void MainWindow::on_actionQuit_triggered() {
	QApplication::quit();
}


void MainWindow::on_actionOpen_state_triggered() {
	QString filename = QFileDialog::getOpenFileName(this, tr("Open File"), QDir::homePath(), tr("stat (*.stat)"));
	State newState = import<State>(filename);
	if (!newState.isEmpty) {
		this->setWindowTitle(filename);
		canvas->updateTimeline({.states = {newState}, .isEmpty = false});
		canvas->updateState(newState);
		ui->pushButton->setEnabled(true);
		ui->pushButton_2->setEnabled(true);
		ui->spx_speed->setEnabled(true);
		ui->spx_time->setEnabled(true);
		ui->actionSave_state->setEnabled(true);
        setScore(newState);
	}
}


void MainWindow::on_actionOpen_timeline_triggered() {
	QString filename = QFileDialog::getOpenFileName(this, tr("Open File"), QDir::homePath(), tr("timeline (*.tlin)"));
	Timeline newTimeline = import<Timeline>(filename);
	if (!newTimeline.isEmpty) {
		this->setWindowTitle(filename);
		ui->pushButton->setEnabled(true);
		ui->pushButton_2->setEnabled(true);
		ui->spx_speed->setEnabled(true);
		ui->spx_time->setEnabled(true);
		ui->actionSave_state->setEnabled(true);
        setScore(newTimeline.states[0]);
        ui->spx_time->setValue(0);
		helper.currentTime = 0;
        s_i = 0;
        ui->spx_time->setMaximum(newTimeline.states[newTimeline.states.size()-1].time + 1./24);
		canvas->updateTimeline(newTimeline);
	}

}


void MainWindow::on_actionSave_state_triggered() {

	QString filename = QFileDialog::getSaveFileName(this, "Save file", ".stat", ".stat");
	exportState(this->helper.currentState, filename);
}



void MainWindow::on_pushButton_clicked() {
    ui->pushButton_2->setText("|>");
    s_i = 0;
    helper.currentTime = 0;
    timerFrameRate->stop();
    ui->spx_time->setValue(0);
    setScore(this->helper.currentTimeline.states[0]);
    canvas->updateState(this->helper.currentTimeline.states[0]);
}

void MainWindow::on_pushButton_2_clicked() {

	if (timerFrameRate->isActive()) {
        timerFrameRate->stop();
        ui->pushButton_2->setText("|>");
	} else {
		timerFrameRate->start((MS_IN_SEC / FPS) / ui->spx_speed->value());
        ui->pushButton_2->setText("||");
	}
}

void MainWindow::refreshTime() {
	ui->spx_time->setValue(ui->spx_time->value() + (1. / FPS));
	helper.currentTime = ui->spx_time->value();
	if (ui->spx_time->value() > this->helper.currentTimeline.states[s_i + 1].time) {
		if (this->helper.currentTimeline.states.size() > s_i + 1) {
			++s_i;
			canvas->updateState(this->helper.currentTimeline.states[s_i]);
			setScore(this->helper.currentTimeline.states[s_i]);
			forceNoInterp = true;
		} else {
			timerFrameRate->stop();
		}
	}
}

void MainWindow::setScore(const State& newState) {

	//Score update
	size_t scoreTotalRobot = 0;
	size_t scoreTotalParticle = 0;

	for (RobotInfo robot: newState.robots) {
		scoreTotalRobot += robot.score;
	}
	for (ParticleInfo particle: newState.particles) {
		scoreTotalParticle += M_PI * particle.radius * particle.radius;
	}

	std::ostringstream o;
	o << scoreTotalRobot << " / " << scoreTotalParticle;
	QString s = QString::fromStdString(o.str());
	ui->score->setText(s);
}

void MainWindow::on_spx_speed_valueChanged(int arg1) {
	timerFrameRate->setInterval((MS_IN_SEC / FPS) / ui->spx_speed->value());
}


void MainWindow::on_spx_time_valueChanged(double arg1)
{

}

