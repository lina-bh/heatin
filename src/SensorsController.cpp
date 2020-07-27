#include "SensorsController.hpp"

#include <qnamespace.h>
#include <sensors-c++/error.h>
#include <sensors-c++/sensors.h>

#include <QTimer>
#include <string_view>
#include <utility>

#include "CPU.h"
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
    bool has_inputs = false;
    const auto module = QString::fromUtf8(chip.prefix().data());
    QString device_name;
    if (module == "k10temp") {
        device_name = QString::fromUtf8(get_cpu_name());
    } else {
        const auto device_name_mb = pci_.device_name(chip);
        if (device_name_mb.has_value()) {
            device_name = QString::fromStdString(device_name_mb.value());
        }
    }
    QString name;
    if (!device_name.isEmpty()) {
        name = QString("%1 (%2)").arg(device_name.trimmed()).arg(module);
    } else {
        name = QString(module);
    }
    auto* const row = new QStandardItem(name);
    for (const auto& feature: chip.features()) {
        // row->appendRow(add_feature(feature));
        auto maybe = feature.subfeature(sensors::subfeature_type::input);
        if (maybe.has_value() && SensorsUtil::can_read(maybe.value())) {
            row->appendRow(add_measurement(maybe.value()));
            has_inputs = true;
        }
    }
    if (has_inputs) {
        root_->appendRow(row);
    } else {
        delete row;
    }
}

QList<QStandardItem*> SensorsController::add_measurement(const sensors::subfeature& subfeature) {
    auto name = QString::fromStdString(subfeature.feature().label());
    auto* name_col = new QStandardItem(name);

    Measurement sub(subfeature);

    this->measurements_.push_back(sub);

    return {name_col, sub.value_col, sub.min_col, sub.max_col};
}

void SensorsController::start(std::chrono::milliseconds tick) {
    timer_->start(tick);
}

void SensorsController::stop() { timer_->stop(); }

void SensorsController::update() {
    for (auto& sub: measurements_) {
        const auto* unit = SensorsUtil::unit(sub.feature.feature().type());
        try {
            auto value = sub.feature.read();
            sub.value_col->setText(QString("%1%2").arg(value).arg(unit));
            if (value < sub.min || sub.min_col->text().isEmpty()) {
                sub.min = value;
                sub.min_col->setText(QString("%1%2").arg(value).arg(unit));
            }
            if (value > sub.max || sub.max_col->text().isEmpty()) {
                sub.max = value;
                sub.max_col->setText(QString("%1%2").arg(value).arg(unit));
            }
        } catch (sensors::io_error& ex) {
            sub.value_col->setText(tr("cannot be read %1").arg(ex.what()));
        }
    }
}