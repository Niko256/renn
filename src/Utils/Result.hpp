#pragma once

#include <exception>
#include <expected>

namespace renn::utils {

template <typename T>
using Result = std::expected<T, std::exception_ptr>;

};
