#pragma once

#include "../ThreadPool/ThreadPool.hpp"
#include "../Timers/TimerThread.hpp"
#include "IExecutor.hpp"
#include "RtView.hpp"
#include <cstddef>
#include <memory>
#include <optional>

namespace renn {

class Runtime {
  public:
    explicit Runtime(size_t workers);

    explicit Runtime(std::unique_ptr<core::IExecutor>);

    Runtime& enable_timers();

    operator RtView();

    void start();

    void stop();

    bool here() const;

  private:
    ThreadPool executor_;
    std::optional<timers::TimerThread> timer_thread_;
};

};  // namespace renn
