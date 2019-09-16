#ifndef LetterLogic_h
#define LetterLogic_h

#include "Rotary.h"

class LetterLogic {
	Rotary *r1;
	Rotary *r2;
	bool TEST_MODE;

	char displayedLetter = 'A';
	char currentGuess;
	String currentLetters = "";
	int correctGuesses = 0;

	char NUM_POSITIONS = 18;
	char dial1Pos = 1;
	char dial2Pos = 4;

	public:
		LetterLogic(char r1p1, char r1p2, char r2p1, char r2p2, bool _test_mode);
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
