#include "uart.h"

void Communication::init() {
  // UBRR0 is split into a high byte and low byte.
  UBRR0H = static_cast<uint8_t>(ubrr >> 8);
  UBRR0L = static_cast<uint8_t>(ubrr);

  // Enable transmitter
  UCSR0B = (1 << TXEN0);
  // UCSZ01 set character size to 8 bits.
  // UCSZ00 sets receiver to enabled
  // No parity bit is enabled.
  // One stop bit is used by default.
  UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
  initialized = true; // we set initialized to true
};

void Communication::write_char(char character_to_write) {
  if (!initialized)
    init();
  // Wait until the transmit data register is empty.
  // UDRE0 becomes 1 when UART is ready to accept the next byte.
  while (!(UCSR0A & (1 << UDRE0))) {
  };

  // puts the character into the UART data registry
  UDR0 = character_to_write;
};

void Communication::write_string(const char *string_to_write) {
  if (!initialized)
    init();
  // walk through the string, dereferencing each position of the array then
  // advancing the array
  while (*string_to_write != '\0') {
    write_char(*string_to_write++);
  }
};

void Communication::write_uint32(uint32_t value_to_write) {
  if (!initialized)
    init();
  // if the value is 0  print '0'.
  if (value_to_write == 0) {
    write_char('0');
    return;
  }

  // Max uint32_t is 4294967295 which is 10 digits.
  char buffer[10];
  uint8_t index = 0;

  // Repeatedly take the last decimal digit and store it.
  // Example: 123 -> store '3', then '2', then '1'
  while (value_to_write > 0) {
    buffer[index] = static_cast<char>('0' + (value_to_write % 10));
    value_to_write /= 10;
    ++index;
  }

  // Digits were stored in reverse order, so send them backwards.
  while (index > 0) {
    --index;
    write_char(buffer[index]);
  }
};

void Communication::write_line(const char *string_to_write) {
  if (!initialized)
    init();
  // Send the string itself.
  write_string(string_to_write);

  // Send carriage return + newline.
  // Many serial terminals expect "\r\n" for a clean new line.
  write_char('\r');
  write_char('\n');
};
