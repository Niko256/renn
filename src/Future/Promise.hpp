#pragma once

#include "../Utils/Result.hpp"
#include "SharedState.hpp"

namespace renn {

template <typename T>
class Promise {

  private:
    SharedState<T>* state_;
};

};  // namespace renn
