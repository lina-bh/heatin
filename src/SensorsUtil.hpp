#pragma once

#include <sensors-c++/sensors.h>

namespace SensorsUtil {

bool can_read(const sensors::subfeature& subfeature);

constexpr const char* unit(const sensors::feature_type& type) {
    using sensors::feature_type;

    switch (type) {
        case feature_type::current:
            return "A";
        case feature_type::fan:
            return " RPM";
        case feature_type::temp:
            return "°C";
        case feature_type::in:
            return "v";
        case feature_type::beep:
            return " beep";
        case feature_type::energy:
            return " \"energy\"";
        case feature_type::humidity:
            return " humidity";
        case feature_type::intrusion:
            return " intruded";
        case feature_type::power:
            return " power?";
        case feature_type::vid:
            return " vid";
        default:
            return "";
    }
}

}