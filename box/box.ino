#include "Rotary.h"
#include "DisplayTimer.h"
#include "LedControl.h"
#include <math.h>
#include "LetterLogic.h"
#include "ChallengeDisplay.h"
#include "FlickSwitches.h"
#include "LatchControl.h"

bool TEST_MODE = true;
/*
  Now we need a LedControl to work with.
 ***** These pin numbers will probably not work with your hardware *****
  pin 12 is connected to the DataIn
  pin 13 is connected to the CLK
  pin 10 is connected to LOAD
  We have only a single MAX72XX.
*/
FlickSwitches flickSwitches = FlickSwitches(6, 7, 8, 9);
ChallengeDisplay challengeDisplay = ChallengeDisplay();
DisplayTimer displayTimer = DisplayTimer(12, 13, 10, TEST_MODE);
LetterLogic letterLogic = LetterLogic(4, 5,2, 3, &challengeDisplay, TEST_MODE);
LatchControl latchControl = LatchControl(A0, A1, A2, A3);

void setup(){
  Serial.begin(9600);

  latchControl.setup();

  displayTimer.setup();

  challengeDisplay.setup();

  letterLogic.setup();

  challengeDisplay.setLetters(letterLogic.getCurrentLetters());

  flickSwitches.setup();
}

void loop(){
  latchControl.loop();
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
        latchControl.openLatch(flickSwitches.getCurrentSwitch());
        
        if (flickSwitches.isLast()){
          Serial.println("Guess Was Last");
          displaySuccess();
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
  }else{
      displayFailure();
    }
}

void displayFailure(){
    challengeDisplay.setLetters("FAILURE!");
    while(!flickSwitches.isAllReset()){
      latchControl.loop();
      displayTimer.loop();
    }
    resetGame();
}

void displaySuccess(){
    displayTimer.complete();
    challengeDisplay.setLetters("SUCCESS!");
    while(!flickSwitches.isAllReset()){
      latchControl.loop();
      displayTimer.loop();
    }
    resetGame();
}

void resetGame(){
  Serial.println("Resetting game");
  while(true){};
  //TODO Reset game elements
}
