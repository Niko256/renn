#pragma once
#include "../Runtime/Core/RtView.hpp"

namespace renn {
/* forward declaration */
class Fiber;
};  // namespace renn

namespace renn::fiber {

class FiberHandle {
  public:
    FiberHandle() = default;

    FiberHandle(renn::Fiber* fiber) : fiber_(fiber) {}

    ~FiberHandle() = default;

    FiberHandle(const FiberHandle&) = delete;

    FiberHandle& operator=(const FiberHandle&) = delete;

    FiberHandle(FiberHandle&& other) noexcept;

    FiberHandle& operator=(FiberHandle&& other) noexcept;

    bool is_valid() const;

    renn::Fiber* release();

    void schedule();

    RtView get_runtime();

  private:
    renn::Fiber* fiber_ = nullptr;
};

};  // namespace renn::fiber
