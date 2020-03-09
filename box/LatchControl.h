#ifndef LatchControl_h
#define LatchControl_h

class LatchControl {
private:
  int _firstLatchPin;
  int _secondLatchPin;
  int _thirdLatchPin;
  int _fourthLatchPin;
  int selectedLatch;
  long millisSinceRelease;
  byte hasReleased = false;

public:
  LatchControl(int firstLatchPin, int secondLatchPin, int thirdLatchPin,
               int fourthLatchPin) {
    _firstLatchPin = firstLatchPin;
    _secondLatchPin = secondLatchPin;
    _thirdLatchPin = thirdLatchPin;
    _fourthLatchPin = fourthLatchPin;
  }

  void setup() {
    Serial.println("Latch control setup");
    pinMode(_firstLatchPin, OUTPUT);
    pinMode(_secondLatchPin, OUTPUT);
    pinMode(_thirdLatchPin, OUTPUT);
    pinMode(_fourthLatchPin, OUTPUT);
    resetLatchOpen();
  }

  void resetLatchOpen() {
    digitalWrite(_firstLatchPin, HIGH);
    digitalWrite(_secondLatchPin, HIGH);
    digitalWrite(_thirdLatchPin, HIGH);
    digitalWrite(_fourthLatchPin, HIGH);
  }

  void loop() {
    if (hasReleased) {
      long currentTime = millis() - 500;
      if (millisSinceRelease < currentTime) {
        // Serial.println("Resetting latches");
        resetLatchOpen();
        hasReleased = false;
      }
    }
  }

  void openLatch(int index) {
    switch (index) {
    case 0:
      selectedLatch = _firstLatchPin;
      break;
    case 1:
      selectedLatch = _secondLatchPin;
      break;
    case 2:
      selectedLatch = _thirdLatchPin;
      break;
    case 3:
      selectedLatch = _fourthLatchPin;
      break;
    }

    // Serial.print("Releasing latch: ");
    // Serial.println(selectedLatch);
    digitalWrite(selectedLatch, LOW);
    hasReleased = true;
    millisSinceRelease = millis();
  }
};
#endif
