#include "TimerThread.hpp"

#include "TimerHandler.hpp"
#include "TimerThread.hpp"
#include <cassert>
#include <chrono>
#include <utility>

namespace renn::timers {

TimerThread::TimerThread(renn::core::IExecutor* executor)
    : m_executor_(executor) {}

void TimerThread::set(Duration delay, timers::Handler handler) {
    auto now = Clock::now();
    /* pushing deadline related with handler to the multimap */
    auto dl = now + std::chrono::duration_cast<Clock::duration>(delay);
    timers_.push(dl, std::move(handler));
}

void TimerThread::start() {
    timer_thread_ = std::jthread([this] {
        run_loop();
    });
}

void TimerThread::stop() {
    timers_.close();
}

void TimerThread::run_loop() {
    std::vector<timers::Handler> ready;

    ready.reserve(32);

    while (true) {
        ready.clear();
        if (!timers_.pop_ready_blocking(ready)) {
            break;
        }

        for (auto& h : ready) {
            m_executor_->submit(std::move(h));
        }
    }
}

}  // namespace renn::timers
