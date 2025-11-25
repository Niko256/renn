#pragma once

#include "SharedState.hpp"
#include <../Utils/Result.hpp>

namespace renn {

template <typename T>
class Future {

  private:
    SharedState<T>* state_;
};

};  // namespace renn
