#pragma once

#include "../../Runtime/Core/RtView.hpp"
#include "../../Utils/Renn.hpp"
#include "../Core/Fiber.hpp"

namespace renn {

void go(renn::RtView, renn::Renn&&);

void go(renn::Renn&&);

};  // namespace renn
