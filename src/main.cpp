#include <Arduino.h>

#include <api/network.h>
#include <api/server.h>

#include <core/setting.h>

void setup() 
{
    Serial.begin(9600);
    Serial.println();

    if (!Network::connect("kiewdesktop", "abcde1234")) {
        while (true) {}
    }

    Serial.println(Network::GetLocalIPv4().c_str());

    serverSetup();
}

void loop() 
{
    serverLoop();
}
