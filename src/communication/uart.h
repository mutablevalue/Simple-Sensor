#pragma once

#include <avr/io.h>
#include <stdint.h>
#include <util/delay.h>

class Communication {
private:
  static constexpr uint8_t Transmit = PD1;
  static constexpr uint8_t Receive = PD0;
  static constexpr uint16_t ubrr = 103;
  bool initialized = false;
  inline void init();

public:
  void write_char(const char character_to_write);
  void write_string(const char *string_to_write);
  void write_uint32(uint32_t value_to_write);
  void write_line(const char *string_to_write);
};
