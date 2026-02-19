# KL25Z Interrupt-Driven I/O System

Embedded C project developed for the NXP FRDM-KL25Z (ARM Cortex-M0+) microcontroller using Keil uVision.

This project demonstrates GPIO configuration, interrupt handling (IRQ), stack usage, timing control, and structured embedded software design.



## Project Overview

The system measures human reaction time using interrupt-driven input and LED output feedback.

Users press hardware switches in response to LED activation, and the firmware records iteration counts to approximate reaction timing.



## Hardware Platform

- NXP FRDM-KL25Z Development Board  
- ARM Cortex-M0+  
- RGB LEDs (on-board)  
- 3 × Momentary Pushbuttons  
- Optional debounce capacitors (1µF)  



## System Features

- GPIO initialization and configuration  
- Interrupt Request (IRQ) handling  
- Interrupt Service Routine (ISR) implementation  
- State-variable driven LED control  
- Software delay-loop calibration  
- Random delay generation using `rand()`  
- Reaction-time iteration counting  
- Counter storage and averaging  



## Software Architecture

- `main.c` contains final working implementation  
- `Device/` contains startup and MCU configuration files  
- `Include/` contains header definitions  
- `Sources/` contains modular source implementations  



## Embedded Concepts Demonstrated

- Interrupt-driven programming  
- Hardware polling vs ISR priority handling  
- Stack usage and timing control  
- Deterministic state transitions  
- Peripheral initialization  
- Embedded C modular structure  



## Tools Used

- Keil uVision5  
- ARM MDK v5.31  
- NXP FRDM-KL25Z  

