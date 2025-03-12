#pragma once
#include <Wifi.h>

class PrivateServer {
    public:
       void initialize();
       void clients();
       bool sensorsEnabled = false;
    private:
        const char* ssid = "MaksESP32";
        const char* password = "nigga2137";
        
        String header;

        String statePin16 = "off";
        String statePin17 = "off";

        const int output16 = 26;
        const int output17 = 27;

        unsigned long currentTime = millis();
        unsigned long previousTime = 0;
        const long timeoutTime = 2000;


};