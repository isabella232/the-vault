#ifndef ChallengeDisplay_h
#define ChallengeDisplay_h

#include "ST7036.h"

// Simple wrap of ST7036 driver
class ChallengeDisplay {
private:
  ST7036 lcd = ST7036(2, 8, 0x78);

public:
  ChallengeDisplay() {}

  void setup() {
    Serial.println("ChallengeDisplay Setup");

    // Initializes and set cursor at origin
    lcd.init();
    lcd.setCursor(0, 0);
  }

  void loop() {}

  void setLetters(String letters) {
    Serial.println("LETTERS:" +letters);
    lcd.setCursor(0, 0);
    lcd.print(letters);
  }

  void setResetMessage() {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(" PLEASE");
    lcd.setCursor(1, 0);
    lcd.print(" RESET!");
  }

  void setFailureMessage() {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("FAILURE!");
    lcd.setCursor(1, 0);
    lcd.print("        ");
  }

  void setSuccessMessage() {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("SUCCESS!");
    lcd.setCursor(1, 0);
    lcd.print("        ");
  }

  void setRotaryValues(char dial2, char dial1) {
    lcd.setCursor(1, 0);
    String message = "   ";
    if (dial1 <= 9) {
      message += (int)dial1;
    } else {
      switch (dial1) {
      case 10:
        message += "A";
        break;
      case 11:
        message += "B";
        break;
      case 12:
        message += "C";
        break;
      case 13:
        message += "D";
        break;
      case 14:
        message += "E";
        break;
      case 15:
        message += "F";
        break;
      }
    }
    message += "";
    if (dial2 <= 9) {
      message += (int)dial2;
    } else {
      switch (dial2) {
      case 10:
        message += "A";
        break;
      case 11:
        message += "B";
        break;
      case 12:
        message += "C";
        break;
      case 13:
        message += "D";
        break;
      case 14:
        message += "E";
        break;
      case 15:
        message += "F";
        break;
      }
    }
    lcd.print(message);
  }
};
#endif
