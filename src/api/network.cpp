#include "network.h"

string Network::_ssid = "";
string Network::_password = "";
 
int Network::timeout = 20 * 1000;

bool Network::is2_4GHz(int networkIndex) {
    int channel = WiFi.channel(networkIndex);

    Serial.print("channel: ");
    Serial.println(channel);

    return channel >= 1 && channel <= 14;
}

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

        Serial.println(Network::GetLocalIPv4().c_str());
        return true;
    }

    Serial.println("not found");
    return false;
}

std::string Network::GetLocalIPv4() {
    if (!WiFi.isConnected()) return "";
    
    return WiFi.localIP().toString().c_str();
}

bool Network::load(string ssid, string password) {
    if (!connect(ssid, password)) 
        return false;

    Network::_ssid = ssid;
    Network::_password = password;

    return true;
}

bool Network::tick() {
    if (WiFi.isConnected())
        return true;

    if (connect(Network::_ssid, Network::_password))
        return true;
    
    delay(5 * 1000);
    return false;
}