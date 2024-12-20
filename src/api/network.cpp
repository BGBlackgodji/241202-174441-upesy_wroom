#include "network.h"

int Network::timeout = 20 * 1000;

bool Network::connect(string ssid, string password)
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

        if (password.empty()) {
            WiFi.begin(ssid.c_str());
        }
        else {
            WiFi.begin(ssid.c_str(), password.c_str());
        }

        WiFi.waitForConnectResult(Network::timeout);

        if (!WiFi.isConnected()) {
            Serial.println("connect timeout");
            return false;
        }

        return true;
    }

    Serial.println("not found");
    return false;
}

bool Network::load(string ssid, string password) {
    if (!connect(ssid, password)) return false;

    Network::_ssid = ssid;
    Network::_password = password;

    WiFi.onEvent(
        [](WiFiEvent_t event, WiFiEventInfo_t info) {
            Serial.println("disconnected");
            Serial.println(info.wifi_sta_disconnected.reason);

            while (!connect(Network::_ssid, Network::_password)) {}
        },
        ARDUINO_EVENT_WIFI_STA_DISCONNECTED
    );

    Serial.println(Network::GetLocalIPv4().c_str());

    return true;
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
