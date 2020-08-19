#include "PCI.hpp"

#include <array>
#include <fstream>
extern "C" {
#include <pci/pci.h>
}

#include <string_view>

static struct pci_access* pacc = nullptr;

std::optional<std::string> PCI::device_name(const sensors::chip_name& chip) {
    if (pacc == nullptr) {
        pacc = pci_alloc();
        pci_init(pacc);
    }

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
    const auto* name = pci_lookup_name(pacc, buf.data(), buf.size(), PCI_LOOKUP_VENDOR | PCI_LOOKUP_DEVICE, ven, dev);
    return name;
}