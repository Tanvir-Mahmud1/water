// header.h File....
#ifndef HEADER_H
#define HEADER_H

#include <LiquidCrystal.h>      // As <LiquidCrystal.h> is used in multiple file, i have added that in header file.
extern LiquidCrystal lcd;       // We also need to add this here, got this from ChatGPT.

// Function declarations
void trans_setup();
void trans_loop();

void pump_setup();
int updatePumpState(int waterLevel);

void print_welcome();

void mode_loop();

void lcd_water(int Level);     // We should specify the type of the parameter Level in the function declaration.

void performAction(int value, int Level);

void motor_turn_on();
void motor_turn_off();
void lcd_pump_on();
void lcd_pump_off();
void lcd_mode_auto();
void lcd_mode_timer();
void lcd_mode_manual();

void startTimer();
void resetTimer();
void incrementTimer(unsigned long increment);
void decrementTimer(unsigned long decrement);
void updateTimer();

void displayWithDelay(const char* text, unsigned long delayTime);

// Constants
extern const int Motor_Pin;
extern bool pumpOn;
extern unsigned long startTime; 
extern unsigned long previousMillis;
extern bool showMessage;

extern const int lowLevel;
extern const int midLevel;
extern const int highLevel;

extern const int incrementTime;
extern const int decrementTime;


#endif
