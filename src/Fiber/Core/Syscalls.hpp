#pragma once

#include "../Utils/Duration.hpp"
#include <variant>

struct YieldTag {};

struct SleepForTag {
    renn::Duration delay_;
};

using Syscall =
    std::variant<
        YieldTag,
        SleepForTag>;
