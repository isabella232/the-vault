#include "LedControl.h"
#include <math.h>
#include "LetterLogic.h"

/*
 Now we need a LedControl to work with.
 ***** These pin numbers will probably not work with your hardware *****
 pin 12 is connected to the DataIn 
 pin 13 is connected to the CLK 
 pin 10 is connected to LOAD 
 We have only a single MAX72XX.
 */

int flichSwitchIn = 7; // choose the input pin (for a pushbutton)
int flichSwitchInValue = 0;

LedControl lc = LedControl(12, 13, 10, 1);

long timeTarget = 120000;
long time = 0;

LetterLogic *ll = new LetterLogic(2, 3, 4, 5);

void setup()
{
  Serial.begin(9600);

  lc.shutdown(0, false); // The MAX72XX is in power-saving mode on startup, we have to do a wakeup call
  lc.setIntensity(0, 8); /* Set the brightness to a medium values */
  lc.clearDisplay(0);    /* and clear the display */

  // Start our timer here

  ll->setup();

  //detect switch button
  pinMode(flichSwitchIn, INPUT);
}

void loop()
{
  countdown();
  flichSwitchInValue = digitalRead(flichSwitchIn); // read input value
  ll->loop();
}

void countdown()
{
  int minutes;
  int seconds;
  int milliseconds;
  int one;
  int two;
  int three;

  if (flichSwitchInValue == LOW)
  {
    time = timeTarget - millis();
    if (time < 0)
    {
      time = 0;
    }
  }

  minutes = floor(time / 60 / 1000);
  seconds = floor((time / 1000) - (minutes * 60));
  milliseconds = time - (minutes * 60000) - (seconds * 1000);

  one = floor(milliseconds / 100);
  two = floor((milliseconds - (one * 100)) / 10);
  three = floor(milliseconds - (one * 100) - (two * 10));

  showOnDisplay(0, minutes, seconds / 10, seconds % 10, one, two, two + 1, two + 2);
}

void showOnDisplay(int first, int second, int third, int fourth, int fifth, int sixth, int seventh, int eighth)
{
  lc.setDigit(0, 7, first, false);
  lc.setDigit(0, 6, second, true);
  lc.setDigit(0, 5, third, false);
  lc.setDigit(0, 4, fourth, true);
  lc.setDigit(0, 3, fifth, false);
  lc.setDigit(0, 2, sixth, true);
  lc.setDigit(0, 1, seventh, false);
  lc.setDigit(0, 0, eighth, false);
}
