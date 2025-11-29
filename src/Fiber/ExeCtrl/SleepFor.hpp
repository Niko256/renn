#pragma once

#include "../Core/Fiber.hpp"
#include "../Timers/Duration.hpp"
#include "Core/Handle.hpp"

namespace renn::fiber {

void sleep_for(renn::timers::Duration delay);

};
