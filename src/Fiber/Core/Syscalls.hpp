#pragma once

#include "../Timers/Duration.hpp"
#include <variant>

namespace renn::fiber {
struct YieldFiberTag {};

struct SleepTag {
    renn::timers::Duration delay_;
};

using Syscall = std::variant<YieldFiberTag, SleepTag /* ... */>;

};  // namespace renn::fiber
