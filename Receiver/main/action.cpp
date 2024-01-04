#include "header.h"
#include "Arduino.h"  // Include Arduino library for Serial

bool showMessage = true;

// Function to perform different actions based on the returned value
void performAction(int value, int Level) {
  // Perform different actions based on the value returned by checkCondition()
  switch (value) {
    case 1:
      motor_turn_on();
      lcd_pump_on();
      lcd_mode_auto();
      break;
      
    case 2:
      motor_turn_on();
      lcd_pump_on();
      lcd_mode_auto();
      break;
      
    case 3:
      motor_turn_off();
      lcd_pump_off();
      lcd_mode_auto();
      break;
      
    case 4:
      lcd_mode_manual();
      delay(1000);  // Delays 2 seconds (1 here and 1 in the function)  sothat Motor_Pin doesn't start immediately.
      motor_turn_on();
      lcd_pump_on();

      // Bellow codes are for, if we want to turn motor off even if it is in manual mode but water tank is full.
      // if (Level < highLevel) {
      //   motor_turn_on();
      //   lcd_pump_on();
      // } else if (Level >= highLevel) {
      //   motor_turn_off();
      //   lcd_pump_off();
      // }

      break;

    case 5:
      startTimer();
      // lcd_mode_timer();
      break;

    case 6:
      // lcd_mode_timer();
      resetTimer();
      break;

    case 7:
      // lcd_mode_timer();
      incrementTimer(incrementTime);
      break;

    case 8:
      // lcd_mode_timer();
      decrementTimer(decrementTime);
      break;


    default:
      // Default action if no specific value matches.
      // bool showMessage = true; written in top.
      if (showMessage) {
        lcd.setCursor(0, 1);
        lcd.print("Please Set Time.");
        showMessage = false;  // Set the flag to false so the message won't be displayed again
      }
      break;
  }
}
