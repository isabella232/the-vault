#ifndef LetterLogic_h
#define LetterLogic_h

#include "ChallengeDisplay.h"
#include "Rotary.h"
#include <avr/eeprom.h>

class LetterLogic {
  Rotary *r1;
  Rotary *r2;
  bool TEST_MODE;

  char displayedLetter = 'A';
  char currentGuess;
  String currentLetters = "";
  int correctGuesses = 0;
  ChallengeDisplay *challengeDisplay;

  char NUM_POSITIONS = 16;
  char dial1Pos = 0;
  char dial2Pos = 0;

private:
  char randomLetter() {
    // hex 41 is dec 65
    if (TEST_MODE) {
      return 65 + correctGuesses;
    } else {
      return random(65, 65 + 26);
    }
  }

  void rotateLetter(int dial1Dir, int dial2Dir) {
    if (dial1Dir) {
      if (dial1Dir == DIR_CW) {
        dial1Pos = ((dial1Pos + 1) + NUM_POSITIONS) % NUM_POSITIONS;
      } else {
        dial1Pos = ((dial1Pos - 1) + NUM_POSITIONS) % NUM_POSITIONS;
      }
      Serial.println((int)dial1Pos);
    }
    if (dial2Dir) {
      if (dial2Dir == DIR_CW) {
        dial2Pos = ((dial2Pos + 1) + NUM_POSITIONS) % NUM_POSITIONS;
      } else {
        dial2Pos = ((dial2Pos - 1) + NUM_POSITIONS) % NUM_POSITIONS;
      }
      Serial.println((int)dial2Pos);
    }
    if (dial1Pos <= 15 && dial2Pos <= 15) {
      currentGuess = dial1Pos + (dial2Pos * 16);
    } else {
      currentGuess = 0;
    }

    if (dial1Dir || dial2Dir) {
      challengeDisplay->setRotaryValues(dial1Pos, dial2Pos);
      Serial.println(currentGuess);
    }
  }

public:
  LetterLogic(char r1p1, char r1p2, char r2p1, char r2p2,
              ChallengeDisplay *_challengeDisplay, bool _test_mode) {
    r1 = new Rotary(r1p1, r1p2);
    r2 = new Rotary(r2p1, r2p2);
    TEST_MODE = _test_mode;
    challengeDisplay = _challengeDisplay;
  }

  void setup() {
    randomSeed(analogRead(A0)); // TODO Issue as A0 is used

    Serial.println("LetterLogic Setup");
    r1->begin();
    r2->begin();

    challengeDisplay->setRotaryValues(dial1Pos, dial2Pos);

    displayedLetter = randomLetter();
  }

  void loop() {
    int dial1Dir = r1->process();
    if (dial1Dir) {
      Serial.println(dial1Dir == DIR_CW ? "Right" : "Left");
    }

    int dial2Dir = r2->process();
    if (dial2Dir) {
      Serial.println(dial2Dir == DIR_CW ? "Right" : "Left");
    }

    rotateLetter(dial1Dir, dial2Dir);
  }

  bool isCorrect() {
    if (currentGuess == displayedLetter) {
      return true;
    } else {
      return false;
    }
  }

  void nextLetter() {
    correctGuesses += 1;
    displayedLetter = randomLetter();
  }

  String getCurrentLetters() {
    currentLetters = String(currentLetters + displayedLetter);
    return currentLetters;
  }
};

#endif
