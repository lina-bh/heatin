#include "Measurement.hpp"

#include <QStandardItem>

Measurement::Measurement(sensors::subfeature subfeature) : feature(std::move(subfeature)) {
    value_col = new QStandardItem();
    min_col = new QStandardItem();
    max_col = new QStandardItem();
    min = max = 0.0f;
}