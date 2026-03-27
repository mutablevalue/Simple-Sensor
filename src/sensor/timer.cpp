#include "timer.h"

void Timer::init() {
  // Normal mode
  TCCR1A = 0;
  TCCR1B = 0;

  // Prescaler = 8
  // 16 MHz / 8 = 2 MHz
  // 1 tick = 0.5 us
  TCCR1B |= (1 << CS11);

  // Clear counter
  TCNT1 = 0;
}

void Timer::reset() { TCNT1 = 0; }

uint16_t Timer::get_count() { return TCNT1; }

bool Timer::exceeded(uint16_t limit) { return TCNT1 >= limit; }
