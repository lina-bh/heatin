#pragma once

#include <sensors-c++/sensors.h>
class QStandardItem;
#include "Measurement.hpp"

class Subfeature final {
public:
    explicit Subfeature(sensors::subfeature);

    void update();
    QStandardItem* value_col() const { return value_col_; }
    QStandardItem* min_col() const { return min_col_; }
    QStandardItem* max_col() const { return max_col_; }

private:
    sensors::subfeature source_;
    QStandardItem* value_col_;
    QStandardItem* min_col_;
    QStandardItem* max_col_;
    double min_;
    double max_;
};