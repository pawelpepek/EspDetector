#include <NTPClient.h>
#include <WiFiUdp.h>
#include <ESP8266WiFi.h>

class TimeNTP
{
    public:
        TimeNTP();
        unsigned long get();
        void begin();

    private:
        WiFiUDP _ntpUDP;
        NTPClient _timeClient;
};