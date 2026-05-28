# cubeSolver-1.0
The first iteration of the 3x3 Puzzle (Rubik's Cube) Solver. This utilized an STM32 and an ESP32 microcontroller. 

## Overview

This project was written in C/C++. The majority of the program lived on the STM32, while the ESP32 simply was used to send and receive data from a webserver.

The STM32 sends the cube state to the ESP32 via UART. The ESP sends the cube state to a webserver, waits for the response, and then returns the solution to the cube back to the STM32 via UART. The STM32 then handles the decoding of the solution into motor rotations. 

A video of the device can be found here:

[![Here](https://img.youtube.com/vi/g6azCDgdOEg/hqdefault.jpg)](https://www.youtube.com/shorts/g6azCDgdOEg)

This project is in the works of being revised. See cubeSolver-2.0.
