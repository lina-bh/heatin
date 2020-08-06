#include "Chip.hpp"

#include <sensors-c++/sensors.h>

#include <QStandardItem>

#include "Exceptions.hpp"
#include "PCI.hpp"
#include "SensorsUtil.hpp"
#include "Subfeature.hpp"

Chip::Chip(const sensors::chip_name& chip) {
    const auto module = QString::fromUtf8(chip.prefix().data());
    QString device_name;
    // if (module == "k10temp") {
    //     device_name = QString::fromUtf8(get_cpu_name());
    // } else {
    const auto device_name_mb = PCI::device_name(chip);
    if (device_name_mb.has_value()) {
        device_name = QString::fromStdString(device_name_mb.value());
    }
    // }
    QString name;
    if (!device_name.isEmpty()) {
        name = QString("%1 (%2)").arg(device_name.trimmed()).arg(module);
    } else {
        name = QString(module);
    }
    root_ = new QStandardItem(name);
    bool has_inputs = false;
    for (const auto& feature: chip.features()) {
        for (const auto& subfeature: feature.subfeatures()) {
            using sensors::subfeature_type;
            const auto type = subfeature.type();
            if ((type == subfeature_type::input ||
                 type == subfeature_type::pulses ||
                 type == subfeature_type::vid ||
                 type == subfeature_type::unknown) &&
                SensorsUtil::can_read(subfeature)) {
                root_->appendRow(add_subfeature(subfeature));
                has_inputs = true;
            }
        }
    }

    if (!has_inputs) {
        delete root_;
        throw NoSensors();
    }
}

std::optional<Chip> Chip::create_chip(const sensors::chip_name& chip) {
    try {
        return {Chip(chip)};
    } catch (NoSensors& none) {
        return std::nullopt;
    }
}

QList<QStandardItem*> Chip::add_subfeature(const sensors::subfeature& subfeature) {
    auto name = QString::fromStdString(subfeature.feature().label());
    auto* name_col = new QStandardItem(name);

    Subfeature sub(subfeature);

    subfeatures_.push_back(sub);

    return {name_col, sub.value_col(), sub.min_col(), sub.max_col()};
}

void Chip::update() {
    for (auto& sub: subfeatures_) {
        sub.update();
    }
}