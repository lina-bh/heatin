#include "Subfeature.hpp"

#include <sensors-c++/error.h>

#include <QStandardItem>
#include <utility>

#include "SensorsController.hpp"

Subfeature::Subfeature(sensors::subfeature subfeature) : source_(std::move(subfeature)) {}

double Subfeature::update() {
    try {
        return source_.read();
    } catch (sensors::io_error& ex) {
        return 0.0;
    }
}