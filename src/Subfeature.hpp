#pragma once

#include <sensors-c++/sensors.h>

#include "SensorsUtil.hpp"
#include "Updateable.hpp"

class QStandardItem;

class Subfeature final : public Updateable {
public:
    explicit Subfeature(sensors::subfeature);

    double update() override;
    double min() const override { return min_; };
    double max() const override { return max_; };
    const char* unit() const override { return SensorsUtil::unit(source_.feature().type()); }
    std::string name() const override { return source_.feature().label(); }

private:
    sensors::subfeature source_;
    double min_;
    double max_;
};