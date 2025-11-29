#include "SleepFor.hpp"

namespace renn::fiber {

void sleep_for(timers::Duration delay) {
    Fiber::current()->suspend(SleepTag(delay), [delay](FiberHandle h) {
        auto& timer_sched = get_timers_scheduler(h.get_runtime());
        timer_sched.set(delay, [&h, delay] {
            h.schedule();
        });
    });
}

}  // namespace renn::fiber
