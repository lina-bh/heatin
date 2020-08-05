#pragma once

#include <QString>
#include <string_view>

namespace StringUtil {

inline QString QString_from_string_view(const std::string_view& sv) {
    return QString::fromUtf8(sv.data());
}

}