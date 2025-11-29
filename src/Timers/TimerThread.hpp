#pragma once

#include "../Runtime/Core/IExecutor.hpp"
#include "Duration.hpp"
#include "IScheduler.hpp"
#include "TimerQueue.hpp"
#include <chrono>
#include <thread>

namespace renn::timers {

class TimerThread final : public timers::IScheduler {
  public:
    using Clock = std::chrono::steady_clock;

    explicit TimerThread(core::IExecutor*);

    void set(timers::Duration, timers::Handler) override;

    void start();

    void stop();

  private:
    void run_loop();

  private:
    std::jthread timer_thread_;
    TimerBlockingQueue timers_;
    renn::core::IExecutor* m_executor_;
};

};  // namespace renn::timers
