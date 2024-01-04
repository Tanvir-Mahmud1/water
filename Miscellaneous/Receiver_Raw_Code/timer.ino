#include <LiquidCrystal.h>

LiquidCrystal lcd(7, 6, 5, 4, 3, 2);  // Define LCD

const int buttonOk = 8;
const int buttonReset = 9;
const int buttonUp = 11;
const int buttonDown = 10;

unsigned long timerDuration = 0;  // Timer duration in seconds
unsigned long startTime = 0;     // Time when the timer started

void setup() {
  lcd.begin(16, 2);
  lcd.print("Press OK to start");

  pinMode(buttonOk, INPUT_PULLUP);
  pinMode(buttonReset, INPUT_PULLUP);
  pinMode(buttonUp, INPUT_PULLUP);
  pinMode(buttonDown, INPUT_PULLUP);
}

void loop() {
  // Check buttons
  if (digitalRead(buttonOk) == LOW && startTime == 0) {
    startTimer();
  }
  if (digitalRead(buttonReset) == LOW) {
    resetTimer();
  }
  if (digitalRead(buttonUp) == LOW) {
    incrementTimer(300);  // Add 5 minutes
  }
  if (digitalRead(buttonDown) == LOW) {
    decrementTimer(300);  // Subtract 5 minutes
  }

  // Update and display timer
  updateTimer();
  delay(1000);  // Update every second
}

void startTimer() {
  lcd.clear();
  lcd.print("Timer started");
  startTime = millis();  // Record start time
}

void resetTimer() {
  lcd.clear();
  lcd.print("Timer reset");
  timerDuration = 0;
  startTime = 0;
}

void incrementTimer(unsigned long increment) {
  lcd.clear();
  lcd.print("Time +5 min");
  timerDuration += increment;
}

void decrementTimer(unsigned long decrement) {
  if (timerDuration >= decrement) {
    lcd.clear();
    lcd.print("Time -5 min");
    timerDuration -= decrement;
  } else {
    lcd.clear();
    lcd.print("Minimum time reached");
  }
}

void updateTimer() {
  if (startTime != 0) {
    unsigned long elapsedSeconds = (millis() - startTime) / 1000;
    unsigned long remainingSeconds = (timerDuration > elapsedSeconds) ? (timerDuration - elapsedSeconds) : 0;

    lcd.setCursor(0, 1);
    lcd.print("Time: ");
    lcd.print(remainingSeconds / 60);  // Minutes
    lcd.print(":");
    if ((remainingSeconds % 60) < 10) {
      lcd.print("0");  // Add leading zero for seconds less than 10
    }
    lcd.print(remainingSeconds % 60);  // Seconds

    if (remainingSeconds == 0) {
      lcd.clear();
      lcd.print("Timer complete");
      startTime = 0;  // Reset timer after countdown
    }
  }
}
