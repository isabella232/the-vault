#include "LedControl.h"
#include "SimpleTimer.h"
/*
 Now we need a LedControl to work with.
 ***** These pin numbers will probably not work with your hardware *****
 pin 12 is connected to the DataIn 
 pin 13 is connected to the CLK 
 pin 10 is connected to LOAD 
 We have only a single MAX72XX.
 */
LedControl lc = LedControl(12,13,10,1);

// Our timer
SimpleTimer timer = SimpleTimer();

// 2 min in seconds
int time = 120;

void countdown() {
  time = time - 1;
  int minutes = (time / 60);
  int seconds = seconds - (minutes * 60);
  // int milliSeconds = time / (60 * 60);
  Serial.println("Start");
  Serial.println(minutes);
  Serial.println(seconds);
  // Serial.println(milliSeconds);
  Serial.println("Stop");
  showOnDisplay(0, minutes, seconds / 10, seconds % 10, 0, 0, 0, 0);
}


void setup() {
  Serial.begin(9600);
  Serial.println(time);
  /*
   The MAX72XX is in power-saving mode on startup,
   we have to do a wakeup call
   */
  lc.shutdown(0,false);
  /* Set the brightness to a medium values */
  lc.setIntensity(0,8);
  /* and clear the display */
  lc.clearDisplay(0);

  
  timer.setTimer(1000, countdown, time);  
}

void loop() { 
  timer.run();
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
