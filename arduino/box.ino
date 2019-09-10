#include "LedControl.h"
#include "SimpleTimer.h"
#include <math.h>


int encoderPin1 = 2;
int encoderPin2 = 3;

volatile int lastEncoded = 0;
volatile long encoderValue = 0;

long lastencoderValue = 0;

int lastMSB = 0;
int lastLSB = 0;
/*
 Now we need a LedControl to work with.
 ***** These pin numbers will probably not work with your hardware *****
 pin 12 is connected to the DataIn 
 pin 13 is connected to the CLK 
 pin 10 is connected to LOAD 
 We have only a single MAX72XX.
 */
LedControl lc = LedControl(12,13,10,1);

// Our timer
SimpleTimer timer = SimpleTimer();
int timerId;

// 2 min in milliseconds
long time = 120000;

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


void setup() {
  Serial.begin(9600);
  Serial.println(time);
  /*
   The MAX72XX is in power-saving mode on startup,
   we have to do a wakeup call
   */
  lc.shutdown(0,false);
  /* Set the brightness to a medium values */
  lc.setIntensity(0,8);
  /* and clear the display */
  lc.clearDisplay(0);

  timerId = timer.setInterval(1, countdown);  


  // Rotary encoder stuff
  pinMode(encoderPin1, INPUT);
  pinMode(encoderPin2, INPUT);

  digitalWrite(encoderPin1, HIGH); //turn pullup resistor on
  digitalWrite(encoderPin2, HIGH); //turn pullup resistor on

  //call updateEncoder() when any high/low changed seen
  //on interrupt 0 (pin 2), or interrupt 1 (pin 3)
  attachInterrupt(0, updateEncoder, CHANGE);
  attachInterrupt(1, updateEncoder, CHANGE);
}

void loop() { 
  timer.run();
  Serial.println(encoderValue);
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


void updateEncoder(){
  int MSB = digitalRead(encoderPin1); //MSB = most significant bit
  int LSB = digitalRead(encoderPin2); //LSB = least significant bit

  int encoded = (MSB << 1) |LSB; //converting the 2 pin value to single number 
  int sum = (lastEncoded << 2) | encoded; //adding it to the previous encoded value 
  if(sum == 0b1101 || sum == 0b0100 || sum == 0b0010 || sum == 0b1011) encoderValue ++; 
  if(sum == 0b1110 || sum == 0b0111 || sum == 0b0001 || sum == 0b1000) encoderValue --; 
  lastEncoded = encoded; //store this value for next time 
}