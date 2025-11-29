#pragma once

#include "../Utils/Renn.hpp"

namespace renn::core {

class IExecutor {
  public:
    virtual void submit(renn::Renn&& renn) = 0;

    virtual ~IExecutor() = default;
};

};  // namespace renn::core
