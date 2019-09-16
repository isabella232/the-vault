#include "LedControl.h"
#include "SimpleTimer.h"
#include "Rotary.h"
#include <math.h>
/*
 Now we need a LedControl to work with.
 ***** These pin numbers will probably not work with your hardware *****
 pin 12 is connected to the DataIn 
 pin 13 is connected to the CLK 
 pin 10 is connected to LOAD 
 We have only a single MAX72XX.
 */
bool TEST_MODE = false;

LedControl lc = LedControl(12, 13, 10, 1);

// Our timer
SimpleTimer timer = SimpleTimer();
int timerId;
// 2 min in milliseconds
long time = 120000;

// Rotary encoder stuff
Rotary r1 = Rotary(2, 3);
Rotary r2 = Rotary(4, 5);

char displayedLetter = 'A';
int correctGuesses = 0;

char NUM_POSITIONS = 18;
char dial1Pos = 0;
char dial2Pos = 0;

char randomLetter() {
	if (TEST_MODE) {
		return 'A' + correctGuesses;
	} else {
		return rand() % 26 + 41;
	}
}

// 1 is correct guess
// 0 is no guess
// -1 is wrong guess
char guess(bool[] switches, char guess) {
	if (sizeof(switches) != 4) {
		return 0;
	}
	if (switches[correctGuesses]) {
		if (guess == displayedLetter) {
			return 1;
		} else {
			return -1;
		}
	} else {
		return 0;
	}
}

char rotateLetter(int dial1Dir, int dial2Dir) {
	if (dial1Dir) {
		if (dial1Dir == DIR_CW) {
			dial1Pos = (dial1Pos + 1) % NUM_POSITIONS;
		} else {
			dial1Pos = (dial1Pos - 1) % NUM_POSITIONS;
		}
	}
	if (dial2Dir) {
		if (dial2Dir == DIR_CW) {
			dial2Pos = (dial2Pos + 1) % NUM_POSITIONS;
		} else {
			dial2Pos = (dial2Pos - 1) % NUM_POSITIONS;
		}
	}
	if (dial1Pos <= 15 && dial2Pos <= 15) {
		return dial1Pos + (dial2Pos * 16);
	} else {
		return 0;
	}
}

void guessedRight() {
  	Serial.println("Guessed Right");
}

void guessedWrong() {
  	Serial.println("Guessed Wrong");
}

void setup() {
  Serial.begin(9600);

  lc.shutdown(0, false); // The MAX72XX is in power-saving mode on startup, we have to do a wakeup call
  lc.setIntensity(0, 8); /* Set the brightness to a medium values */
  lc.clearDisplay(0); /* and clear the display */

  // Start our timer here
  timerId = timer.setInterval(1, countdown);  

  // Listen to changes in rotary encoder
  r1.begin();
  r2.begin();

  displayedLetter = randomLetter();
}

void loop() { 
  timer.run();

  int dial1Dir = r1.process();
  if (dial1Dir) {
    Serial.println(dial1Dir == DIR_CW ? "Right" : "Left");
  }

  int dial2Dir = r2.process();
  if (dial2Dir) {
  	Serial.println(dial2Dir == DIR_CW ? "Right" : "Left");
  }

  bool[] switches = {true, true, true, true};

  char currentGuess = rotateLetter(dial1Dir, dial2Dir);
  char isCorrectGuess = guess(switches, currentGuess);

  if (isCorrectGuess == 1) {
	  guessedRight();
  } else if (isCorrectGuess == -1) {
	  guessedWrong();
  }
}

void countdown() {
  time = time - 1;

  int minutes = floor(time / 60 / 1000);
  int seconds = floor((time / 1000) - (minutes * 60));
  int milliseconds = time - (minutes * 60000) - (seconds * 1000);

  int one = floor(milliseconds / 100);
  int two = floor((milliseconds - (one * 100)) / 10);
  int three = floor(milliseconds - (one * 100) - (two * 10));

  showOnDisplay(0, minutes, seconds / 10, seconds % 10, one, two, three, three);

  // Stop timer after we've shown full zeros on the display
  if (time == 0) {
    timer.disable(timerId);
    timer.deleteTimer(timerId);
    return;
  }
}

void showOnDisplay(int first, int second, int third, int fourth, int fifth, int sixth, int seventh, int eighth) {
  lc.setDigit(0, 7, first, false);
  lc.setDigit(0, 6, second, true);
  lc.setDigit(0, 5, third, false);
  lc.setDigit(0, 4, fourth, true);
  lc.setDigit(0, 3, fifth, false);
  lc.setDigit(0, 2, sixth, true);
  lc.setDigit(0, 1, seventh, false);
  lc.setDigit(0, 0, eighth, false);
}
