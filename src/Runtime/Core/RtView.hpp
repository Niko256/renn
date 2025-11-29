#pragma once

#include "../Timers/IScheduler.hpp"
#include "IExecutor.hpp"
#include <tuple>

namespace renn {

using RtView = std::tuple<
    core::IExecutor*,
    timers::IScheduler*
    /* ... services in our runtime ... */
    >;

template <typename Service>
Service& get(RtView rt) {
    auto* s = std::get<Service*>(rt);
    assert(s);
    return *s;
}

inline auto get_renn_scheduler(RtView rt) -> renn::core::IExecutor& {
    return get<renn::core::IExecutor>(rt);
}

inline auto get_timers_scheduler(RtView rt) -> renn::timers::IScheduler& {
    return get<renn::timers::IScheduler>(rt);
}

};  // namespace renn
