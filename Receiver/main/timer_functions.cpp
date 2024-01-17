#include "header.h"
#include "Arduino.h"  // Include Arduino library for Serial

unsigned long timerDuration = 0;  // Timer duration in seconds
unsigned long startTime = 0;     // Time when the timer started
unsigned long previousMillis = 0; // Variable to store the last time LCD was updated

bool showSetTime = true;
bool showMessage = true;
bool start_btn_pressed = false;  // This is for to check if start button is pressed or not, and needed in increament and decreament timer while timer is already on. 
                                // To check if timer is running or not, otherwise when pressing the timer button its start running the timer as millis() is started.

void start_btn() {
  if (timerDuration > 0) {
    startTime = millis();  // Record start time
    start_btn_pressed = true;
  } else {
    lcd.setCursor(0, 1);
    lcd.print("Timer is not Set");
    delay(1000);
    lcd_pls_setTime();
  }
}


void resetTimer() {
  timerDuration = 0;
  startTime = 0;
  start_btn_pressed = false;  // This will help again to increament or decreament timer while timer is already on.
  if (pumpOn) {
    motor_turn_off();
  }
  lcd.setCursor(0, 1);
  lcd.print("Timer Stop/Reset");
  delay(1000);
  lcd_pls_setTime();
}


void incrementTimer(unsigned long increment) {
  // Bellow part of the code [till else block] is for increasing time while timer is already on and user want to increment time from that moment.
  double rem_sec = updateTimer();   // This line will get data about how many time have been passed, sothat we can add time with that.
  if (rem_sec > 0 && start_btn_pressed) {     // This if condition will check if timer is already is on or not i.e. start button is pressed or not
    startTime = millis();           // This line will start counting the millis() just like when we press start button, it is almost like pressing start button.
    timerDuration = rem_sec + increment;  // This line will set new timerDuration with added time and remaining seconds.
  } else {
    timerDuration += increment;     // This else block is for when timer is not on/start button is not pressed/Base State.
  }
  formatTimer();
}



void decrementTimer(unsigned long decrement) {
  if (timerDuration >= decrement) {
    // Bellow part of the code [till 1st else block] is for decreasing time while timer is already on and user want to decrement time from that moment.
    double rem_sec = updateTimer();   // This line will get data about how many time have been passed, sothat we can subtrack time with that.
    if (rem_sec > 0 && start_btn_pressed) {                // This if condition will check if timer is already is on or not i.e. start button is pressed or not.
      startTime = millis();           // This line will start counting the millis() just like when we press start button, it is almost like pressing start button.
      timerDuration = rem_sec - decrement;  // This line will set new timerDuration by [remaining seconds - reduced time].
    } else {
      timerDuration -= decrement;     // This else block is for when timer is not on/start button is not pressed/Base State.
    }
    formatTimer();

  } else {            // This block is for when this button is pressed/function is called but [timerDuration < decrement time].
    lcd.setCursor(0, 1);
    lcd.print("Min Time Reached");
    delay(1000);
    lcd_pls_setTime();
  }
}



void min_sec_format(unsigned int minutes, unsigned int seconds) {
  // Print minutes (right-aligned)
  if (minutes < 10) {
    lcd.print(" "); // Pad a space for single-digit minutes
  }
  lcd.print(String(minutes, DEC));  // Display minutes
  lcd.print(":");
  
  // Print seconds (right-aligned with leading zero if needed)
  if (seconds < 10) {
    lcd.print("0");   // Add leading zero for single-digit seconds
  }
  lcd.print(String(seconds, DEC));
  lcd.print(" "); // Pad with a space after the time.
}


void formatTimer() {
  // Calculate minutes and seconds
  unsigned int minutes = timerDuration / 60;
  unsigned int seconds = timerDuration % 60;

  lcd.setCursor(0, 1);
  lcd.print("Time Set: ");
  // Display the formatted time on the LCD
  min_sec_format(minutes, seconds);
}



double updateTimer() {
  if (startTime != 0) {
    motor_turn_on();
    unsigned long elapsedSeconds = (millis() - startTime) / 1000;
    unsigned long remainingSeconds = (timerDuration > elapsedSeconds) ? (timerDuration - elapsedSeconds) : 0;
    // Calculate minutes and seconds
    unsigned long minutes = remainingSeconds / 60;
    unsigned long seconds = remainingSeconds % 60;
    lcd.setCursor(0, 1);
    lcd.print("Time Rem: ");
    min_sec_format(minutes, seconds);

    if (remainingSeconds == 0) {
      motor_turn_off();
      startTime = 0;  // Reset timer after countdown
      bool showMessage = true;
      start_btn_pressed = false;  // This will help again to increament or decreament timer while timer is already on.
      timerDuration = 0;    // This is for setting last remembered timer to zero, sothat when startring the timer agian it will start from zero, not the last one.
      if (!showSetTime) {
        lcd.setCursor(0, 1);
        lcd.print("Timer Completed ");
        delay(1000);
      }
      lcd_pls_setTime();
    }
    return remainingSeconds;
  }
}
