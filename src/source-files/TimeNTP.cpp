#include "../header-files/TimeNTP.h"
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <ESP8266WiFi.h>

TimeNTP::TimeNTP() : _timeClient(_ntpUDP){}

void TimeNTP::begin()
{
    _timeClient.begin();
}

unsigned long TimeNTP::get()
{
    _timeClient.update();
    return _timeClient.getEpochTime();
}