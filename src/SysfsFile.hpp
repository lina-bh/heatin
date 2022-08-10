#pragma once

#include <cstdint>
#include <optional>
#include <vector>

class SysfsFile final {
    SysfsFile(SysfsFile&&) = delete;
    SysfsFile& operator=(SysfsFile&&) = delete;

    ~SysfsFile();

    std::vector<std::uint8_t> read_bytes(std::size_t n);
    template <typename T>
    T read_int();

    static SysfsFile& open(const char* path);

private:
    explicit SysfsFile() = default;
    int fd_;
};