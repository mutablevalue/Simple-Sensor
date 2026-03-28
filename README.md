# Simple-Sensor

An AVR C++ ultrasonic distance sensor project for the Arduino Uno using the HC-SR04, three LEDs for distance indication, and UART communication to send data to a PC.

---

## Overview

This project measures distance using an HC-SR04 ultrasonic sensor and:
- Uses Timer1 for precise timing
- Drives LEDs to indicate distance ranges
- Sends distance data over UART → USB → PC

---

## Hardware

### Board
- Arduino Uno (ATmega328P)
- 16 MHz clock

### Sensor
- HC-SR04 ultrasonic sensor

---

## Pin Configuration

### HC-SR04
- VCC → 5V
- GND → GND
- TRIG → PB0 (D8)
- ECHO → PB1 (D9)

### UART (Hardware Serial)
- TX → PD1 (D1)
- RX → PD0 (D0)

UART appears on PC as:
- /dev/ttyACM0

---

## Features

- Accurate distance measurement using Timer1
- LED-based distance indication
- UART serial output to PC
- CMake-based AVR build system

---

## UART Configuration

- Baud: 9600
- Format: 8N1 (8 data bits, no parity, 1 stop bit)

At 16 MHz:
UBRR = 103

---

## Example Output

Distance: 24 cm
Distance: 23 cm
Distance: 25 cm

---

## Requirements

### Debian / Ubuntu
sudo apt update
sudo apt install cmake gcc-avr g++-avr avr-libc binutils-avr avrdude

### Fedora
sudo dnf install cmake avr-gcc avr-gcc-c++ avr-libc avr-binutils avrdude

---

## Project Structure

.
├── CMakeLists.txt
├── src
│   ├── entry.cpp
│   ├── core.cpp
│   ├── communication
│   │   ├── uart.cpp
│   │   └── uart.h
│   └── sensor
│       ├── sensor.cpp
│       ├── sensor.h
│       ├── timer.cpp
│       └── timer.h

---

## Build

cd build
cmake ..
make

---

## Flash

make flash

If port is busy:
pkill screen
fuser -k /dev/ttyACM0

---

## Read UART Data

screen /dev/ttyACM0 9600

Exit:
Ctrl-A → K → y

---

## Program Flow

core.init()
core.run_service()

Loop:
- Read sensor
- Get distance
- Send over UART
- Delay
- Repeat

---

## Example UART Usage

CommunicationSystem.write_string("Distance: ");
CommunicationSystem.write_uint32(distance);
CommunicationSystem.write_line(" cm");

---

## Timer Details

Timer1:
- Prescaler: 8
- Frequency: 2 MHz
- Resolution: 0.5 µs

distance_cm = ticks / 116

---

## Notes

- UART initializes on first use
- Always send newline (\r\n)
- Only one process can use /dev/ttyACM0 at a time
