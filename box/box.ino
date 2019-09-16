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
ChallengeDisplay challengeDisplay = ChallengeDisplay();
DisplayTimer displayTimer = DisplayTimer(12, 13, 10, TEST_MODE);
LetterLogic letterLogic = LetterLogic(2, 3, 4, 5, TEST_MODE);

void setup()
{
  Serial.begin(9600);
  
  displayTimer.setup();

  letterLogic.setup();

  challengeDisplay.setup();
  challengeDisplay.setLetters(letterLogic.getCurrentLetters());

  flickSwitches.setup();

  
}

void loop()
{
  displayTimer.loop();
  letterLogic.loop();
  flickSwitches.loop();
  challengeDisplay.loop();

  if (!displayTimer.isComplete())
  {
    //Serial.println("timer not completed");
    if (flickSwitches.currentIsFlicked())
    {
       Serial.println("Current flicked");
      if (letterLogic.isCorrect())
      {
        Serial.println("Guess Correct");
        // Open Current Clamp
        if (flickSwitches.isLast())
        {
          Serial.println("Guess Was Last");
          displayTimer.stop();
        }
        else
        {
          Serial.println("Select Next");
          letterLogic.nextLetter();
          challengeDisplay.setLetters(letterLogic.getCurrentLetters());
          flickSwitches.selectNextFlicker();
        }
      }
      else
      {
        Serial.println("Guess Wrong");
        displayTimer.failed();
      }
    }
  }
}
