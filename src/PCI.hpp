#pragma once

#include <optional>
#include <string>
namespace sensors {
class chip_name;
}

class PCI final {
public:
    PCI();
    ~PCI();

    std::optional<std::string> device_name(const sensors::chip_name&);

private:
    struct pci_access* pacc_;
};