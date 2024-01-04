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
  int valueToReturn = 0; // Default value if no condition is met

  // Conditions to check button states and level
  if (digitalRead(buttonAutomatic) == LOW) {
    if (Level < lowLevel) {
      valueToReturn = 1;
    } else if (Level <= midLevel) {
      valueToReturn = 2;
    } else if (Level > highLevel) {
      valueToReturn = 3;
    }
    
  } else if (digitalRead(buttonManual) == LOW) {
    valueToReturn = 4;


  } else if (digitalRead(buttonTimer) == LOW) {
      unsigned long currentMillis = millis();
      if (digitalRead(buttonOk) == LOW  && startTime == 0) {
        valueToReturn = 5;
      } else if (digitalRead(buttonReset) == LOW) {
        valueToReturn = 6;
      } else if (digitalRead(buttonUp) == LOW) {
        valueToReturn = 7;
      } else if (digitalRead(buttonDown) == LOW) {
        valueToReturn = 8;
      }  
      // else if (digitalRead(buttonOk) == HIGH  &&  digitalRead(buttonReset) == HIGH  &&  
      // digitalRead(buttonUp) == HIGH  &&  digitalRead(buttonDown) == HIGH) {
      //   valueToReturn = 9;
      // }

      // Update and display timer every second
      if (currentMillis - previousMillis >= 1000) {
        updateTimer();
        previousMillis = currentMillis;
      }
  }

  return valueToReturn;
}



