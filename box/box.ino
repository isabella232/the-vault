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

void guessedRight()
{
	Serial.println("Guessed Right");
}

void guessedWrong()
{
	Serial.println("Guessed Wrong");
}

DisplayTimer displayTimer = DisplayTimer(12, 13, 10, TEST_MODE);
LetterLogic letterLogic = LetterLogic(2, 3, 4, 5, guessedRight, guessedWrong, TEST_MODE);

int flichSwitchIn = 7; // choose the input pin (for a pushbutton)
int flichSwitchInValue = 0;

void setup()
{
  displayTimer.setup();
  letterLogic.setup();

  Serial.begin(9600);

  //detect switch button
  pinMode(flichSwitchIn, INPUT);
}

void loop()
{
  displayTimer.loop();
  letterLogic.loop();

  flichSwitchInValue = digitalRead(flichSwitchIn); // read input value
  if (flichSwitchInValue)
  {
    displayTimer.stop();
  }
  else
  {
    displayTimer.start();
  }
}
