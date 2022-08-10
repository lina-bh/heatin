#include "CPU.hpp"

#include <cpuid.h>
#include <fcntl.h>
#include <fmt/core.h>
#include <unistd.h>

#include <cerrno>
#include <cstdio>
#include <cstring>
#include <fstream>
#include <iostream>
#include <sstream>

static const unsigned int CPUID_BRAND_STRING = 0x80000002;

static std::string core_name(const int idx) {
    char buf[8] = {0};
    std::snprintf(buf, sizeof(buf), "CPU %d", idx);
    return {buf};
}

CPU::CPU(const int idx) : idx_(idx),
                          name_(core_name(idx)),
                          fd_(-1) {
    char buf[128] = {0};
    auto n = std::snprintf(buf, sizeof(buf), "/sys/devices/system/cpu/cpufreq/policy%d/scaling_cur_freq", idx);
    if (!n) {
        std::cerr << "couldn't format scaling_cur_freq path\n";
        return;
    }
    auto fd = open(buf, O_RDONLY);
    if (!fd_) {
        std::cerr << "couldn't open scaling_cur_freq path for core " << idx << ": " << std::strerror(errno) << "\n";
        return;
    }
    fd_ = fd;
}

CPU::~CPU() {
    if (fd_) {
        close(fd_);
    }
}

double CPU::update() {
    if (!fd_) {
        return 0.0;
    }
    char buf[16] = {0};
    if (pread(fd_, buf, sizeof(buf), 0) == -1) {
        std::cerr << "couldn't read current frequency for core " << idx_ << ": " << std::strerror(errno) << "\n";
        close(fd_);
        fd_ = -1;
        return 0.0;
    }
    auto hz = std::strtol(buf, nullptr, 10);
    return hz / 1000;
}

std::string CPU::name() const {
    return name_;
}

const char* cpu_brand_string() {
    static char cpu_name[49] = {0};
    if (cpu_name[0] != '\0') {
        return cpu_name;
    }
    for (int i = 0; i <= 2; i++) {
        const int offset = 16 * i;
        auto* const base = reinterpret_cast<unsigned int*>(cpu_name + offset);
        __get_cpuid(CPUID_BRAND_STRING + i, base, base + 1, base + 2, base + 3);
    }
    cpu_name[48] = 0;
    return cpu_name;
}
