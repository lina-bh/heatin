#include "SensorsController.h"

#include <QDebug>
#include <sensors-c++/error.h>

SensorsController::SensorsController(QObject* parent) : QObject(parent) {
    model_ = new QStandardItemModel(this);
    root_ = model_->invisibleRootItem();

    model_->setColumnCount(2);

    auto chips = sensors::get_detected_chips();
    for (auto chip: chips) {
        add_chip(chip);
    }

    timer_ = new QTimer(this);
    connect(timer_, &QTimer::timeout, this, [this]() { update(); });
    update();
    start();
}

SensorsController::~SensorsController() {
    stop();
}

QStandardItemModel* SensorsController::model() const noexcept {
    return model_;
}

void SensorsController::add_chip(sensors::chip_name& chip) {
    bool has_inputs = false;
    auto chip_name = QString::fromStdString(chip.name());
    auto adapter = QString::fromUtf8(chip.bus().adapter_name().data());
    auto name = QString("%1 %2")
        .arg(adapter)
        .arg(chip_name);
    auto* row = new QStandardItem(name);
    for (auto feature: chip.features()) {
        // row->appendRow(add_feature(feature));
        auto maybe = feature.subfeature(sensors::subfeature_type::input);
        if (maybe.has_value() && can_read(maybe.value())) {
            row->appendRow(add_subfeature(maybe.value()));
            has_inputs = true;
        }
    }
    if (has_inputs) {
        root_->appendRow(row);
    } else {
        delete row;
    }
}

QStandardItem* SensorsController::add_feature(sensors::feature& feature) {
    auto name = QString::fromUtf8(feature.name().data());
    auto* row = new QStandardItem(name);
    for (auto subfeature: feature.subfeatures()) {
        if (can_read(subfeature)) {
            row->appendRow(add_subfeature(subfeature));
        }
    }
    return row;
}

const QList<QStandardItem*> SensorsController::add_subfeature(sensors::subfeature& subfeature) {
    auto name = QString::fromUtf8(subfeature.name().data());
    auto* name_col = new QStandardItem(name);
    auto* value_col = new QStandardItem(QString("test"));

    subfeatures_.push_back({subfeature, value_col});

    return {name_col, value_col};
}

void SensorsController::start() {
    timer_->start(2000);
}

void SensorsController::stop() {
    timer_->stop();
}

void SensorsController::update() {
    for (auto pair: subfeatures_) {
        auto subfeature = pair.first;
        auto column = pair.second;
        try {
            auto value = subfeature.read();
            column->setText(QString("%1").arg(value));
        } catch (sensors::io_error& ex) {
            column->setText(QString("cannot be read %1").arg(static_cast<int>(subfeature.type())));
        }
    }
}

bool SensorsController::can_read(sensors::subfeature& subfeature) {
    if (subfeature.readable()) {
        try {
            subfeature.read();
        } catch (sensors::io_error& ex) {
            return false;
        }
        return true;
    } else {
        return false;
    }
}