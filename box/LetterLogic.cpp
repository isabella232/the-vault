#include "Rotary.h"
#include "LetterLogic.h"


//public
LetterLogic::LetterLogic(char r1p1, char r1p2, char r2p1, char r2p2, bool _test_mode) {
	r1 = new Rotary(r1p1, r1p2);
	r2 = new Rotary(r2p1, r2p2);
	TEST_MODE = _test_mode;
}

//public
void LetterLogic::setup() 
{
	Serial.println("LetterLogic Setup");
	r1->begin();
	r2->begin();

	displayedLetter = randomLetter();
}

//public
void LetterLogic::loop() 
{
	int dial1Dir = r1->process();
	if (dial1Dir)
	{
		Serial.println(dial1Dir == DIR_CW ? "Right" : "Left");
	}

	int dial2Dir = r2->process();
	if (dial2Dir)
	{
		Serial.println(dial2Dir == DIR_CW ? "Right" : "Left");
	}

	rotateLetter(dial1Dir, dial2Dir);
}

//public
bool LetterLogic::isCorrect()
{
	if (currentGuess == displayedLetter)
	{
		return true;
	}
	else
	{
		return false;
	}
}

//public
void LetterLogic::nextLetter()
{
	displayedLetter = randomLetter();
	currentGuess += 1;
}

//public
String LetterLogic::getCurrentLetters()
{
	currentLetters = String(currentLetters + displayedLetter);
	return currentLetters;
}

//private
char LetterLogic::randomLetter()
{
	if (TEST_MODE)
	{
		return 'A' + correctGuesses;
	}
	else
	{
		return rand() % 26 + 41;
	}
}

//private
void LetterLogic::rotateLetter(int dial1Dir, int dial2Dir)
{
	if (dial1Dir)
	{
		if (dial1Dir == DIR_CW)
		{
			dial1Pos = (dial1Pos + 1) % NUM_POSITIONS;
		}
		else
		{
			dial1Pos = (dial1Pos - 1) % NUM_POSITIONS;
		}
	}
	if (dial2Dir)
	{
		if (dial2Dir == DIR_CW)
		{
			dial2Pos = (dial2Pos + 1) % NUM_POSITIONS;
		}
		else
		{
			dial2Pos = (dial2Pos - 1) % NUM_POSITIONS;
		}
	}
	if (dial1Pos <= 15 && dial2Pos <= 15)
	{
		currentGuess = dial1Pos + (dial2Pos * 16);
	}
	else
	{
		currentGuess = 0;
	}

   if(dial1Dir || dial2Dir){
     Serial.println(currentGuess);
  }
}
