#include <VirtualWire.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(7, 6, 5, 4, 3, 2); // Adjust the pin numbers based on your wiring

const int trigPin = 8; // Change the pin numbers as needed
const int echoPin = 9; // Change the pin numbers as needed
const int Motor_Pin = 13; // Change the pin numbers as needed

long duration;
int distance;

void setup() {
  vw_set_tx_pin(12); // Set the virtual wire transmitter pin to pin 12
  vw_setup(2000);     // Bits per second
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(Motor_Pin, OUTPUT);

  lcd.begin(16, 2); // Initialize the LCD with 16 columns and 2 rows

  // Initialize motor state and display water level
  int initialLevel = readWaterLevel(); // Implement a function to read the initial water level
  updateMotorState(initialLevel);
  displayWaterLevel(initialLevel);
}

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;
  int Level = map(distance, 0, 1000, 0, 100);

  // Update motor state and display water level
  updateMotorState(Level);
  displayWaterLevel(Level);

  // Send the water level wirelessly
  char buffer[5];
  sprintf(buffer, "%d", Level);
  vw_send((uint8_t*)buffer, strlen(buffer));
  vw_wait_tx();

  delay(50); // Adjust delay based on your requirements
}

void updateMotorState(int waterLevel) {
  // Control the motor based on water level
  if (waterLevel < 30) {
    digitalWrite(Motor_Pin, HIGH); // Turn on the motor
  } else if (waterLevel >= 90) {
    digitalWrite(Motor_Pin, LOW); // Turn off the motor
  }
  // If water level is between 30 and 90, maintain the motor state
  // based on the previous state after Arduino reset.
}

void displayWaterLevel(int waterLevel) {
  // Print the water level on the LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Water Level: ");
  lcd.print(waterLevel);
  lcd.print("%");
}

int readWaterLevel() {
  // Implement a function to read the initial water level from your sensor
  // Replace this with the actual code to read the water level.
  // This function should return an integer representing the water level.
  // Example: return analogRead(Water_Level_Pin);
  return 0; // Replace with actual implementation
}
