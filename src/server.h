#pragma once
#include <Wifi.h>

class PrivateServer {
    public:
       void initialize();
       void clients();
    private:
        const char* ssid = "MaksESP32";
        const char* password = "nigga2137";
        
        String header;

        String output16State = "off";
        String output17State = "off";

        const int output16 = 26;
        const int output17 = 27;

        unsigned long currentTime = millis();
        unsigned long previousTime = 0;
        const long timeoutTime = 2000;


};