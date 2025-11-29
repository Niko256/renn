#include "Go.hpp"
#include "../Core/Fiber.hpp"
#include "../Core/Handle.hpp"

namespace renn {

void go(renn::RtView rt, renn::Renn&& proc) {
    auto newbie = new renn::Fiber(rt, std::move(proc));
    newbie->schedule();
}

void go(renn::Renn&& proc) {
    auto h = fiber::FiberHandle(Fiber::current());
    go(h.get_runtime(), std::move(proc));
}

};  // namespace renn
