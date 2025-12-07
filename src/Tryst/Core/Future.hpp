#pragma once

#include "Callback.hpp"
#include "SharedState.hpp"
#include <../../Utils/Result.hpp>
#include <utility>

namespace renn::tryst {

template <typename T>
class Future {
  public:
    explicit Future(SharedState<T>*);

    // Move-constructible
    Future(Future&&) noexcept;

    // Non-copyable
    Future(const Future&) = delete;
    Future& operator=(const Future&) = delete;

    // Non-move-assignable
    Future& operator=(Future&&) = delete;

    ~Future();

    void consume(Callback<T>) &&;

    bool valid() const;

    void reset();

    SharedState<T>* release_state();

  private:
    SharedState<T>* state_;
};

/* ///////////////////////////////////////////////////////////// */


template <typename T>
Future<T>::Future(SharedState<T>* state)
    : state_(state) {}

template <typename T>
void Future<T>::consume(Callback<T> cb) && {
    RENN_ASSERT(valid());

    auto adapter = [cb = std::move(cb)](utils::Result<T> res) mutable {
        if (res.has_value()) {
            cb(std::move(*res));
        }
    };

    auto utilize = release_state();

    utilize->consume(std::move(adapter));
}

template <typename T>
Future<T>::Future(Future&& other) noexcept
    : state_(std::exchange(other.state_, nullptr)) {}

template <typename T>
Future<T>::~Future<T>() {
    if (valid()) {
        reset();
    }
}

template <typename T>
bool Future<T>::valid() const {
    return state_ != nullptr;
}

template <typename T>
SharedState<T>* Future<T>::release_state() {
    return std::exchange(state_, nullptr);
}

template <typename T>
void Future<T>::reset() {
    release_state()->consume([](utils::Result<T>) {});
}

};  // namespace renn::tryst
