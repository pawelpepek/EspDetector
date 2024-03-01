#include "../header-files/LocalWiFi.h"
#include "Arduino.h"
#include <header-files/config.h>

LocalWiFi::LocalWiFi() {}

bool LocalWiFi::connect()
{
    WiFi.mode(WIFI_STA);
    WiFi.disconnect();
    delay(1000);

    Serial.println();
    Serial.println();
    Serial.print("Connecting to: ");
    Serial.println(_SSID);
    WiFi.begin(_SSID, _PASSWORD);

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print("-");
    }

    Serial.println("");
    Serial.println("WiFi Connected");

    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());

    return true;
}
