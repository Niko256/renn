#pragma once

#include "Duration.hpp"
#include "TimerHandler.hpp"
#include <function2/function2.hpp>

namespace renn::timers {

struct IScheduler {
  public:
    virtual void set(Duration delay, Handler handler) = 0;

    virtual ~IScheduler() = default;
};

};  // namespace renn::timers
