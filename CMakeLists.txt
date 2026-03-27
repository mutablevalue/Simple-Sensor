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
    src/sensor/timer.cpp
)

target_compile_options(${PROJECT_NAME}.elf PRIVATE ${COMMON_FLAGS})
target_link_options(${PROJECT_NAME}.elf PRIVATE -mmcu=${MCU})

target_include_directories(${PROJECT_NAME}.elf PRIVATE
    src
    src/communication
    src/data
    src/sensor
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
