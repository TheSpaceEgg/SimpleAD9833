/**
 * @file SimpleAD9833.h
 * @brief Header file for the SimpleAD9833 library.
 * 
 * This code is provided under free-use rights with credit.
 */

#pragma once
#include <Arduino.h>
#include <SPI.h>

// Enumeration for the waveform types supported by the AD9833.
enum WaveformMode { SINE, SQUARE, TRIANGLE };

class SimpleAD9833 {
public:
    /**
     * @brief Constructor for the SimpleAD9833 class.
     */
    SimpleAD9833(uint8_t csPin);

    /**
     * @brief Initialises the AD9833 and sets default configurations.
     */
    void begin();

    /**
     * @brief Resets the AD9833 by toggling the RESET bit in the control register.
     */
    void reset();
  
    /**
     * @brief Sets the output frequency of the AD9833.
     * 
     * @param freq The desired output frequency in Hz.
     * @return True if the frequency is set successfully.
     */
    bool setFrequency(float freq);

    /**
     * @brief Sets the waveform type for the AD9833.
     * 
     * @param mode The desired waveform mode (SINE, TRIANGLE, or SQUARE).
     * @return True if the waveform type is set successfully.
     */
    bool setWaveform(WaveformMode mode);

    /**
     * @brief Sets both the waveform type and the output frequency for the AD9833.
     * 
     * @param mode The desired waveform mode (SINE, TRIANGLE, or SQUARE).
     * @param freq The desired output frequency in Hz.
     * @return True if both waveform type and frequency are set successfully.
     */
    bool setWaveform(WaveformMode mode, float freq);

    /**
     * @brief Puts the AD9833 into sleep mode to disable output.
     */
    void off();

    /**
     * @brief Reactivates the AD9833 output by clearing sleep mode.
     */
    void on();

private:
    uint8_t _csPin; // Chip select pin
    uint16_t _regCtl; // Control register value

    SPIClass _spi; // SPI class instance

    const uint32_t AD_MCLK = 25000000UL; // Master clock frequency
    const uint32_t AD_2POW28 = (1UL << 28); // 2^28 constant for frequency calculation

    /**
     * @brief Sends a 16-bit data word to the AD9833 via SPI.
     * 
     * @param data The 16-bit data word to be sent.
     */
    void spiSend(uint16_t data);

    /**
     * @brief Calculates the 28-bit frequency register value from the provided frequency in Hz.
     * 
     * @param f The desired frequency in Hz.
     * @return The calculated 28-bit frequency register value.
     */
    uint32_t calcFreq(float f);
};

