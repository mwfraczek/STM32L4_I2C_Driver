# Overview:
This repository features a bare-metal I2C driver and application code written in C for the STM32L476 (Nucleo-L476RG). It communicates with a BMP390 pressure/temperature sensor without reliance of HAL or vendor abstraction layers. All peripherals are configured directly from the STM32L4xx Reference Manual (RM0351). The goal is to demonstrate proficiency in low-level embedded C programming fundamentals, hardware interfacing, and reliable driver design. This project is under active development, with additional sensor features and data processing planned.

## Hardware Requirements: 🧰
- **MCU:** Nucleo-L476RG (STM32L476RG).
- **Sensor:** BMP390 Breakout Board - Adafruit or Amazon variants have both been tested and verified to work.
- **Pull-ups:** 2.2kOhm on SCL and SDA. Ideal communication and waveform results may vary dependent on your hardware setup and capacitance characteristics.
- **Power:** PC supplied USB-power to Nucleo board. Nucleo board supplied 3.3V VDD to sensor.
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
    │   ├── utils.c
    │   └── peripherals.c
    ├── inc
    │   ├── bmp390.h
    │   ├── i2c.h
    │   ├── peripherals.h
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
- Open to collaboration feedback!

