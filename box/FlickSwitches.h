#ifndef FlickSwitches_h
#define FlickSwitches_h

class FlickSwitches
{
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
    FlickSwitches(int firstSwitchPin, int secondSwitchPin, int thirdSwitchPin, int fourthSwitchPin)
    {
        _firstSwitchPin = firstSwitchPin;
        _secondSwitchPin = secondSwitchPin;
        _thirdSwitchPin = thirdSwitchPin;
        _fourthSwitchPin = fourthSwitchPin;
    }
    void setup()
    {
        Serial.println("FlickSwitches Setup");
        pinMode(_firstSwitchPin, INPUT_PULLUP);
        pinMode(_secondSwitchPin, INPUT_PULLUP);
        pinMode(_thirdSwitchPin, INPUT_PULLUP);
        pinMode(_fourthSwitchPin, INPUT_PULLUP);
    }
    void loop()
    {
    }

    bool currentIsFlicked()
    {

        switch (_currentSwitch)
        {
        case 0:
            if (digitalRead(_firstSwitchPin) == LOW)
            {
                _firstSwitchValue++;
            }
            else
            {
                _firstSwitchValue = 0;
            }
            return _firstSwitchValue > 10;
        case 1:
            if (digitalRead(_secondSwitchPin) == LOW)
            {
                _secondSwitchValue++;
            }
            else
            {
                _secondSwitchValue = 0;
            }
            return _secondSwitchValue > 10;
        case 2:
            if (digitalRead(_thirdSwitchPin) == LOW)
            {
                _thirdSwitchValue++;
            }
            else
            {
                _thirdSwitchValue = 0;
            }
            return _thirdSwitchValue > 10;
        case 3:
            if (digitalRead(_fourthSwitchPin) == LOW)
            { 
                _fourthSwitchValue++;
            }
            else
            {
                _fourthSwitchValue = 0;
            }
            return _fourthSwitchValue > 10;

        default:
            break;
        }
    }
    bool isLast()
    {
        return _currentSwitch == 3;
    }

    int getCurrentSwitch(){
      return _currentSwitch;
    }
    
    void selectNextFlicker()
    {
      Serial.println("FlickSwitches selectNextFlicker");
      Serial.println(_currentSwitch);
        if (_currentSwitch < 3)
        {
            _currentSwitch++;
        }
        else
        {
            Serial.println("No more switches");
        }
    }

    bool isAllReset(){
       return (digitalRead(_firstSwitchPin) == HIGH && 
       digitalRead(_secondSwitchPin) == HIGH && 
       digitalRead(_thirdSwitchPin) == HIGH && 
       digitalRead(_fourthSwitchPin) == HIGH);
    }
};
#endif
