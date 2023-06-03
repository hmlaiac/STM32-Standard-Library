# Introduction

The goal of this project is to convert my previous codes and notes into gitbook format. I will try to add more details
and explainations to development of STM32 MCU.

# Prerequisites

1. [Keil MDK-ARM V5.0 Enterprise](https://www.keil.com/download/product/)
   Please use enterprise / unlock version, otherwise you are only able to compile 32KB of code.
2. [STM32CubeMX](https://www.st.com/en/development-tools/stm32cubemx.html)
   We only Use STM32CubeMX for generating startup files and peripheral drivers. If you are using STM32F10x series, you
   can copy the example code and build the project in Keil directly.

# Standard Peripheral Library vs HAL

Standard Peripheral Library is the old version of STM32 peripheral drivers, but you can learn more about the
architecture of STM32 MCU. HAL is the new version of STM32 peripheral drivers, it is more convenient to use but you
can't learn more about the hardware of STM32 MCU.
