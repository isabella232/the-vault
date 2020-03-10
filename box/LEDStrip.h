#ifndef LEDStrip_h
#define LEDStrip_h

#include <FastLED.h>

#define NUM_LEDS 60
#define DATA_PIN 11

CRGB leds[NUM_LEDS];

class LEDStrip {
private:
  unsigned long startMillis;
  unsigned long currentMillis;
  const unsigned long period = 30;
  int x = 0;
public:
  LEDStrip() {}

  void setup() { 
    startMillis = millis();
    FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
  }

  void loop() {
    currentMillis = millis();
    if (currentMillis - startMillis >= period) {
      // Every 30ms do this: 
      startMillis = currentMillis;
      
      leds[x] = CRGB::Blue;
      FastLED.show();
      leds[x] = CRGB::Black;


      if (++x >= NUM_LEDS) x = 0;
    }
  }

  void showSuccess() {
   
  }

  void showFailure() {}
};

#endif