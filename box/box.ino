#include "ChallengeDisplay.h"
#include "DisplayTimer.h"
#include "FlickSwitches.h"
#include "LatchControl.h"
#include "LedControl.h"
#include "LetterLogic.h"
#include "Rotary.h"
#include <math.h>

bool TEST_MODE = true;

FlickSwitches flickSwitches = FlickSwitches(6, 7, 8, 9);
ChallengeDisplay challengeDisplay = ChallengeDisplay();
DisplayTimer displayTimer = DisplayTimer(12, 13, 10, TEST_MODE);
LetterLogic letterLogic = LetterLogic(4, 5, 2, 3, &challengeDisplay, TEST_MODE);
LatchControl latchControl = LatchControl(A0, A1, A2, A3);

void setup() {
  Serial.begin(9600);

  latchControl.setup();

  displayTimer.setup();

  challengeDisplay.setup();

  letterLogic.setup();

  challengeDisplay.setLetters(letterLogic.getCurrentLetters());

  flickSwitches.setup();

  while (!flickSwitches.isAllReset()) {
    challengeDisplay.setResetMessage();
    exit(0);
  }
}

void loop() {
  latchControl.loop();
  displayTimer.loop();
  letterLogic.loop();
  flickSwitches.loop();
  challengeDisplay.loop();

  // If we have run out of time, then we show the failure message and nothing else
  if (displayTimer.isComplete()) {
    displayFailure();
    return;
  }

  // We need to wait for the user to flick the current switch before we can decide what to do
  if (!flickSwitches.currentIsFlicked()) {
    return;
  }
  
  // If the guess was not correct we tell the user that they failed
  if (!letterLogic.isCorrect()) {
    // Calling failed here causes the failure message to be display in the if statement above
    displayTimer.failed();
    return;
  }

  // The users guess was correct, so we open the current latch
  latchControl.openLatch(flickSwitches.getCurrentSwitch());
  

  // If this was not the last switch, we need to set the next letter and 
  if (!flickSwitches.isLast()) {
    letterLogic.nextLetter();
    challengeDisplay.setLetters(letterLogic.getCurrentLetters());
    flickSwitches.selectNextFlicker();
    return;
  }

  // Once we get here, the switch is in fact the last switch, so we display success
  displaySuccess();
}

void displayFailure() {
  challengeDisplay.setFailureMessage();
  while (!flickSwitches.isAllReset()) {
    latchControl.loop();
    displayTimer.loop();
  }
}

void displaySuccess() {
  challengeDisplay.setSuccessMessage();
  displayTimer.complete();
  while (!flickSwitches.isAllReset()) {
    latchControl.loop();
    displayTimer.loop();
  }
}
