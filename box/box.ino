#include "Rotary.h"
#include <math.h>
#include "DisplayTimer.h"

bool TEST_MODE = true;
/*
 Now we need a LedControl to work with.
 ***** These pin numbers will probably not work with your hardware *****
 pin 12 is connected to the DataIn 
 pin 13 is connected to the CLK 
 pin 10 is connected to LOAD 
 We have only a single MAX72XX.
 */
DisplayTimer displayTimer = DisplayTimer(12, 13, 10, TEST_MODE);

int flichSwitchIn = 7; // choose the input pin (for a pushbutton)
int flichSwitchInValue = 0;

// Rotary encoder stuff
Rotary r1 = Rotary(2, 3);
Rotary r2 = Rotary(4, 5);

char displayedLetter = 'A';
int correctGuesses = 0;

char NUM_POSITIONS = 18;
char dial1Pos = 0;
char dial2Pos = 0;

char randomLetter()
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
char guess(bool switches[], char guess)
{
  if (sizeof(switches) != 4)
  {
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

char rotateLetter(int dial1Dir, int dial2Dir)
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

void guessedRight()
{
  Serial.println("Guessed Right");
}

void guessedWrong()
{
  Serial.println("Guessed Wrong");
}

void setup()
{
  displayTimer.Setup();

  Serial.begin(9600);

  // Start our timer here

  // Listen to changes in rotary encoder
  r1.begin();
  r2.begin();

  displayedLetter = randomLetter();

  //detect switch button
  pinMode(flichSwitchIn, INPUT);
}

void loop()
{
  displayTimer.Loop();

  int result = r1.process();
  if (result)
  {
    Serial.println(result == DIR_CW ? "Right" : "Left");
    int dial1Dir = r1.process();
    if (dial1Dir)
    {
      Serial.println(dial1Dir == DIR_CW ? "Right" : "Left");
    }

    int dial2Dir = r2.process();
    if (dial2Dir)
    {
      Serial.println(dial2Dir == DIR_CW ? "Right" : "Left");
    }

    bool switches[] = {true, true, true, true};

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

  flichSwitchInValue = digitalRead(flichSwitchIn); // read input value
  if (flichSwitchInValue)
  {
    displayTimer.Stop();
  }
  else
  {
    displayTimer.Start();
  }
}
