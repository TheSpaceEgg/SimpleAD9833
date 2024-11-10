# SimpleAD9833
 Arduino library for very easy interfacing with the AD9833 signal generator

## Overview
The `SimpleAD9833` library is an Arduino library designed to provide a simplified interface for controlling the AD9833 waveform generator IC. With this library, users can generate sine, triangle, and square waveforms at user-defined frequencies with ease.

## Features
- Supports generating sine, triangle, and square waveforms.
- Provides functions for setting and adjusting waveform frequencies.
- Simplified SPI communication handling for the AD9833.

## Usage
### Basic Example
Here's a simple example of how to use the `SimpleAD9833` library:

```cpp
#include <SimpleAD9833.h>

const uint8_t CS_PIN = 10; // Chip select pin for the AD9833
SimpleAD9833 myWaveform(CS_PIN);

void setup() {
    Serial.begin(115200);
    SPI.begin()
    myWaveform.begin();
    myWaveform.setWaveform(SINE, 1000); // Set waveform to sine at 1 kHz
}

void loop() {
    // Additional code for operation
}
