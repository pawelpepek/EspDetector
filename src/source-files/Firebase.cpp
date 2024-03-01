#include "../header-files/Firebase.h"
#include <header-files/config.h>

Firebase::Firebase()
{
  _host = _REFERENCE_URL;

  if (_host.startsWith("https://"))
  {
    _host.remove(0, 8);
  }

  if (_host.endsWith("/"))
  {
    _host.remove(_host.length() - 1);
  }

  _httpsClient.setInsecure();
}

void Firebase::post(unsigned long value)
{
  Serial.println("wysylam");
  _valuesToSend.push(value);
}

FirebaseState Firebase::manageState()
{
  switch (_state)
  {
  case Ready:
    if (isTimeElapsed() && !_valuesToSend.empty())
    {
      _state = Sending;
    }
    break;
  case Sending:
    send();
    break;
  }

  return _state;
}

void Firebase::sendIfNotEmpty()
{
  if (!_valuesToSend.empty())
  {
    send();
  }
  _startTime = millis();
}

void Firebase::send()
{
  if (!_httpsClient.connect(_host, PORT))
  {
    Serial.println("rozlaczony");
    _state = Ready;
    return;
  }

  String msg = String(_valuesToSend.front());
  String jsonObject = String("/pushbutton.json");

  _httpsClient.print(String("POST ") + jsonObject + " HTTP/1.1\r\n" +
                     "Host: " + _host + "\r\n" +
                     "Connection: close\r\n" +
                     "Accept: */*\r\n" +
                     "User-Agent: Mozilla/4.0 (compatible; esp8266 Lua; Windows NT 5.1)\r\n" +
                     "Content-Type: application/json;charset=utf-8\r\n" +
                     "Content-Length: " + msg.length() + "\r\n" +
                     "\r\n" +
                     msg + "\r\n");
  if (_httpsClient.connected())
  {
    String line = _httpsClient.readStringUntil('\n');
    if (is200OK(line))
    {
      Serial.println("send");
      _valuesToSend.pop();
    }
    else
    {
      Serial.println("nie poszlo");
    }
  }
  else
  {
    Serial.println("rozlaczony");
  }
  _state = Ready;
}

bool Firebase::is200OK(String str)
{
  str.trim();
  if (str.length() < 6)
  {
    return false;
  }

  return str.endsWith("200 OK");
}

bool Firebase::isTimeElapsed()
{
  return millis() - _startTime > 2000;
}