#pragma once

#include <stdexcept>

class NoSensors final : public std::runtime_error {
public:
    NoSensors() : std::runtime_error("no sensors found") {}
};