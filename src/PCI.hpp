#pragma once

#include <sensors-c++/sensors.h>

class PCI final {
public:
    PCI();
    ~PCI();

    std::optional<std::string> device_name(const sensors::chip_name&);

private:
    struct pci_access* pacc_;
};