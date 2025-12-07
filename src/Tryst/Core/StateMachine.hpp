#pragma once

#include <atomic>
#include <cstdint>

namespace renn::tryst {

enum States : uint64_t {
    INIT = 0,
    CONSUMER = 1,                /* consumer comes to shared state */
    PRODUCER = 2,                /* producer comes to shared state */
    TRYST = PRODUCER | CONSUMER, /* consumer and producer met => date => callback + result */
};

/* Wait-free */
class StateMachine {
  public:
    bool consume();

    bool produce();

  private:
    std::atomic<uint64_t> state_{States::INIT};
};

/* ///////////////////////////////////////////////////////////// */

/*
 * fetch_or do atomic rmw:
 *  \ reads current value
 *  \ writes (old_value | new_value)
 *  \ returns old_value
 */

/* if old_value == States::PRODUCER => automata switches to States::TRYST
 * Otherwise, States::CONSUMER stored
 */
inline bool StateMachine::consume() {
    return state_.fetch_or(States::CONSUMER) == States::PRODUCER;
}

/* if old_value == States::CONSUMER => automata switches to States::TRYST
 * Otherwise, States::PRODUCER stored
 */
inline bool StateMachine::produce() {
    return state_.fetch_or(States::PRODUCER) == States::CONSUMER;
}

};  // namespace renn::tryst
