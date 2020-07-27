#include "PCI.hpp"

#include <fstream>
extern "C" {
#include <pci/pci.h>
}

PCI::PCI() {
    pacc_ = pci_alloc();
    pci_init(pacc_);
}

PCI::~PCI() { pci_cleanup(pacc_); }

std::optional<std::string> PCI::device_name(const sensors::chip_name& chip) {
    std::string hwmon_path(chip.path().data());

    std::ifstream fdev((hwmon_path + "/device/device").c_str());
    int dev = 0;
    fdev >> std::hex >> dev;

    std::ifstream fven((hwmon_path + "/device/vendor").c_str());
    int ven = 0;
    fven >> std::hex >> ven;

    if (dev == 0 || ven == 0) {
        return {};
    }

    constexpr int bufsiz = 1024;
    std::array<char, bufsiz> buf{};
    // NOLINTNEXTLINE(cppcoreguidelines-pro-type-vararg, hicpp-vararg)
    const auto* name = pci_lookup_name(pacc_, buf.data(), buf.size(), PCI_LOOKUP_VENDOR | PCI_LOOKUP_DEVICE, ven, dev);
    return name;
}