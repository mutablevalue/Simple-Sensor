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
- **Close LED** → `led_close`
- **Mid LED** → `led_mid`
- **Far LED** → `led_far`

---

## Requirements

Install required tools:

```bash
sudo apt update
sudo apt install cmake gcc-avr g++-avr avr-libc binutils-avr avrdude
```

---

## Project Structure

```
.
├── CMakeLists.txt
├── src
│   ├── entry.cpp
│   ├── sensor
│   │   ├── sensor.cpp
│   │   └── sensor.h
│   └── timer
│       ├── timer.cpp
│       └── timer.h
└── README.md
```

---

## Build

```bash
cmake -S . -B build
cmake --build build
```

Output:
- `build/SimpleSensor.elf`
- `build/SimpleSensor.hex`

---

## Flash

```bash
cmake --build build --target flash
```

If you get permission errors:

```bash
sudo usermod -aG dialout $USER
```

Then log out and back in.

---

## Timer Details

This project uses Timer1 for precise echo measurement.

- Mode: Normal
- Prescaler: 8
- Timer frequency: 2 MHz
- Resolution: 0.5 µs per tick

Distance conversion:

```
distance_cm = ticks / 116
```

---

## Example CMakeLists.txt

```cmake
cmake_minimum_required(VERSION 3.16)

project(SimpleSensor C CXX)

set(MCU atmega328p)
set(AVRDUDE_MCU m328p)
set(F_CPU 16000000UL)

set(CMAKE_SYSTEM_NAME Generic)

set(CMAKE_C_COMPILER /usr/bin/avr-gcc)
set(CMAKE_CXX_COMPILER /usr/bin/avr-g++)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(COMMON_FLAGS
    -mmcu=${MCU}
    -DF_CPU=${F_CPU}
    -Os
    -fno-exceptions
    -fno-rtti
)

add_executable(${PROJECT_NAME}.elf
    src/entry.cpp
    src/sensor/sensor.cpp
    src/timer/timer.cpp
)

target_compile_options(${PROJECT_NAME}.elf PRIVATE ${COMMON_FLAGS})
target_link_options(${PROJECT_NAME}.elf PRIVATE -mmcu=${MCU})

target_include_directories(${PROJECT_NAME}.elf PRIVATE
    src
    src/sensor
    src/timer
)

add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD
    COMMAND avr-objcopy -O ihex -R .eeprom
            ${PROJECT_NAME}.elf
            ${CMAKE_BINARY_DIR}/${PROJECT_NAME}.hex
)

add_custom_target(flash
    COMMAND avrdude -c arduino -p ${AVRDUDE_MCU} -P /dev/ttyACM0 -b 115200
            -U flash:w:${CMAKE_BINARY_DIR}/${PROJECT_NAME}.hex:i
    DEPENDS ${PROJECT_NAME}.elf
)
```
