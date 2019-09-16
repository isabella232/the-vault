#include "Rotary.h"
#include "DisplayTimer.h"
#include "LedControl.h"
#include <math.h>
#include "LetterLogic.h"
#include "ChallengeDisplay.h"
#include "FlickSwitches.h"

bool TEST_MODE = true;
/*
 Now we need a LedControl to work with.
 ***** These pin numbers will probably not work with your hardware *****
 pin 12 is connected to the DataIn 
 pin 13 is connected to the CLK 
 pin 10 is connected to LOAD 
 We have only a single MAX72XX.
 */
FlickSwitches flickSwitches = FlickSwitches();
ChallengeDisplay challengeDisplayu = ChallengeDisplay();
DisplayTimer displayTimer = DisplayTimer(12, 13, 10, TEST_MODE);
LetterLogic letterLogic = LetterLogic(2, 3, 4, 5, TEST_MODE);

int flichSwitchIn = 7; // choose the input pin (for a pushbutton)
int flichSwitchInValue = 0;

void setup()
{
  displayTimer.setup();

  letterLogic.setup();

  challengeDisplayu.setup();
  challengeDisplayu.setLetter(letterLogic.currentLetter());

  FlickSwitches flickSwitches = FlickSwitches();
  flickSwitch.setup();

  Serial.begin(9600);

  //detect switch button
  pinMode(flichSwitchIn, INPUT);
}

void loop()
{
  displayTimer.loop();
  letterLogic.loop();
  flickSwitches.loop();
  challengeDisplayu.loop();

  if (!displayTimer.isComplete())
  {
    if (flickSwitches.currentIsFlicked())
    {
      if (letterLogic.isCorrect())
      {
        // Open Current Clamp
        if (flickSwitches.isLast())
        {
          displayTimer.stop(;)
        }
        else
        {
          letterLogic.nextLetter();
          challengeDisplayu.setLetters(letterLogic.currentLetters());
          flickSwitches.selectNextFlicker();
        }
      }
      else
      {
        displayTimer.failed();
      }
    }
  }

  //TEST
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
