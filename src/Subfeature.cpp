#include "Subfeature.hpp"

#include <sensors-c++/error.h>

#include <QStandardItem>
#include <utility>

#include "SensorsController.hpp"

Subfeature::Subfeature(sensors::subfeature subfeature) : source_(std::move(subfeature)) {
    // value_col_ = new QStandardItem();
    // min_col_ = new QStandardItem();
    // max_col_ = new QStandardItem();
    max_ = 0.0f;
    min_ = std::numeric_limits<double>::max();
}

double Subfeature::update() {
    try {
        auto value = source_.read();
        if (value < min_) {
            min_ = value;
        }
        if (value > max_) {
            max_ = value;
        }
        return value;
    } catch (sensors::io_error& ex) {
        return 0.0;
    }
}