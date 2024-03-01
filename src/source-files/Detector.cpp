#include "../header-files/Detector.h"
#include <ESP8266WiFi.h>

Detector::Detector(int pin, int pinPower)
{
  _pin = pin;
  _pinPower = pinPower;
}

void Detector::setup()
{
  pinMode(_pin, INPUT);
  pinMode(_pinPower, OUTPUT);
  switchPower(false);
}

void Detector::switchPower(bool power)
{
  digitalWrite(_pinPower, power);
}

bool Detector::detect()
{
  int newDetection = digitalRead(_pin);
  if (newDetection != _lastDetection)
  {
    _lastDetection = newDetection;
    if (newDetection == 0)
    {
      _detected = true;
    }
    else
    {
      if (_detected)
      {
        _detected = false;
        return true;
      }
    }
  }

  return false;
}
