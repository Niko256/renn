#pragma once

#include "../Utils/Renn.hpp"

namespace renn::sched {

class IScheduler {
  public:
    virtual void submit(renn::Renn&& procedure) = 0;

    virtual ~IScheduler() = default;
};

};  // namespace renn::sched
