#include "header.h"
#include "Arduino.h"  // Include Arduino library for Serial

void print_welcome() {
  // Print Welcome messages.
  lcd.setCursor(5, 0);
  lcd.print("Welcome");

  lcd.setCursor(0, 1); // Set cursor to the first character of the second row
  lcd.print("KBT Electronics"); // Print on the second row

  delay(200); // Wait for two seconds.
  lcd.clear(); // Clear the LCD screen
}


void lcd_water(int Level) {       // We should specify the type of the parameter "Level" in the function declaration.
  // lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Water: ");
  lcd.print(Level);     // Gets "Level" from [trans_loop()].
  lcd.print("%     ");
  // delay(100);
}


void motor_turn_on() {
  digitalWrite(Motor_Pin, HIGH); // Turn on the motor
  pumpOn = true;
}

void motor_turn_off() {
  digitalWrite(Motor_Pin, LOW); // Turn on the motor
  pumpOn = false;
}

void lcd_pump_on() {
  lcd.setCursor(0, 1);
  // displayWithDelay("Pump: ON        ", 1000);
  lcd.print("Pump: ON        ");
  delay(1000);
}

void lcd_pump_off() {
  lcd.setCursor(0, 1);
  // displayWithDelay("Pump: OFF       ", 1000);
  lcd.print("Pump: OFF       ");
  delay(1000);
}

void lcd_mode_auto() {
  lcd.setCursor(0, 1);
  // displayWithDelay("Mode: Automatic ", 1000);
  lcd.print("Mode: Automatic ");
  delay(1000);
}

void lcd_mode_timer() {
  lcd.setCursor(0, 1);
  displayWithDelay("Mode: Set Timer", 1000);
  // lcd.print("Mode: Set Timer ");
  // delay(1000);
}

void lcd_mode_manual() {
  lcd.setCursor(0, 1);
  lcd.print("Mode: Manual    ");
  delay(1000);
}


void displayWithDelay(const char* text, unsigned long delayTime) {
  // Got this code From ChatGPT.
  // i have use '2' here as 'currentMillis' and others have used somewhere else.
  static unsigned long previousMillis2 = 0;
  unsigned long currentMillis2 = millis();

  // Check if the specified delayTime has elapsed
  if (currentMillis2 - previousMillis2 >= delayTime) {
    lcd.setCursor(0, 1);
    lcd.print(text);

    // Update the previousMillis for the next iteration
    previousMillis2 = currentMillis2;
  }
}

