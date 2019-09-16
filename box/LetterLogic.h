#ifndef LetterLogic_h
#define LetterLogic_h

#include "Rotary.h"

class LetterLogic {
	Rotary *r1;
	Rotary *r2;
	bool TEST_MODE;

	char displayedLetter = 'A';
	int correctGuesses = 0;

	char NUM_POSITIONS = 18;
	char dial1Pos = 0;
	char dial2Pos = 0;
	void (*guessedRight)();
	void (*guessedWrong)();

	public:
		LetterLogic(char r1p1, char r1p2, char r2p1, char r2p2, void (*_guessedRight)(), void (*_guessedWrong)(), bool _test_mode);
		void setup();
		void loop();
	private:
		char randomLetter();
		void readSwitches(bool switches[]);
		char guess(bool switches[], char guess);
		char rotateLetter(int dial1Dir, int dial2Dir);
};

#endif
