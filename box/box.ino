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

void guessedRight()
{
  Serial.println("Guessed Right");
}

void guessedWrong()
{
  Serial.println("Guessed Wrong");
}
FlickSwitches flickSwitches = FlickSwitches();
ChallengeDisplay challengeDisplayu = ChallengeDisplay();
DisplayTimer displayTimer = DisplayTimer(12, 13, 10, TEST_MODE);
LetterLogic letterLogic = LetterLogic(2, 3, 4, 5, guessedRight, guessedWrong, TEST_MODE);

void setup()
{
  displayTimer.setup();

  letterLogic.setup();

  challengeDisplayu.setup();
  challengeDisplayu.setLetter(letterLogic.currentLetter());

  flickSwitch.setup();

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
}
