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
  int x = 0;
  bool on = false;
public:
  LEDStrip() {}

  void setup() { 
    startMillis = millis();
    FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);

    for (int i = 0; i < NUM_LEDS; i++) {
      leds[i] = CRGB::Black;    
    }
    FastLED.show();
  }

  void loop() {
   
  }

  void showSuccess() {
    currentMillis = millis();
    if (currentMillis - startMillis >= 1000) {
      startMillis = currentMillis;

      for (int i = 0; i < NUM_LEDS; i++) {
        if (on) {
          leds[i] = CRGB::Black;
          FastLED.show();
        } else {
          leds[i] = CRGB::Green;
          FastLED.show();
        }    
      }
      
      on = !on;
    }
  }

  void showFailure() {
    currentMillis = millis();
    if (currentMillis - startMillis >= 1000) {
      // Every 30ms do this: 
      startMillis = currentMillis;

      for (int i = 0; i < NUM_LEDS; i++) {
        if (on) {
          leds[i] = CRGB::Black;
        } else {
          leds[i] = CRGB::Red;
        }    
      }
      FastLED.show();
      on = !on;
    }
  }
};

#endif