#include "SensorsUtil.hpp"

#include <sensors-c++/error.h>

#include "PCI.hpp"

namespace SensorsUtil {

bool can_read(const sensors::subfeature& subfeature) {
    if (subfeature.readable()) {
        try {
            subfeature.read();
        } catch (const sensors::io_error& ex) {
            return false;
        }
        return true;
    }
    return false;
}

QStandardItem* new_chip_row(const sensors::chip_name& chip) {
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
    return new QStandardItem(name);
}

}