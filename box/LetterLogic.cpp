#include "Rotary.h"
#include "LetterLogic.h"


LetterLogic::LetterLogic(char r1p1, char r1p2, char r2p1, char r2p2) {
	r1 = new Rotary(r1p1, r1p2);
	r2 = new Rotary(r2p1, r2p2);
}

void LetterLogic::guessedRight()
{
	Serial.println("Guessed Right");
}

void LetterLogic::guessedWrong()
{
	Serial.println("Guessed Wrong");
}

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

// 1 is correct guess
// 0 is no guess
// -1 is wrong guess
char LetterLogic::guess(bool switches[], char guess)
{
	if (sizeof(switches) != 4)
	{
		Serial.println("Not enough switches exist: " + sizeof(switches));
		return 0;
	}
	if (switches[correctGuesses])
	{
		if (guess == displayedLetter)
		{
			return 1;
		}
		else
		{
			return -1;
		}
	}
	else
	{
		return 0;
	}
}

char LetterLogic::rotateLetter(int dial1Dir, int dial2Dir)
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
		return dial1Pos + (dial2Pos * 16);
	}
	else
	{
		return 0;
	}
}

void LetterLogic::setup() 
{
	// Listen to changes in rotary encoder
	r1->begin();
	r2->begin();

	displayedLetter = randomLetter();
}

void LetterLogic::loop() 
{
	bool switches[] = {true, true, true, true};

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

	char currentGuess = rotateLetter(dial1Dir, dial2Dir);
	char isCorrectGuess = guess(switches, currentGuess);

	if (isCorrectGuess == 1)
	{
		guessedRight();
	}
	else if (isCorrectGuess == -1)
	{
		guessedWrong();
	}
}
