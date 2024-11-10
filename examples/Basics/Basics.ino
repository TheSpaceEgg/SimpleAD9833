/*
 * Example script for SimpleAD9833 library
 * Author: Will Hickmott
 * GitHub: TheSpaceEgg
 * Date: 10 November 2024
 * 
 * Description:
 * This example demonstrates how to use the SimpleAD9833 library to control 
 * an AD9833 waveform generator. It includes setting different waveforms 
 * (sine, triangle, square) and iterating through the C Major scale frequencies.
 * 
 * License:
 * This code is provided under a free-use license, with the condition that 
 * appropriate credit is given to the author (TheSpaceEgg). 
 * Redistribution and use in source and binary forms, with or without modification, 
 * are permitted provided that proper attribution is maintained.
 */
 
 #include <SimpleAD9833.h>

// Define the SPI pins
const uint8_t SCLK_PIN = 18;
const uint8_t DATA_PIN = 19;
const uint8_t CS_PIN = 5;

// Frequencies for the C Major scale (in Hz)
const float cMajorScale[] = {261.63, 293.66, 329.63, 349.23, 392.00, 440.00, 493.88, 523.25};

// Instantiate the SimpleAD9833 object with the chip select (CS) pin
SimpleAD9833 myWaveform(CS_PIN);

void setup() {
  Serial.begin(115200); // Start serial communication for debugging
  while (!Serial);      

  Serial.println("\n\nSimpleAD9833 Example");

  // Initialise SPI communication using the defined pins
  SPI.begin(SCLK_PIN, -1, DATA_PIN);
  Serial.println("Starting SPI");

  // Initialise the AD9833 chip for waveform generation
  myWaveform.begin();
  Serial.println("Starting AD9833\n");
  delay(1000);
}

void loop() {
  // Loop through different waveform types (Sine, Triangle, Square)
  for (int j = 0; j < 3; j++) {
    // Iterate through the C Major scale frequencies
    for (int i = 0; i < 8; i++) {
      if (!i) {
        // On the first frequency, set the waveform type and initial frequency
        switch (j) {
          case 0:
            myWaveform.on(); // Enable waveform output
            Serial.println("Turning output on");
            myWaveform.setWaveform(SINE, cMajorScale[i]); // Set waveform to Sine and frequency
            Serial.println("Setting waveform to Sine");
            break;
          case 1:
            myWaveform.setWaveform(TRIANGLE, cMajorScale[i]); // Set waveform to Triangle and frequency
            Serial.println("Setting waveform to Triangle");
            break;
          case 2:
            myWaveform.setWaveform(SQUARE, cMajorScale[i]); // Set waveform to Square and frequency
            Serial.println("Setting waveform to Square");
            break;
        }
        // Print the frequency set
        Serial.println("Setting frequency to " + String(cMajorScale[i]) + "Hz");
      } else {
        // Update the frequency while keeping the current waveform type
        myWaveform.setFrequency(cMajorScale[i]);
        Serial.println("Setting frequency to " + String(cMajorScale[i]) + "Hz");
      }
      delay(1000); 
    }
  }

  // Turn off the waveform output after cycling through all frequencies
  myWaveform.off();
  Serial.println("Turning output off\n");
  delay(2000); 

  // Demonstrate changing waveforms individually with delays
  myWaveform.on();
  Serial.println("Turning output on");
  myWaveform.setWaveform(SINE); // Set the waveform to Sine without changing frequency
  Serial.println("Setting waveform to Sine");
  delay(2000);

  myWaveform.setWaveform(TRIANGLE); // Change the waveform to Triangle
  Serial.println("Setting waveform to Triangle");
  delay(2000);

  myWaveform.setWaveform(SQUARE); // Change the waveform to Square
  Serial.println("Setting waveform to Square");
  delay(2000);

  // Turn off the output again
  myWaveform.off();
  Serial.println("Turning output off\n");
  delay(2000);
}
