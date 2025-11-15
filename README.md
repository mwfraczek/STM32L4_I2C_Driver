# Overview:
This project contains embedded C firmware for the STM32 Nucleo-L476RG, interfacing with a BMP390 pressure/temperature sensor and a GT-U7 GPS module. It utilizes hardware-driven interrupts to retrieve and output data via UART. All peripherals are configured in a bare-metal environment directly from the STM32L4 Reference Manual. The goal is to build a strong foundation in embedded systems while expanding the project's functionality for a model rocket flight controller application.


## Features: 🔧
- Bare-metal STM32L4 firmware (no HAL, RTOS, CubeMX). 
- Interrupt-driven data handling for non-blocking, real-time operation. 
- I2C driver for BMP390 pressure/temperature sensor.
- UART drivers for GPS input (USART3) and serial output (USART2).
- Floating-point conversion of BMP390 raw measurement data.
- Ring-buffer GPS parser for continuous NMEA sentence extraction.
- Python logging script for UART output capture and CSV generation. 


## Demonstration: 🎥
**Hardware & Data Stream Demo:** 
- https://youtu.be/9T74qPDPzVY


## Future Work: 🚧 
- Parse NMEA sentences to extract time, longitude, latitude, and altitude.
- Integrate BNO085 IMU over SPI. 


## Hardware Requirements: 🧰
- **MCU:** Nucleo-L476RG (STM32L476RG).
- **Device:** BMP390 Breakout Board & GT-U7 GPS Module
- **Pull-ups:** 2.2kOhm on I2C SCL and SDA lines.
- **Power:** PC supplied USB-power to Nucleo board. Nucleo board supplied 3.3V VDD to devices.
- **Configuration:** SDO tied to GND (slave addr: 0x76). CSB tied to 3.3V (I2C Interface Selection).   


## Build Instructions: 🛠️
- **Install** ARM GCC toolchain: `sudo apt install gcc-arm-none-eabi`
- **Clone** repo: `git clone https://github.com/mwfraczek/FlightCore-L4.git`
- **Build**: `make` 
- **Flash**: `st-flash --reset write bin/main.bin 0x08000000` or use STM32CubeIDE


## Directory Structure: 📂
    .
    ├── bin
    ├── build
    ├── drivers
    │   ├── bmp390.c
    │   ├── gps.c
    │   ├── i2c.c
    │   ├── usart.c
    │   ├── utils.c
    │   └── peripherals.c
    ├── inc
    │   ├── cmsis/
    │   ├── bmp390.h
    │   ├── gps.h
    │   ├── i2c.h
    │   ├── peripherals.h
    │   ├── usart.h
    │   ├── utils.h
    │   └── stm32l476.h
    ├── log.py
    ├── linker.ld
    ├── Makefile
    ├── README
    └── src
        ├── main.c
        ├── startup.s
        └── system.c


## Contributions: 👤
- **Author:** Michael Fraczek
- Open to collaboration & feedback!

