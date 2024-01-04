#include <LiquidCrystal.h>

// Define LCD
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

// Define button pins
const int buttonAutomatic = 8;
const int buttonManual = 9;
const int buttonTimer = 10;

void setup() {
  // Initialize LCD
  lcd.begin(16, 2);

  // Initialize buttons
  pinMode(buttonAutomatic, INPUT_PULLUP);
  pinMode(buttonManual, INPUT_PULLUP);
  pinMode(buttonTimer, INPUT_PULLUP);

  // Display initial message
  lcd.print("Select mode:");

  // Wait for a moment
  delay(200);
}

void loop() {
  // Check buttons
    if (digitalRead(buttonAutomatic) == HIGH && 
        digitalRead(buttonManual) == HIGH && 
        digitalRead(buttonTimer) == HIGH) {
    lcd.clear();
    lcd.print("Pls Select any of the 3 mode");
    delay(100);
  }

  if (digitalRead(buttonAutomatic) == LOW) {
    lcd.clear();
    lcd.print("Mode: Automatic");
    delay(100);
    //automaticMode();
  }
  if (digitalRead(buttonManual) == LOW) {
    lcd.clear();
    lcd.print("Mode: Manual");
    delay(100);
    //manualMode();
  }
  if (digitalRead(buttonTimer) == LOW) {
    lcd.clear();
    lcd.print("Mode: Timer");
    delay(100);
    //timerMode();
  }
}

void automaticMode() {
  // Add your code for automatic mode here
  lcd.clear();
  lcd.print("Automatic Mode");
  delay(200);
}

void manualMode() {
  // Add your code for manual mode here
  lcd.clear();
  lcd.print("Manual Mode");
  delay(200);
}

void timerMode() {
  // Add your code for timer mode here
  lcd.clear();
  lcd.print("Timer Mode");
  delay(200);
}
