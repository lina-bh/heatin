#pragma once

#include <sensors-c++/sensors.h>

#include "SensorsUtil.hpp"
#include "Updateable.hpp"

class Subfeature final : public Updateable {
public:
    Subfeature(Subfeature&&) = delete;
    Subfeature& operator=(Subfeature&&) = delete;

    explicit Subfeature(sensors::subfeature);

    double update() override;
    const char* unit() const override;
    std::string name() const override;

private:
    sensors::subfeature source_;
};