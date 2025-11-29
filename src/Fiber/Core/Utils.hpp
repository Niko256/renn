#pragma once

#include "../Fiber/Core/Handle.hpp"
#include "sure/context.hpp"
#include <function2/function2.hpp>
#include <sure/stack/mmap.hpp>

namespace renn::fiber {

using Stack = sure::stack::GuardedMmapExecutionStack;

using SuspendHandler = fu2::unique_function<void(FiberHandle)>;

using ExecutionContext = sure::ExecutionContext;

};  // namespace renn::fiber
