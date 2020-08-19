#pragma once

#include <sensors-c++/sensors.h>

#include <optional>
#include <string>

namespace PCI {
std::optional<std::string> device_name(const sensors::chip_name&);
};