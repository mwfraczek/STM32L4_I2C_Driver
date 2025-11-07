# Overview:
This project contains embedded C firmware for the STM32L476 (Nucleo-L476RG), interfacing with a BMP390 pressure/temperature sensor and a GT-U7 GPS module. All peripherals are configured directly from the STM32L4 Reference Manual (RM0351), with no reliance on vendor HAL. The goal is to continuously expand functionality through hardware-level control, and to build a strong foundation in embedded systems and firmware development.


## Features: 🔧
- Register-level control of GPIO, I2C, UART, TIM, RCC peripherals. 
- I2C driver for BMP390 pressure/temperature sensor.
- UART drivers for GPS input (USART3) and serial output (USART2).
- Floating-point conversion of BMP390 raw sensor data. 
- NMEA sentence filtering (GPRMC) from GPS module. 
- LED indicator for system status and timing reference. 


## Demonstration: 🎥
**BMP390 sensor data output:** 
- https://youtu.be/KMbyM4Ony0o?si=7weaQ0JydmJHaIW2
**GPS module addition and data stream:** 
- https://youtu.be/wnoSNGjvu-4?si=5N056fnCtZTQxa17


## Future Work: 
**Short Term:** 
- Parse NMEA sentences to pull time, longitude, latitude, and altitude.
- Develop Python script for serial data logging. 
- Implement hardware interrupt handling.
**Long Term:** 
- Integrate BMI088 IMU via SPI.
- Expand logging format for SD card storage. 


## Hardware Requirements: 🧰
- **MCU:** Nucleo-L476RG (STM32L476RG).
- **Device:** BMP390 Breakout Board & GT-U7 GPS Module
- **Pull-ups:** 2.2kOhm on I2C SCL and SDA lines.
- **Power:** PC supplied USB-power to Nucleo board. Nucleo board supplied 3.3V VDD to devices.
- **Configuration:** SDO tied to GND (slave addr: 0x76). CSB tied to 3.3V (I2C Interface Selection).   


## Build Instructions: 🛠️
- **Install** ARM GCC toolchain: `sudo apt install gcc-arm-none-eabi`
- **Clone** repo: `git clone https://github.com/mwfraczek/STM32L4_I2C_Driver.git`
- **Build**: `make`
- **Flash**: `st-flash --reset write bin/main.bin 0x08000000` or use STM32CubeIDE


## Directory Structure: 📂
    .
    ├── bin
    ├── build
    ├── drivers
    │   ├── bmp390.c
    │   ├── i2c.c
    │   ├── usart.c
    │   ├── utils.c
    │   └── peripherals.c
    ├── inc
    │   ├── bmp390.h
    │   ├── i2c.h
    │   ├── peripherals.h
    │   ├── usart.h
    │   ├── utils.h
    │   └── stm32l476.h
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

