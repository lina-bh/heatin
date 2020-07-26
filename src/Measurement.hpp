#pragma once

#include <sensors-c++/sensors.h>
#include <qstandarditemmodel.h>

class Measurement final {
    friend class SensorsController;
    explicit Measurement(sensors::subfeature);
    sensors::subfeature feature;
    QStandardItem* value_col;
    QStandardItem* min_col;
    QStandardItem* max_col;
    double min;
    double max;
};