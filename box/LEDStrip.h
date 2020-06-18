#ifndef LEDStrip_h
#define LEDStrip_h

#include "Arduino.h"
#include <FastLED.h>
#include "DisplayTimer.h"


// Remember to update the numbers responsible for setting the color for countdown
#define NUM_LEDS 69
#define DATA_PIN 11

CRGB leds[NUM_LEDS];

class LEDStrip {
private:
  unsigned long startMillis;
  unsigned long currentMillis;
  int x = 0;
  bool on = false;
  DisplayTimer *timer;

public:
  LEDStrip(DisplayTimer *_timer) {
    timer = _timer;
  }

  void setup() { 
    startMillis = millis();
    FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);

    for (int i = 0; i < NUM_LEDS; i++) {
      leds[i] = CRGB::Black;    
    }
    FastLED.show();
  }

  void loop() {
    currentMillis = millis();
    
    if (currentMillis - startMillis >= 1000) {
      startMillis = currentMillis;

      long secondsLeft =  timer->getTime();
      long target = timer->getTarget();
      float secondsPerLed = (float) target / (float) NUM_LEDS;
      int ledToLightUpTo = secondsLeft / secondsPerLed;
      for (int i = 0; i < NUM_LEDS; i++) {
        if (i <= ledToLightUpTo) {
            

          if (ledToLightUpTo > 32) {
            leds[i] = CRGB::Green;    
          } else if (ledToLightUpTo > 22) {
            leds[i] = CHSV( 64, 255, 255); // Yellow
          } else if (ledToLightUpTo > 12) {
            leds[i] = CHSV( 22, 255, 255); // Orange
          } else {
            leds[i] = CRGB::Red;
          }

        } else {
          leds[i] = CRGB::Black;    
        }
      } 
      FastLED.show();
    }
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