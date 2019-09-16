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
FlickSwitches flickSwitches = FlickSwitches(6, 8, 9, 11);
ChallengeDisplay challengeDisplayu = ChallengeDisplay();
DisplayTimer displayTimer = DisplayTimer(12, 13, 10, TEST_MODE);
LetterLogic letterLogic = LetterLogic(2, 3, 4, 5, TEST_MODE);

void setup()
{
  displayTimer.setup();

  letterLogic.setup();

  challengeDisplayu.setup();
  challengeDisplayu.setLetters(letterLogic.getCurrentLetters());

  flickSwitches.setup();

  Serial.begin(9600);
}

void loop()
{
  displayTimer.loop();
  letterLogic.loop();
  flickSwitches.loop();
  challengeDisplayu.loop();

  if (!displayTimer.isComplete())
  {
    //Serial.println("timer not completed");
    if (flickSwitches.currentIsFlicked())
    {
       //Serial.println("Current flicked");
      if (letterLogic.isCorrect())
      {
        // Open Current Clamp
        if (flickSwitches.isLast())
        {
          displayTimer.stop();
        }
        else
        {
          letterLogic.nextLetter();
          challengeDisplayu.setLetters(letterLogic.getCurrentLetters());
          flickSwitches.selectNextFlicker();
        }
      }
      else
      {
        displayTimer.failed();
      }
    }
  }
}
