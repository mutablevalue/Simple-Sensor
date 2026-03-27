#pragma once

#define F_CPU 16000000UL

#include <avr/io.h>
#include <stdint.h>
#include <util/delay.h>

class Sensor {
public:
  void init();
  uint32_t read_distance();
  uint32_t get_distance() const;

private:
  // Sensor pins
  static constexpr uint8_t trig = PB1;
  static constexpr uint8_t echo = PB0;

  // LED pins
  static constexpr uint8_t led_close = PD5;
  static constexpr uint8_t led_mid = PD6;
  static constexpr uint8_t led_far = PD7;

  // Distance thresholds in cm
  static constexpr uint32_t distance_close = 10;
  static constexpr uint32_t distance_mid = 30;

  // Max time to wait for echo in microseconds
  static constexpr uint32_t timeout = 60000;

  // Starts at 0, and returns to 0 on failed read
  uint32_t current_distance = 0;

  void trigger();
  uint32_t measure_echo();
  void clear_leds();
  void update_leds();
};
