#include "SensorsTask.h"

#include <QDebug>

SensorsTask::SensorsTask(QObject *parent) : QObject(parent) {
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, [this]() { update(); });
}

void SensorsTask::start() {
    timer->start(2000);
}

void SensorsTask::stop() {
    timer->stop();
}

void SensorsTask::update() {
    qInfo() << "sensorstask::update called";
}