#pragma once

#include <optional>
#include <string>
namespace sensors {
class chip_name;
}

namespace PCI {
std::optional<std::string> device_name(const sensors::chip_name&);
};