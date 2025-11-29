#pragma once

#include "../Runtime/RtView.hpp"
#include "Duration.hpp"

namespace renn::timers {

inline void set_timer(renn::RtView rt, Duration delay, renn::Renn handler) {
    get_timers_scheduler(rt).Set(delay, std::move(handler));
}


};  // namespace renn::timers
