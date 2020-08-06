#include "SensorsController.hpp"

#include <qnamespace.h>
#include <sensors-c++/error.h>
#include <sensors-c++/sensors.h>

#include <QTimer>
#include <string_view>
#include <utility>

#include "CPU.h"
#include "Chip.hpp"
#include "Exceptions.hpp"
#include "SensorsUtil.hpp"

SensorsController::SensorsController(QObject* parent) : QObject(parent) {
    model_ = new QStandardItemModel(this);
    root_ = model_->invisibleRootItem();

    model_->setColumnCount(4);
    model_->setHeaderData(0, Qt::Horizontal, tr("Device"));
    model_->setHeaderData(1, Qt::Horizontal, tr("Value"));
    model_->setHeaderData(2, Qt::Horizontal, tr("Minimum"));
    model_->setHeaderData(3, Qt::Horizontal, tr("Maximum"));

    const auto chips = sensors::get_detected_chips();
    for (const auto& chip: chips) {
        add_chip(chip);
    }

    timer_ = new QTimer(this);
    connect(timer_, &QTimer::timeout, this, [this]() { update(); });
    update();
    start();
}

SensorsController::~SensorsController() { stop(); }

void SensorsController::add_chip(const sensors::chip_name& chip) {
    // try {
    //     Chip group(chip);
    //     root_->appendRow(group.row());
    //     chips_.push_back(group);
    // } catch (NoSensors& none) {
    // }
    const auto mb = Chip::create_chip(chip);
    if (mb.has_value()) {
        const auto& chip = mb.value();
        root_->appendRow(chip.row());
        chips_.push_back(chip);
    }
}

void SensorsController::start(std::chrono::milliseconds tick) {
    timer_->start(tick);
}

void SensorsController::stop() { timer_->stop(); }

void SensorsController::update() {
    for (auto& group: chips_) {
        group.update();
    }
}