#include "Runtime.hpp"

namespace renn {


Runtime::Runtime(size_t workers)
    : executor_(workers) {
}

Runtime& Runtime::enable_timers() {
    if (!timer_thread_.has_value()) {
        timer_thread_.emplace(&executor_);  //!!!
    }
    return *this;
}

void Runtime::start() {
    executor_.start();
    if (timer_thread_.has_value()) {
        timer_thread_->start();
    }
}

void Runtime::stop() {
    if (timer_thread_.has_value()) {
        timer_thread_->stop();
    }
    executor_.stop();
}

Runtime::operator RtView() {
    timers::IScheduler* timer_scheduler = nullptr;
    if (timer_thread_.has_value()) {
        timer_scheduler = &(*timer_thread_);
    }

    return {&executor_, timer_scheduler};
}

bool Runtime::here() const {
    return ThreadPool::current() == &executor_;
}

};  // namespace renn
