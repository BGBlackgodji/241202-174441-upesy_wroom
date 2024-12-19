#include "network.h"

bool Network::connect(string ssid, string password, int timeout)
{
    WiFi.mode(WIFI_STA);

    int networkNum = WiFi.scanNetworks(false, true);
    
    Serial.println("connecting");

    for (int i = 0; i < networkNum; i++) {
        string name = WiFi.SSID(i).c_str();

        if (name != ssid) continue;

        if (!Network::is2_4GHz(i)) {
            Serial.println("support only 2.4GHz");
            return false;
        }

        WiFi.begin(ssid.c_str(), password.c_str());

        WiFi.waitForConnectResult(timeout);

        if (!WiFi.isConnected()) {
            Serial.println("connect timeout");
            return false;
        }

        return true;
    }

    Serial.println("not found");
    return false;
}

void Network::disconnect() {
    WiFi.disconnect();

    WiFi.mode(WIFI_OFF);
}

bool Network::is2_4GHz(int networkIndex) {
    int channel = WiFi.channel(networkIndex);

    Serial.print("channel: ");
    Serial.println(channel);

    return channel >= 1 && channel <= 14;
}

std::string Network::GetLocalIPv4() {
    if (!WiFi.isConnected()) return "";
    
    return WiFi.localIP().toString().c_str();
}
