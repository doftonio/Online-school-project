#pragma once
#include <string_view>

namespace Color {
    inline constexpr std::string_view reset = "\x1B" "[0m";
    inline constexpr std::string_view red = "\x1B" "[31m";
    inline constexpr std::string_view green = "\x1B" "[32m";
    inline constexpr std::string_view yellow = "\x1B" "[33m";
    inline constexpr std::string_view blue = "\x1B" "[34m";
    inline constexpr std::string_view cyan = "\x1B" "[36m";
}