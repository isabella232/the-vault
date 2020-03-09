#ifndef DisplayTimer_h
#define DisplayTimer_h
#include <Time.h>
#include <SoftwareSerial.h>
#include <math.h>
#include "LedControl.h"

class DisplayTimer {
private:
  LedControl *lc;

  bool TEST_MODE = false;
  bool stopped = false;
  bool completed = false;
  long stoppedOffset = 0;
  long timeTarget = 120000;
  long time = 0;
  long COMPLETED_DURATION_MS = 250;

  void countdown() {
    int minutes;
    int seconds;
    int milliseconds;
    int one;
    int two;
    int three;
    int offsetOne = 2;
    int offsetTwo = 1;

    if (!stopped) {
      time = timeTarget - millis();
    }

    if (time < 0) {
      time = 0;
      offsetOne = offsetTwo = 0;

      stopped = true;
      completed = true;
    }

    minutes = floor(time / 60 / 1000);
    seconds = floor((time / 1000) - (minutes * 60));
    milliseconds = time - (minutes * 60000) - (seconds * 1000);

    one = floor(milliseconds / 100);
    two = floor((milliseconds - (one * 100)) / 10);
    three = floor(milliseconds - (one * 100) - (two * 10));

    showOnDisplay(0, minutes, seconds / 10, seconds % 10, one, two,
                  two + offsetOne, two + offsetTwo);
  }

  void showOnDisplay(int first, int second, int third, int fourth, int fifth,
                     int sixth, int seventh, int eighth) {
    lc->setDigit(0, 7, first, false);
    lc->setDigit(0, 6, second, true);
    lc->setDigit(0, 5, third, false);
    lc->setDigit(0, 4, fourth, true);
    lc->setDigit(0, 3, fifth, false);
    lc->setDigit(0, 2, sixth, false);
    lc->setDigit(0, 1, seventh, false);
    lc->setDigit(0, 0, eighth, false);
  }

public:
  DisplayTimer(int dataPin, int clkPin, int csPin, bool _TEST_MODE) {
    TEST_MODE = _TEST_MODE;
    lc = new LedControl(dataPin, clkPin, csPin, 1); // 12, 13, 10, 1);
  }

  bool isStopped() { return stopped; }

  bool isComplete() { return completed; }

  void setup() {
    Serial.println("DisplayTimer Setup");
    if (TEST_MODE) {
      timeTarget = 120000;
    }

    lc->shutdown(0, false); // The MAX72XX is in power-saving mode on startup,
                            // we have to do a wakeup call
    lc->setIntensity(0, 8); /* Set the brightness to a medium values */
    lc->clearDisplay(0);    /* and clear the display */
  }

  void loop() {
    if (!stopped && !completed) {
      countdown();
    } else if (stopped) {
      if ((millis() % (COMPLETED_DURATION_MS * 2)) < COMPLETED_DURATION_MS) {
        lc->setIntensity(0, 0); /* Set the brightness to a medium values */
      } else {
        lc->setIntensity(0, 8); /* Set the brightness to a medium values */
      }
    }
  }
  void failed() {
    stopped = true;
    completed = true;
  }

  void stop() {
    if (!stopped) {
      stoppedOffset = millis();
      stopped = true;
    }
  }

  void complete() {
    completed = true;
    // stopped = true;
  }

  void start() {
    if (stopped && time >= 0) {
      timeTarget = timeTarget + (millis() - stoppedOffset);
      stoppedOffset = 0;

      stopped = false;
    }
  }
};
#endif
