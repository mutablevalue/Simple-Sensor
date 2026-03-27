#include "sensor.h"
#include "timer.h"

void Sensor::init() {
  // Set trig as output
  DDRB |= (1 << trig);

  // Set echo as input
  DDRB &= ~(1 << echo);
  Timer::init();
  // Make sure trig starts low
  PORTB &= ~(1 << trig);

  // Set each LED pin as an output
  DDRD |= (1 << led_close) | (1 << led_mid) | (1 << led_far);

  // Make sure all LEDs start off
  clear_leds();

  // Start with no valid distance
  current_distance = 0;
}

void Sensor::trigger() {
  // Ensure trig is low before the pulse
  PORTB &= ~(1 << trig);
  _delay_us(2);

  // Send a 10 microsecond pulse
  PORTB |= (1 << trig);
  _delay_us(10);
  PORTB &= ~(1 << trig);
}

uint32_t Sensor::measure_echo() {
  // Wait for echo to go HIGH
  Timer::reset();
  while (!(PINB & (1 << echo))) {
    if (Timer::exceeded(timeout)) {
      return 0;
    }
  }

  // Start measuring HIGH pulse width
  Timer::reset();
  while (PINB & (1 << echo)) {
    if (Timer::exceeded(timeout)) {
      return 0;
    }
  }

  uint16_t pulse_ticks = Timer::get_count();
  return pulse_ticks;
}

void Sensor::clear_leds() {
  PORTD &= ~((1 << led_close) | (1 << led_mid) | (1 << led_far));
}

void Sensor::update_leds() {
  clear_leds();

  // No valid reading
  if (current_distance == 0) {
    return;
  }

  if (current_distance < distance_close) {
    PORTD |= (1 << led_close);
  } else if (current_distance < distance_mid) {
    PORTD |= (1 << led_mid);
  } else {
    PORTD |= (1 << led_far);
  }
}

uint32_t Sensor::read_distance() {
  trigger();

  uint32_t echo_time = measure_echo();

  if (echo_time == 0) {
    current_distance = 0;
    update_leds();
    _delay_ms(100);
    return current_distance;
  }

  // Timer tick = 0.5 us, so divide by 116 for cm
  current_distance = echo_time / 116;

  update_leds();
  _delay_ms(100);

  return current_distance;
}

uint32_t Sensor::get_distance() const { return current_distance; }
