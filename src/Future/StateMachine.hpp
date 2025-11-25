#pragma once

#include <cstdint>

class StateMachine {
  public:
    void consume();

    void produce();

  private:
    enum _ : uint16_t {
        Init = 0,
        Producer = 1,
        Consumer = 2,
        Rendezvouz = Producer | Consumer,
    };
};
