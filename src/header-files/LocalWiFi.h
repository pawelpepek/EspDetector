#include <ESP8266WiFi.h>

class LocalWiFi{
    public:
        LocalWiFi();
        bool connect();

    private:
        WiFiClientSecure _httpsClient;
};