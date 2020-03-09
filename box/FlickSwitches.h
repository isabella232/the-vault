#ifndef FlickSwitches_h
#define FlickSwitches_h

class FlickSwitches {
private:
  int _currentSwitch = 0;

  int _firstSwitchPin;
  int _firstSwitchValue;
  int _secondSwitchPin;
  int _secondSwitchValue;
  int _thirdSwitchPin;
  int _thirdSwitchValue;
  int _fourthSwitchPin;
  int _fourthSwitchValue;

public:
  FlickSwitches(int firstSwitchPin, int secondSwitchPin, int thirdSwitchPin,
                int fourthSwitchPin) {
    _firstSwitchPin = firstSwitchPin;
    _secondSwitchPin = secondSwitchPin;
    _thirdSwitchPin = thirdSwitchPin;
    _fourthSwitchPin = fourthSwitchPin;
  }
  void setup() {
    Serial.println("FlickSwitches Setup");
    pinMode(_firstSwitchPin, INPUT_PULLUP);
    pinMode(_secondSwitchPin, INPUT_PULLUP);
    pinMode(_thirdSwitchPin, INPUT_PULLUP);
    pinMode(_fourthSwitchPin, INPUT_PULLUP);
  }
  void loop() {}

  bool currentIsFlicked() {
    switch (_currentSwitch) {
      case 0:
        return firstFlicked();
      case 1:
        return secondFlicked();
      case 2:
        return thirdFlicked();
      case 3:
        return fourthFlicked();
      default:
        break;
    }  
  }

  bool laterSwitchFlicked() {
    switch (_currentSwitch) {
      case 0:
        return secondFlicked() || thirdFlicked() || fourthFlicked();
      case 1:
        return  thirdFlicked() || fourthFlicked();
      case 2:
        return  fourthFlicked();
      case 3:
        // There are no more switches after the fourth one
        return false;
    }
  }

  bool isLast() { return _currentSwitch == 3; }

  int getCurrentSwitch() { return _currentSwitch; }

  void selectNextFlicker() {
    Serial.println("FlickSwitches selectNextFlicker");
    Serial.println(_currentSwitch);
    if (_currentSwitch < 3) {
      _currentSwitch++;
    } else {
      Serial.println("No more switches");
    }
  }

  bool isAllReset() {
    return (digitalRead(_firstSwitchPin) == HIGH &&
            digitalRead(_secondSwitchPin) == HIGH &&
            digitalRead(_thirdSwitchPin) == HIGH &&
            digitalRead(_fourthSwitchPin) == HIGH);
  }

  bool firstFlicked() {
    return digitalRead(_firstSwitchPin) == LOW;
  }

  bool secondFlicked() {
    return digitalRead(_secondSwitchPin) == LOW;
  }

  bool thirdFlicked() {
    return digitalRead(_thirdSwitchPin) == LOW;
  }

  bool fourthFlicked() {
    return digitalRead(_fourthSwitchPin) == LOW;
  }
};
#endif
