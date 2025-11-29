#pragma once

#include "IScheduler.hpp"
#include <chrono>
#include <condition_variable>
#include <map>
#include <mutex>
#include <utility>

namespace renn::timers {

using Deadline = std::chrono::steady_clock::time_point;
using Clock = std::chrono::steady_clock;

/*
/ [TODO] : Lock-free timer queue
*/

class TimerBlockingQueue {
  public:
    void push(Deadline deadline, timers::Handler handler);

    void close();

    bool closed() const;

    bool pop_ready_blocking(std::vector<timers::Handler>& out);

  private:
    std::condition_variable cv_;
    std::mutex mutex_;
    bool closed_ = false;
    std::multimap<Deadline, timers::Handler> timer_queue_;
};

};  // namespace renn::timers

void renn::timers::TimerBlockingQueue::push(renn::timers::Deadline deadline, timers::Handler handler) {
    {
        std::unique_lock<std::mutex> lock(mutex_);
        timer_queue_.emplace(deadline, std::move(handler));
    }
    cv_.notify_one();
}

void renn::timers::TimerBlockingQueue::close() {
    {
        std::unique_lock lock(mutex_);
        closed_ = true;
    }
    cv_.notify_all();
}

bool renn::timers::TimerBlockingQueue::closed() const {
    return closed_;
}

bool renn::timers::TimerBlockingQueue::pop_ready_blocking(std::vector<timers::Handler>& out) {
    std::unique_lock lock(mutex_);

    for (;;) {
        if (closed_) {
            return false;
        }

        if (timer_queue_.empty()) {
            cv_.wait(lock, [this] {
                return closed_ || !timer_queue_.empty();
            });
            continue;
        }

        Deadline next = timer_queue_.begin()->first;
        auto now = Clock::now();

        if (now >= next) {
            while (!timer_queue_.empty() && timer_queue_.begin()->first <= now) {
                auto it = timer_queue_.begin();
                out.emplace_back(std::move(it->second));
                timer_queue_.erase(it);
            }
            return true;
        } else {
            auto status = cv_.wait_until(lock, next);
            (void)status;
        }
    }
}
