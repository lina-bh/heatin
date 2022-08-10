#include "SysfsFile.hpp"

#include <fcntl.h>
#include <unistd.h>

#include <cerrno>
#include <cstring>
#include <sstream>
#include <stdexcept>

SysfsFile& SysfsFile::open(const char* path) {
    SysfsFile file;
    int fd = ::open(path, O_RDONLY);
    if (fd == -1) {
        std::ostringstream fmt;
        fmt << "couldn't open " << path << ": " << std::strerror(errno);
        throw std::runtime_error(fmt.str());
    }
    file.fd_ = fd;
    return file;
}

SysfsFile::~SysfsFile() {
    close(fd_);
}

std::vector<std::uint8_t> SysfsFile::read_bytes(const std::size_t n) {}