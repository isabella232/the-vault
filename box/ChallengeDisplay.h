#ifndef ChallengeDisplay_h
#define ChallengeDisplay_h

#include "ST7036.h"

#define boxNumber 1

// Simple wrap of ST7036 driver
class ChallengeDisplay {
private:
  ST7036 lcd = ST7036(2, 8, 0x78);

  String currentAnswerString = "";
  String answerHistory = "";

  bool failed = false;
  bool succeeded = false;

  byte box[8] = {
      B11111, B11111, B11111, B11111, B11111, B11111, B11111,
  };

public:
  ChallengeDisplay() {}

  void setup() {
    Serial.println("ChallengeDisplay Setup");

    // Initializes and set cursor at origin
    lcd.init();
    lcd.setCursor(0, 0);
    lcd.load_custom_character(boxNumber, box);
  }

  void loop() {}

  void setLetters(String letters) {
    lcd.setCursor(0, 0);
    switch (letters.length()) {
      case 1:
        lcd.print(letters.charAt(0));
        writeBox(0, 2);
        writeBox(0, 4);
        writeBox(0, 6);
        break;
      case 2:
        lcd.print(letters.charAt(0));
        lcd.setCursor(0, 2);
        lcd.print(letters.charAt(1));
        writeBox(0, 4);
        writeBox(0, 6);
        break;
      case 3:
        lcd.print(letters.charAt(0));
        lcd.setCursor(0, 2);
        lcd.print(letters.charAt(1));
        lcd.setCursor(0, 4);
        lcd.print(letters.charAt(2));
        break;
      case 4:
        lcd.print(letters.charAt(0));
        lcd.setCursor(0, 2);
        lcd.print(letters.charAt(1));
        lcd.setCursor(0, 4);
        lcd.print(letters.charAt(2));
        lcd.setCursor(0, 6);
        lcd.print(letters.charAt(3));
        break;
    }
  }

  void setResetMessage() {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(" PLEASE");
    lcd.setCursor(1, 0);
    lcd.print(" RESET!");
  }

  void writeBox(int row, int column) {
    lcd.setCursor(row, column);
    lcd.write(byte(boxNumber));
  }

  void setFailureMessage() {
    if (failed) {
      return;
    }
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("FAILURE!");
    lcd.setCursor(1, 0);
    lcd.print("        ");
    failed = true;
  }

  void setSuccessMessage() {
    if (succeeded) {
      return;
    }
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("SUCCESS!");
    lcd.setCursor(1, 0);
    lcd.print("        ");
    succeeded = true;
  }

  void setRotaryValues(char dial2, char dial1) {
    lcd.setCursor(1, 0);
    String message = "";
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
    lcd.print(answerHistory + message);
    currentAnswerString = message;
  }

  void setAnswerString() {
    answerHistory = answerHistory + currentAnswerString;
    lcd.setCursor(1,0);
    lcd.print(answerHistory + currentAnswerString);
    Serial.println("setAnswerString: " + answerHistory);
  }
};
#endif
