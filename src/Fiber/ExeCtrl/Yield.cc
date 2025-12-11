#include "Yield.hpp"
#include "Handle.hpp"
#include "Syscalls.hpp"

namespace renn::fiber {

void yield() {
    renn::Fiber::current()->suspend(YieldTag{}, [](FiberHandle h) {
        h.schedule();
    });
}

};  // namespace renn::fiber
