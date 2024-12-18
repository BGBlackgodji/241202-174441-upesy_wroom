#include "wifi.h"
#include <Arduino.h>

bool Network::__connect(int timeout) {
    while(true) {
        if (WiFi.isConnected()) return true;

        if (timeout <= 0) return false;

        int delayTime = 1000;

        delay(delayTime);
        timeout -= delayTime;
    }
}

bool Network::connect(std::string ssid, std::string password, int timeout) {
    WiFi.begin(ssid.c_str(), password.c_str());
    return __connect(timeout);
}

void Network::disconnect() {
    WiFi.disconnect();
}

std::string Network::GetIPv4() {
    if (!WiFi.isConnected()) return "";
    
    return WiFi.localIP().toString().c_str();
}
