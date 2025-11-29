#include "Fiber.hpp"
#include "Core/Syscalls.hpp"
#include "Coro.hpp"
#include "Handle.hpp"
#include <cassert>

namespace renn {

thread_local Fiber* Fiber::current_ = nullptr;

Fiber::Fiber(renn::RtView& rt, renn::Renn renn)
    : coro_(std::move(renn)),
      runtime_(rt),
      reason_(fiber::YieldFiberTag{}) {}

void Fiber::schedule() {
    get_renn_scheduler(runtime_).submit([this] {
        /* scheduling new step */
        step();
    });
}

void Fiber::step() {
    auto prev_fiber = current_;
    current_ = this;

    coro_.resume();

    current_ = prev_fiber;

    if (coro_.is_done()) {
        delete this;
        return;
    }

    if (handler_) {
        auto hd = std::move(handler_);
        hd(fiber::FiberHandle(this));
    }
}

/* get current fiber */
Fiber* Fiber::current() {
    return current_;
}

void Fiber::set_current(Fiber* new_current) {
    current_ = new_current;
}

/* get internal coroutine */
Coroutine& Fiber::get_coro() {
    return coro_;
}

/* get internal scheduler */
renn::RtView& Fiber::current_scheduler() {
    return runtime_;
}


};  // namespace renn
