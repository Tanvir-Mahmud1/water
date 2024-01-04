#include "header.h"
#include "Arduino.h"  // Include Arduino library for Serial

unsigned long timerDuration = 0;  // Timer duration in seconds
unsigned long startTime = 0;     // Time when the timer started
unsigned long previousMillis = 0; // Variable to store the last time LCD was updated


void startTimer() {
  // if we need to show "Timer started" msg, then bellow code is needed. Else its no need.
  // lcd.setCursor(0, 1);
  // lcd.print("Timer started    ");
  startTime = millis();  // Record start time
}

void resetTimer() {
  timerDuration = 0;
  startTime = 0;

  lcd.setCursor(0, 1);
  lcd.print("Timer Reset     ");
  delay(1000);
  lcd.setCursor(0, 1);
  lcd.print("Please Set Time.");
}


void incrementTimer(unsigned long increment) {
  timerDuration += increment;

  // Calculate minutes and seconds
  unsigned int minutes = timerDuration / 60;
  unsigned int seconds = timerDuration % 60;

  // Display the formatted time on the LCD
  lcd.setCursor(0, 1);
  lcd.print("Time Set: ");

  // Print minutes (right-aligned)
  if (minutes < 10) {
    lcd.print(" "); // Pad a space for single-digit minutes
  }
  lcd.print(String(minutes, DEC));  // Display minutes
  lcd.print(":");

  // Print seconds (right-aligned with leading zero if needed)
  // Display seconds with leading zero if less than 10
  if (seconds < 10) {
    lcd.print("0"); // Add leading zero for single-digit seconds
  }
  lcd.print(String(seconds, DEC));
  lcd.print(" "); // Pad with a space after the time
}



void decrementTimer(unsigned long decrement) {
  if (timerDuration >= decrement) {
    // Decrement the timer duration
    timerDuration -= decrement;

    // Calculate minutes and seconds
    unsigned int minutes = timerDuration / 60;
    unsigned int seconds = timerDuration % 60;

    // Display the formatted time on the LCD
    lcd.setCursor(0, 1);
    lcd.print("Time Set: ");

    // Print minutes (right-aligned)
    if (minutes < 10) {
      lcd.print(" "); // Pad a space for single-digit minutes
    }
    lcd.print(String(minutes, DEC));  // Display minutes
    lcd.print(":");
    
    // Display seconds with leading zero if less than 10
    if (seconds < 10) {
      lcd.print("0");
    }
    lcd.print(String(seconds, DEC));
    lcd.print(" "); // Pad with a space after the time

    // Additional code for any actions related to the updated time can be added here
  } else {
    lcd.setCursor(0, 1);
    lcd.print("Minimum T Reached");
  }
}


void updateTimer() {
  if (startTime != 0) {
    motor_turn_on();

    unsigned long elapsedSeconds = (millis() - startTime) / 1000;
    unsigned long remainingSeconds = (timerDuration > elapsedSeconds) ? (timerDuration - elapsedSeconds) : 0;

    lcd.setCursor(0, 1);
    lcd.print("Time Rem: ");

    // Calculate minutes and seconds
    unsigned long minutes = remainingSeconds / 60;
    unsigned long seconds = remainingSeconds % 60;

    // Print minutes (right-aligned)
    if (minutes < 10) {
      lcd.print(" "); // Pad a space for single-digit minutes
    }
    lcd.print(minutes);
    lcd.print(":");

    // Print seconds (right-aligned with leading zero if needed)
    if (seconds < 10) {
      lcd.print("0"); // Add leading zero for single-digit seconds
    }
    lcd.print(seconds);
    lcd.print(" "); // Pad with a space after the time

    if (remainingSeconds == 0) {
      motor_turn_off();

      lcd.setCursor(0, 1);
      lcd.print("Timer Completed ");
      delay(1000);
      // displayWithDelay("Timer Completed ", 1000);

      startTime = 0;  // Reset timer after countdown
      bool showMessage = true;

      lcd.setCursor(0, 1);
      lcd.print("Please Set Time.");
    }
  }
}
