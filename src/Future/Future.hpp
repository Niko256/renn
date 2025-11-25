#pragma once

#include "Event.hpp"
#include "SharedState.hpp"
#include <../Utils/Result.hpp>

namespace renn {

template <typename T>
class Future {

    utils::Result<T> get();

  private:
    SharedState<T>* state_;
};

};  // namespace renn
