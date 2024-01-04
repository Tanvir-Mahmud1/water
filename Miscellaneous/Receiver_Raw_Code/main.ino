#include <VirtualWire.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(A5, A4, A3, A2, A1, A0);

const int Motor_Pin = 13;
bool pumpOn = false;  // Variable to track pump state

void setup() {
  vw_set_rx_pin(12); // Set the virtual wire receiver pin to pin 11
  vw_setup(2000);     // Bits per second
  vw_rx_start();    // Start the receiver
  lcd.begin(16, 2);
  pinMode(Motor_Pin, OUTPUT);
  // Initialize pump state based on water level
  int initialLevel = readWaterLevel(); // Implement a function to read the initial water level
  updatePumpState(initialLevel);
}
void loop() {
  // Listen for data from the transmitter
  uint8_t buffer[VW_MAX_MESSAGE_LEN];
  uint8_t buflen = VW_MAX_MESSAGE_LEN;
  if (vw_get_message(buffer, &buflen)) {
    // Convert received data to integer
    buffer[buflen] = '\0'; // Null-terminate the string
    int Level = atoi((char*)buffer);
    // Print the water level on the LCD
    lcd.setCursor(0, 0);
    lcd.print("Water: ");
    lcd.print(Level);
    lcd.print("%     ");
    // Control the motor based on water level
    updatePumpState(Level);
  }
}
void updatePumpState(int waterLevel) {
  if (waterLevel < 30) {
    digitalWrite(Motor_Pin, HIGH); // Turn on the motor
    pumpOn = true;
    lcd.setCursor(0, 1);
    lcd.print("Pump: ON     ");
  } else if (waterLevel >= 90) {
    digitalWrite(Motor_Pin, LOW); // Turn off the motor
    pumpOn = false;
    lcd.setCursor(0, 1);
    lcd.print("Pump: OFF    ");
  }
  // If water level is between 30 and 90, maintain the pump state
  // (either on or off) based on the previous state.
  // This prevents the pump from turning on after a reset in this range.
}
int readWaterLevel() {
  // Implement a function to read the initial water level from your sensor
  // Replace this with the actual code to read the water level.
  // This function should return an integer representing the water level.
  // Example: return analogRead(Water_Level_Pin);
  return 0; // Replace with actual implementation
}