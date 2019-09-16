#ifndef FlickSwitches_h
#define FlickSwitches_h

class FlickSwitches
{
private:
    int _currentSwitch = 0;

    int _firstSwitchPin;
    int _secondSwitchPin;
    int _thirdSwitchPin;
    int _fourthSwitchPin;
public:
    FlickSwitches(int firstSwitchPin, int secondSwitchPin, int thirdSwitchPin, int fourthSwitchPin)
    {
        _firstSwitchPin = firstSwitchPin;
        _secondSwitchPin = secondSwitchPin;
        _thirdSwitchPin = thirdSwitchPin;
        _fourthSwitchPin = fourthSwitchPin;
    }
    void setup() {
        pinMode(_firstSwitchPin, INPUT);
        pinMode(_secondSwitchPin, INPUT);
        pinMode(_thirdSwitchPin, INPUT);
        pinMode(_fourthSwitchPin, INPUT);
    }
    void loop() {

    }

    bool currentIsFlicked() {
        switch (_currentSwitch)
        {
        case 0:
            return digitalRead(_firstSwitchPin) == HIGH;
        case 1:
            return digitalRead(_secondSwitchPin) == HIGH;
        case 2:
            return digitalRead(_thirdSwitchPin) == HIGH;
        case 3:
            return digitalRead(_fourthSwitchPin) == HIGH;
        
        default:
            break;
        }
    }
    bool isLast() {
        return _currentSwitch == 3;
    }
    void selectNextFlicker() {
        if (_currentSwitch > 3) {
            _currentSwitch++;
        } else {
            Serial.println("No more switches");
        }
    }
};
#endif