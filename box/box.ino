#include "Rotary.h"
#include "DisplayTimer.h"
#include "LedControl.h"
#include <math.h>
#include "LetterLogic.h"

bool TEST_MODE = true;
/*
 Now we need a LedControl to work with.
 ***** These pin numbers will probably not work with your hardware *****
 pin 12 is connected to the DataIn 
 pin 13 is connected to the CLK 
 pin 10 is connected to LOAD 
 We have only a single MAX72XX.
 */
DisplayTimer displayTimer = DisplayTimer(12, 13, 10, TEST_MODE);

int flichSwitchIn = 7; // choose the input pin (for a pushbutton)
int flichSwitchInValue = 0;

LetterLogic *ll = new LetterLogic(2, 3, 4, 5);

void setup()
{
  displayTimer.Setup();

  Serial.begin(9600);

  // Start our timer here
  ll->setup();

  //detect switch button
  pinMode(flichSwitchIn, INPUT);
}

void loop()
{
  displayTimer.Loop();
  ll->loop();

  flichSwitchInValue = digitalRead(flichSwitchIn); // read input value
  if (flichSwitchInValue)
  {
    displayTimer.Stop();
  }
  else
  {
    displayTimer.Start();
  }
}
