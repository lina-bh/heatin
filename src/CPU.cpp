#include "CPU.hpp"

extern "C" {
#include <cpufreq.h>
}
#include <cpuid.h>

#include <array>
#include <sstream>

static const unsigned int CPUID_BRAND_STRING = 0x80000002;

static char cpu_name[49] = {0};

CPU::CPU(int idx) : idx_(idx) {}

double CPU::update() {
    return cpufreq_get_freq_kernel(idx_) / 1000;
}

std::string CPU::name() const {
    std::ostringstream fmt;
    fmt << "CPU " << idx_;
    return fmt.str();
}

const char* CPU::get_name() {
    if (cpu_name[0] == '\0') {
        for (int i = 0; i <= 2; i++) {
            int offset = 16 * i;
            auto* const base = reinterpret_cast<unsigned int*>(cpu_name + offset);
            __get_cpuid(CPUID_BRAND_STRING + i, base, base + 1, base + 2, base + 3);
        }
    }
    return cpu_name;
}