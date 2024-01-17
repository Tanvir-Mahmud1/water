#include "header.h"

#include <LiquidCrystal.h>

LiquidCrystal lcd(0, 1, A0, A1, A2, A3);

void setup() {
  lcd.begin(16, 2);
  print_welcome();

  trans_setup();
  pump_setup();

}

void loop() {
  // Getting data from Transmitter module.
  trans_loop();

}

