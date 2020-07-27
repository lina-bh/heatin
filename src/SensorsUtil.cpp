#include "SensorsUtil.hpp"

#include <sensors-c++/error.h>

namespace SensorsUtil {

bool can_read(const sensors::subfeature& subfeature) {
    if (subfeature.readable()) {
        try {
            subfeature.read();
        } catch (const sensors::io_error& ex) {
            return false;
        }
        return true;
    }
    return false;
}

}