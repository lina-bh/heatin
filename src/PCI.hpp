#pragma once

#include <sensors-c++/sensors.h>

#include <optional>
#include <string>

class PCI final {
public:
    PCI();
    ~PCI();

    std::optional<std::string> device_name(const sensors::chip_name&);

private:
    struct pci_access* pacc_;
};