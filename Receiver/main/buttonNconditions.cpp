#include "header.h"
#include "Arduino.h"  // Include Arduino library for Serial

// Defining Timer Pins.
const int buttonUp = 2;
const int buttonDown = 3;
const int buttonReset = 4;
const int buttonOk = 5;

// Defining Mode Pins.
const int buttonAutomatic = 8;
const int buttonManual = 7;
const int buttonTimer = 6;

const int Motor_Pin = 13;
bool pumpOn = false;  // Variable to track pump state

// Defining water level.
const int lowLevel = 30;
const int midLevel = 80;
const int highLevel = 81;

const int incrementTime = 10;
const int decrementTime = 10;


void pump_setup() {
  pinMode(Motor_Pin, OUTPUT);

  // Initializing Mode Pins.
  pinMode(buttonAutomatic, INPUT_PULLUP);
  pinMode(buttonManual, INPUT_PULLUP);
  pinMode(buttonTimer, INPUT_PULLUP);

  // Initializing Timer Pins.
  pinMode(buttonUp, INPUT_PULLUP);
  pinMode(buttonDown, INPUT_PULLUP);
  pinMode(buttonReset, INPUT_PULLUP);
  pinMode(buttonOk, INPUT_PULLUP);
}


int updatePumpState(int Level) {

  // Conditions to check button states and level
  if (digitalRead(buttonAutomatic) == LOW) {
    if (Level < lowLevel) {
      motor_turn_on();
      lcd_mode_auto();
      lcd_pump_on();
      showSetTime = true;
      timerDuration = 0;
      startTime = 0;

    } else if (Level < highLevel  && Level > lowLevel) {
      lcd_mode_auto();
      if (pumpOn) {
        lcd_pump_on();
      } else if (!pumpOn) {
        lcd_pump_off();
      }
      showSetTime = true;
      timerDuration = 0;
      startTime = 0;

    } else if (Level > highLevel) {
      motor_turn_off();
      lcd_mode_auto();
      lcd_pump_off();
      showSetTime = true;
      timerDuration = 0;
      startTime = 0;
    }
    
  } else if (digitalRead(buttonManual) == LOW) {
    lcd_mode_manual();
    delay(1000);  // Delays 2 seconds (1 here and 1 in the function)  sothat Motor_Pin doesn't start immediately.
    motor_turn_on();
    lcd_pump_on();
    showSetTime = true;
    timerDuration = 0;
    startTime = 0;


  } else if (digitalRead(buttonTimer) == LOW) {

      unsigned long currentMillis = millis();
      if (pumpOn && showSetTime) {
        motor_turn_off();
      }

      if (digitalRead(buttonOk) == LOW  && startTime == 0) {
        start_btn();
        showSetTime = false;

      } else if (digitalRead(buttonReset) == LOW) {
        resetTimer();
        showSetTime = false;

      } else if (digitalRead(buttonUp) == LOW) {
        incrementTimer(incrementTime);
        showSetTime = false;

      } else if (digitalRead(buttonDown) == LOW) {
        decrementTimer(decrementTime);
        showSetTime = false;

      // If no button is pressed, this code will execute.
      } else if (showSetTime){
        lcd_pls_setTime();
      }

      // Update and display timer every second
      if (currentMillis - previousMillis >= 1000) {
        updateTimer();
        previousMillis = currentMillis;
      }
  }
}



