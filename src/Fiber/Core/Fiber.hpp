#pragma once

#include "../Coroutine/Coro.hpp"
#include "../Runtime/Core/RtView.hpp"
#include "Core/Syscalls.hpp"
#include "Handle.hpp"
#include "Utils.hpp"
#include <vvv/list.hpp>

namespace renn {

/* Fiber = Stackful coroutine x Scheduler */
class Fiber : public vvv::IntrusiveListNode<Fiber> {
  public:
    explicit Fiber(renn::RtView&, renn::Renn);

    void schedule();

    void step();

    static void set_current(Fiber*);

    static Fiber* current();

    void suspend(fiber::Syscall, fiber::SuspendHandler);

    friend renn::fiber::FiberHandle;

  private:
    Coroutine& get_coro();

    [[nodiscard]] renn::RtView& current_scheduler();

  private:
    renn::Coroutine coro_;
    renn::RtView runtime_;
    renn::fiber::Syscall reason_;
    renn::fiber::SuspendHandler handler_;

    static thread_local Fiber* current_;
};

};  // namespace renn
