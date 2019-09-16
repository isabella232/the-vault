#ifndef ChallengeDisplay_h
#define ChallengeDisplay_h

#include "ST7036.h"

// Simple wrap of ST7036 driver
class ChallengeDisplay
{
private:
  ST7036 lcd = ST7036(2, 8, 0x78);

public:
  ChallengeDisplay()
  {
    // Setup Midas 2x8 LCD display
    // 0x3C shifted << 1
    //
    //lcd = new ST7036(2, 8, 0x78);
  }

  void setup()
  {
    Serial.println("ChallengeDisplay Setup");

    // Initializes and set cursor at origin
    lcd.init();
   
  }

  void loop() {}

  void setLetters(String letters)
  {
    lcd.setCursor(0,0);
    lcd.print(letters);
    Serial.println(letters);
  }
};
#endif
