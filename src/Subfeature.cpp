#include "Subfeature.hpp"

#include <sensors-c++/error.h>

#include <QStandardItem>
#include <iostream>
#include <utility>

#include "SensorsController.hpp"
#include "SensorsUtil.hpp"

Subfeature::Subfeature(sensors::subfeature subfeature) : source_(std::move(subfeature)) {}

double Subfeature::update() {
    try {
        return source_.read();
    } catch (sensors::io_error& ex) {
        std::cerr << "couldn't read sensor " << name() << ": " << ex.what() << "\n";
        return 0.0;
    }
}

const char* Subfeature::unit() const {
    return SensorsUtil::unit(source_.feature().type());
}

std::string Subfeature::name() const {
    return source_.feature().label();
}