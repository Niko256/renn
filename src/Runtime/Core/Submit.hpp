#pragma once

#include "RtView.hpp"
#include <utility>

namespace renn {

inline void submit(renn::RtView rt, renn::Renn renn) {
    get_renn_scheduler(rt).submit(std::move(renn));
}

};  // namespace renn
