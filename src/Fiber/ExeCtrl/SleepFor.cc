#include "SleepFor.hpp"
#include "Fiber.hpp"
#include "Handle.hpp"
#include "Syscalls.hpp"

namespace renn::fiber {

// void sleep_for(Duration delay) {
//     Fiber::current()->suspend(SleepForTag{delay}, [delay](FiberHandle h) {
//         auto& timer_sched = renn::timers(h.get_view());
//         timer_sched.set(delay, [h] mutable {
//             h.schedule();
//         });
//     });
// }


};  // namespace renn::fiber
