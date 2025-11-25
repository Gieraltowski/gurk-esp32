# General Use Runtime Kernel (GURK) for ESP32

![ESP32](https://img.shields.io/badge/ESP32-Platform-blue.svg)
![PlatformIO](https://img.shields.io/badge/PlatformIO-Compatible-brightgreen.svg)
![License](https://img.shields.io/badge/License-GPLv3-blue.svg)

A portable runtime kernel and bytecode interpreter for embedded systems, enabling cross-platform execution on various microcontrollers including ESP32.

GURK provides a hardware abstraction layer through a custom bytecode interpreter. Write once, run anywhere on supported embedded platforms.

**Traditional Microcontroller Program:**
Your Program -> Board harware

**GURK:**
Your Program -> GURK -> Board Hardware (example: ESP32)
Your Program -> GURK -> Other Board Hardware (example: Arduino Uno)

## ✨ Key Innovation

Write programs in GURK bytecode, compile once, and distribute the same binary to users with different microcontroller boards - it will work on all supported platforms without recompilation.
