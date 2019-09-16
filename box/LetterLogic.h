#ifndef LetterLogic_h
#define LetterLogic_h

#include "Rotary.h"
#include "ChallengeDisplay.h"
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

	public:
		LetterLogic(char r1p1, char r1p2, char r2p1, char r2p2, ChallengeDisplay *_challengeDisplay, bool _test_mode);
		void setup();
		void loop();
		bool isCorrect();
		void nextLetter();
		String getCurrentLetters();
	private:
		char randomLetter();
		void rotateLetter(int dial1Dir, int dial2Dir);
};

#endif
