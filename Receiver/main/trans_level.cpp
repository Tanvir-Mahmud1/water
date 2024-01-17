#include "header.h"
#include "Arduino.h"  // Include Arduino library for Serial

#include <VirtualWire.h>

void trans_setup() {
  vw_set_rx_pin(12); // Set the virtual wire receiver pin to pin 12
  vw_setup(2000);     // Bits per second
  vw_rx_start();    // Start the receiver
}

void trans_loop() {
  // Listen for data from the transmitter
  uint8_t buffer[VW_MAX_MESSAGE_LEN];
  uint8_t buflen = VW_MAX_MESSAGE_LEN;
  
  if (vw_get_message(buffer, &buflen)) {
    // Convert received data to integer
    buffer[buflen] = '\0'; // Null-terminate the string
    int trans_Level = atoi((char*)buffer);

    // Print the water level on the LCD
    lcd_water(trans_Level);
    updatePumpState(trans_Level);
  }
}