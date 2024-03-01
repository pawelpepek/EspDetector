#include "header-files/Firebase.h"
#include "header-files/Detector.h"
#include "header-files/TimeNTP.h"
#include "header-files/LocalWiFi.h"

LocalWiFi _localWiFi;
Firebase _firebase;
Detector _detector(0, 3);
TimeNTP _timeNTP;

void setup()
{
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);

  _localWiFi.connect();

  _timeNTP.begin();
  Serial.println(_timeNTP.get());

  _detector.setup();
  _detector.switchPower(true);

  digitalWrite(LED_BUILTIN, HIGH);
}

void loop()
{
  if (_detector.detect())
  {
    _detector.switchPower(false);
    int moment = _timeNTP.get();
    _detector.switchPower(true);

    _firebase.post(moment);
  }

  FirebaseState state = _firebase.manageState();
  _detector.switchPower(state != Sending);
}