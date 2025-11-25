#pragma once

#include "../Utils/Futex.hpp"
#include <atomic>
#include <cstdint>

namespace renn {

class Event {
  public:
    void wait() {
    }

    void fire();

  private:
    std::atomic<uint32_t> ready_{0};
};

};  // namespace renn
