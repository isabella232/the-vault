#include "LedControl.h"
#include "SimpleTimer.h"
#include "Rotary.h"
#include <math.h>
/*
 Now we need a LedControl to work with.
 ***** These pin numbers will probably not work with your hardware *****
 pin 12 is connected to the DataIn 
 pin 13 is connected to the CLK 
 pin 10 is connected to LOAD 
 We have only a single MAX72XX.
 */
LedControl lc = LedControl(12, 13, 10, 1);

// Our timer
SimpleTimer timer = SimpleTimer();
int timerId;
// 2 min in milliseconds
long time = 120000;

// Rotary encoder stuff
Rotary r1 = Rotary(2, 3);

void setup() {
  Serial.begin(9600);

  lc.shutdown(0, false); // The MAX72XX is in power-saving mode on startup, we have to do a wakeup call
  lc.setIntensity(0, 8); /* Set the brightness to a medium values */
  lc.clearDisplay(0); /* and clear the display */

  // Start our timer here
  timerId = timer.setInterval(1, countdown);  

  // Listen to changes in rotary encoder
  r1.begin();
}

void loop() { 
  timer.run();

  int result = r1.process();
  if (result) {
    Serial.println(result == DIR_CW ? "Right" : "Left");
  }
}

void countdown() {
  time = time - 1;

  int minutes = floor(time / 60 / 1000);
  int seconds = floor((time / 1000) - (minutes * 60));
  int milliseconds = time - (minutes * 60000) - (seconds * 1000);

  int one = floor(milliseconds / 100);
  int two = floor((milliseconds - (one * 100)) / 10);
  int three = floor(milliseconds - (one * 100) - (two * 10));

  showOnDisplay(0, minutes, seconds / 10, seconds % 10, one, two, three, three);

  // Stop timer after we've shown full zeros on the display
  if (time == 0) {
    timer.disable(timerId);
    timer.deleteTimer(timerId);
    return;
  }
}

void showOnDisplay(int first, int second, int third, int fourth, int fifth, int sixth, int seventh, int eighth) {
  lc.setDigit(0, 7, first, false);
  lc.setDigit(0, 6, second, true);
  lc.setDigit(0, 5, third, false);
  lc.setDigit(0, 4, fourth, true);
  lc.setDigit(0, 3, fifth, false);
  lc.setDigit(0, 2, sixth, true);
  lc.setDigit(0, 1, seventh, false);
  lc.setDigit(0, 0, eighth, false);
}