#include "SensorsController.hpp"

#include <sensors-c++/sensors.h>

#include <QDebug>
#include <QStandardItemModel>
#include <QTimer>

#include "SensorsUtil.hpp"
#include "Subfeature.hpp"

SensorsController::SensorsController(QObject* parent) : QObject(parent) {
    model_ = new QStandardItemModel(this);
    root_ = model_->invisibleRootItem();

    model_->setColumnCount(4);
    model_->setHeaderData(0, Qt::Horizontal, tr("Device"));
    model_->setHeaderData(1, Qt::Horizontal, tr("Value"));
    model_->setHeaderData(2, Qt::Horizontal, tr("Minimum"));
    model_->setHeaderData(3, Qt::Horizontal, tr("Maximum"));

    add_chips();

    timer_ = new QTimer(this);
    connect(timer_, &QTimer::timeout, this, [this]() { update(); });
    update();
    start();
}

void SensorsController::add_chips() {
    const auto chips = sensors::get_detected_chips();
    for (const auto& chip: chips) {
        auto* group = SensorsUtil::new_chip_row(chip);
        bool has_inputs = false;
        for (const auto& feature: chip.features()) {
            for (const auto& subfeature: feature.subfeatures()) {
                using sensors::subfeature_type;
                const auto type = subfeature.type();
                if ((type == subfeature_type::input ||
                     type == subfeature_type::vid ||
                     type == subfeature_type::unknown) &&
                    SensorsUtil::can_read(subfeature)) {
                    auto source = std::make_unique<Subfeature>(subfeature);
                    auto row = new_row(source->name());
                    row[0]->setData(static_cast<unsigned int>(sources.size()), ROW_SOURCE_ROLE);
                    sources.push_back(std::move(source));
                    group->appendRow(row);
                    has_inputs = true;
                }
            }
        }
        if (has_inputs) {
            root_->appendRow(group);
        } else {
            delete group;
        }
    }
}

SensorsController::~SensorsController() { stop(); }

void SensorsController::start(std::chrono::milliseconds tick) {
    timer_->start(tick);
}

void SensorsController::stop() { timer_->stop(); }

void SensorsController::update() {
    for (int i = 0; i < root_->rowCount(); i++) {
        auto* group = root_->child(i);
        for (int j = 0; j < group->rowCount(); j++) {
            auto* name_col = group->child(j, 0);
            auto* val_col = group->child(j, 1);
            auto* min_col = group->child(j, 2);
            auto* max_col = group->child(j, 3);
            auto idx = name_col->data(ROW_SOURCE_ROLE).toUInt();
            auto& source = sources[idx];
            const auto* unit = source->unit();
            val_col->setText(QString("%1%2").arg(source->update()).arg(unit));
            min_col->setText(QString("%1%2").arg(source->min()).arg(unit));
            max_col->setText(QString("%1%2").arg(source->max()).arg(unit));
        }
    }
}

QList<QStandardItem*> SensorsController::new_row(const std::string& name) {
    return {new QStandardItem(QString::fromStdString(name)), new QStandardItem(), new QStandardItem(), new QStandardItem()};
}