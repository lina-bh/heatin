#pragma once

#include <sensors-c++/sensors.h>

#include "SensorsUtil.hpp"
#include "Updateable.hpp"

class Subfeature final : public Updateable {
public:
    explicit Subfeature(sensors::subfeature);

    double update() override;
    const char* unit() const override { return SensorsUtil::unit(source_.feature().type()); }
    std::string name() const override { return source_.feature().label(); }

private:
    sensors::subfeature source_;
};