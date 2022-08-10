#include "SensorsController.hpp"

#include <sys/sysinfo.h>

#include <QDebug>
#include <filesystem>
#include <sstream>

#include "CPU.hpp"
#include "Frequency.hpp"
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
    add_cpus();

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
                    auto row = new_row(std::make_unique<Subfeature>(subfeature));
                    group->appendRow(row);
                    has_inputs = true;
                }
            }
        }
        const std::filesystem::path path(chip.path());
        for (const auto& entry: std::filesystem::directory_iterator(path)) {
            auto name = entry.path().filename().string();
            if (name.find("freq") == 0 && name.find("input") != std::string::npos) {
                auto row = new_row(std::make_unique<Frequency>(entry.path().c_str()));
                group->appendRow(row);
                has_inputs = true;
            }
        }
        if (has_inputs) {
            root_->appendRow(group);
        } else {
            delete group;
        }
    }
}

void SensorsController::add_cpus() {
    const auto cpus = get_nprocs();
    auto* const group = new QStandardItem(QString(cpu_brand_string()));
    for (int i = 0; i < cpus; i++) {
        auto row = new_row(std::make_unique<CPU>(i));
        group->appendRow(row);
    }
    root_->appendRow(group);
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
            auto& source = sources_[idx];
            const auto* unit = source->unit();
            const auto value = source->update();
            val_col->setText(QString("%1%2").arg(value).arg(unit));
            if (value < min_col->data(MIN_ROLE).toDouble()) {
                min_col->setData(QVariant::fromValue(value), MIN_ROLE);
                min_col->setText(QString("%1%2").arg(value).arg(unit));
            }
            if (value > max_col->data(MAX_ROLE).toDouble() || max_col->text().isEmpty()) {
                max_col->setData(QVariant::fromValue(value), MAX_ROLE);
                max_col->setText(QString("%1%2").arg(value).arg(unit));
            }
        }
    }
}

QList<QStandardItem*> SensorsController::new_row(std::unique_ptr<Updateable> source) {
    auto* const name_col = new QStandardItem(QString::fromStdString(source->name()));
    name_col->setData(QVariant::fromValue(sources_.size()), ROW_SOURCE_ROLE);
    sources_.push_back(std::move(source));
    auto* const min_col = new QStandardItem();
    min_col->setData(QVariant::fromValue(std::numeric_limits<double>::max()), MIN_ROLE);
    auto* const max_col = new QStandardItem();
    max_col->setData(QVariant(0.0), MAX_ROLE);
    return {name_col, new QStandardItem(), min_col, max_col};
}