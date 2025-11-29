#include "Handle.hpp"
#include "Fiber.hpp"
#include <algorithm>
#include <cassert>
#include <utility>

namespace renn::fiber {

bool FiberHandle::is_valid() const {
    return fiber_ != nullptr;
}

renn::Fiber* FiberHandle::release() {
    assert(is_valid());
    return std::exchange(fiber_, nullptr);
}

void FiberHandle::schedule() {
    this->release()->schedule();
}

FiberHandle::FiberHandle(FiberHandle&& other) noexcept : fiber_(std::move(other.fiber_)) {
    other.fiber_ = nullptr;
}

FiberHandle& FiberHandle::operator=(FiberHandle&& other) noexcept {
    if (this == &other) {
        return *this;
    }
    fiber_ = other.fiber_;
    other.fiber_ = nullptr;
    return *this;
}

RtView FiberHandle::get_runtime() {
    assert(fiber_);
    return this->fiber_->current_scheduler();
}

};  // namespace renn::fiber
