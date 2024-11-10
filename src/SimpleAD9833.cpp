/**
 * @file SimpleAD9833.cpp
 * @brief Implementation file for the SimpleAD9833 library.
 * 
 * This code is provided under free-use rights with credit.
 */

#include "SimpleAD9833.h"

// Constructor: Initialises the SimpleAD9833 object with the given chip select (CS) pin.
SimpleAD9833::SimpleAD9833(uint8_t csPin) : _csPin(csPin) {}

// Initialises the AD9833 device and sets up SPI communication.
void SimpleAD9833::begin() {
  pinMode(_csPin, OUTPUT);
  digitalWrite(_csPin, HIGH);

  _regCtl = 0;
  bitSet(_regCtl, 13); 
  spiSend(_regCtl);

  reset();
  setFrequency(1000);
  setWaveform(SINE);
}

// Resets the AD9833 by setting and clearing the RESET bit in the control register.
void SimpleAD9833::reset() {
  bitSet(_regCtl, 8); 
  spiSend(_regCtl);
  bitClear(_regCtl, 8);
  spiSend(_regCtl);
}

// Sets the output frequency of the AD9833.
bool SimpleAD9833::setFrequency(float freq) {
  uint32_t regFreq = calcFreq(freq);
  spiSend(_regCtl);
  spiSend((1 << 14) | (uint16_t)(regFreq & 0x3FFF));
  spiSend((1 << 14) | (uint16_t)((regFreq >> 14) & 0x3FFF));
  return true;
}

// Sets the waveform type of the AD9833.
bool SimpleAD9833::setWaveform(WaveformMode mode) {
  switch (mode) {
    case SINE:
      bitClear(_regCtl, 5);
      bitClear(_regCtl, 1);
      break;
    case TRIANGLE:
      bitClear(_regCtl, 5);
      bitSet(_regCtl, 1);
      break;
    case SQUARE:
      bitSet(_regCtl, 5);
      bitClear(_regCtl, 1);
      bitSet(_regCtl, 3);
      break;
  }
  spiSend(_regCtl);
  return true;
}

// Sets both the waveform type and the frequency of the AD9833.
bool SimpleAD9833::setWaveform(WaveformMode mode, float freq) {
  setWaveform(mode);
  setFrequency(freq);
  return true;
}

// Sends a 16-bit data word to the AD9833 via SPI.
void SimpleAD9833::spiSend(uint16_t data) {
  digitalWrite(_csPin, LOW);
  
  SPI.beginTransaction(SPISettings(2000000, MSBFIRST, SPI_MODE2));
  SPI.transfer16(data);
  SPI.endTransaction();
  
  digitalWrite(_csPin, HIGH);
}

// Calculates the 28-bit frequency register value for the AD9833.
uint32_t SimpleAD9833::calcFreq(float f) {
  return (uint32_t)((f * AD_2POW28 / AD_MCLK) + 0.5);
}

// Puts the AD9833 into sleep mode to disable output.
void SimpleAD9833::off() {
  bitSet(_regCtl, 7);  // SLEEP1 = 1, disables internal clock
  bitSet(_regCtl, 6);  // SLEEP12 = 1, disables DAC output
  spiSend(_regCtl);
}

// Reactivates the AD9833 output by clearing sleep mode bits.
void SimpleAD9833::on() {
  bitClear(_regCtl, 7); // SLEEP1 = 0, enables internal clock
  bitClear(_regCtl, 6); // SLEEP12 = 0, enables DAC output
  spiSend(_regCtl);
}

