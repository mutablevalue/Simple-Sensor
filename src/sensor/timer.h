#ifndef TIMER_H
#define TIMER_H

#include <avr/io.h>
#include <stdint.h>

class Timer {
public:
  // Initialize Timer1
  static void init();

  // Reset Timer1 count to 0
  static void reset();

  // Get current Timer1 count
  static uint16_t get_count();

  // Check if timer exceeded a limit
  static bool exceeded(uint16_t limit);

private:
  Timer() = delete;
};

#endif
