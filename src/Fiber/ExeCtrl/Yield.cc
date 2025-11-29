#include "Yield.hpp"
#include "Core/Handle.hpp"
#include "Core/Syscalls.hpp"

namespace renn::fiber {

void yield() {
    renn::Fiber::current()->suspend(YieldFiberTag{}, [](FiberHandle h) {
        h.schedule();
    });
}

};  // namespace renn::fiber
