# Simple-Sensor

A simple AVR C++ ultrasonic distance sensor project for the Arduino Uno using the HC-SR04 and three LEDs to indicate distance ranges.

---

## Hardware

### Board
- Arduino Uno
- MCU: ATmega328P
- Clock: 16 MHz

### Sensor
- HC-SR04 ultrasonic sensor

---

## Pin Configuration

### HC-SR04
- **VCC** → 5V  
- **GND** → GND  
- **TRIG** → PB0 (Arduino D8)  
- **ECHO** → PB1 (Arduino D9)  

### LEDs
Configured in `sensor.h`:

- **Close LED** → PD5 (Arduino D5)
- **Mid LED** → PD6 (Arduino D6)
- **Far LED** → PD7 (Arduino D7)

---

## UART Communication (ADDED)

This project now includes UART communication to send distance data to a PC.

### UART Pins (ATmega328P)
- **TX** → PD1 (Arduino D1)
- **RX** → PD0 (Arduino D0)

UART is routed through the Arduino Uno USB interface and appears on the PC as:

/dev/ttyACM0

### UART Configuration
- Baud: 9600
- Format: 8N1 (8 data bits, no parity, 1 stop bit)

At 16 MHz:
UBRR = 103

### Example Output
Distance: 24 cm
Distance: 23 cm
Distance: 25 cm

---

## Requirements

Install required tools:

sudo apt update
sudo apt install cmake gcc-avr g++-avr avr-libc binutils-avr avrdude

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
│   ├── sensor
│   │   ├── sensor.cpp
│   │   ├── sensor.h
│   │   ├── timer.cpp
│   │   └── timer.h
└── README.md

---

## Build

cmake -S . -B build
cmake --build build

Output:
- build/SimpleSensor.elf
- build/SimpleSensor.hex

---

## Flash

cmake --build build --target flash

If you get permission errors:

sudo usermod -aG dialout $USER

Then log out and back in.

---

## Timer Details

This project uses Timer1 for precise echo measurement.

- Mode: Normal
- Prescaler: 8
- Timer frequency: 2 MHz
- Resolution: 0.5 µs per tick

Distance conversion:

distance_cm = ticks / 116
